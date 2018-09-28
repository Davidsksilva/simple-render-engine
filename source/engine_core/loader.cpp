#include "loader.hpp"

RawModel Loader::loadToVAO( const std::vector<GLfloat>& t_positionitions,const std::vector<GLuint>& t_indices, const std::vector<GLfloat>& t_texture_coordinates_vector){

    // Create VAO
    GLuint vao_id = createVAO();
    bindIndicesBuffer(t_indices);
    // Store model positionitions on VAO 0
    storeDataInAttributeList( 0, 3, t_positionitions );
    storeDataInAttributeList( 1, 2, t_texture_coordinates_vector);
    // Unbind
    unbindVAO();
    // Return RawModel
    return RawModel( vao_id , t_indices.size() );
}

GLuint Loader::loadTexture( const std::string t_file_name ){
    sf::Image image;
    GLuint texture_id ;
    glGenTextures(1, &texture_id);
    

    // Load texture array from file
    if(!image.loadFromFile( t_file_name ))
        std::cerr << "Problem loading texture image " << std::endl;

    image.flipVertically();
    
    glBindTexture(GL_TEXTURE_2D, texture_id);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.getSize().x, image.getSize().y, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.getPixelsPtr());

    // Set Filtering
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    // Set Wrapping
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    
    

    m_textures.push_back(texture_id);

    return texture_id;
}

void Loader::cleanUp(){
    
    // Delete all Vertex Arrays
    for(unsigned int i = 0; i < m_vaos.size(); i++ )
        glDeleteVertexArrays( 1, &m_vaos[i] );
    // Delete all Buffers
    for(unsigned int i = 0; i < m_vbos.size(); i++)
        glDeleteBuffers( 1, &m_vbos[i] );
    // Delete all Textures
    for(unsigned int i = 0; i < m_textures.size(); i++)
        glDeleteTextures(1,&m_textures[i]);
}

GLuint Loader::createVAO(){
    
    GLuint vao_id;
    // Create one Vertex Array (VAO) and keep address
    glGenVertexArrays( 1, &vao_id );
    // Add VAO to vector
    m_vaos.push_back( vao_id );
    // Bind VAO
    glBindVertexArray( vao_id );
    return vao_id;
}

void Loader::storeDataInAttributeList(const GLuint t_attribute_number, const GLuint t_size, const std::vector<GLfloat>& t_data){

    GLuint vbo_id;
    // Generate buffer object of size 1 and store it in vbo_id
    glGenBuffers( 1,&vbo_id );
    // Add VBO to vector
    m_vbos.push_back( vbo_id );
    // Bind the Buffer
    glBindBuffer( GL_ARRAY_BUFFER, vbo_id );
    // Put the data on the buffer, the data will be modified once and will be used many times with GL drawing commands
    glBufferData( GL_ARRAY_BUFFER, t_data.size() * sizeof ( t_data.at( 0 )), t_data.data(), GL_STATIC_DRAW );
    glVertexAttribPointer( t_attribute_number, t_size , GL_FLOAT, false, 0,0 );
    // Unbind Buffer
    glBindBuffer( GL_ARRAY_BUFFER, 0 );
}

void Loader::unbindVAO(){
    // Unbind the Vertex Array
    glBindVertexArray( 0 );
}

void Loader::bindIndicesBuffer( std::vector<GLuint> indices ){

    GLuint vbo_id;
    // Generate buffer object of size 1 and store it in vbo_id
    glGenBuffers( 1, &vbo_id );
    // Add VBO to vector
    m_vbos.push_back( vbo_id );
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, vbo_id );
    // Put the data on the buffer, the data will be modified once and will be used many times with GL drawing commands
    glBufferData( GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof( indices.at( 0 )), indices.data(), GL_STATIC_DRAW );


}

 RawModel Loader::loadObj( const char* t_file_path ){

     std::vector < GLfloat > vertices_vector;
     std::vector < GLfloat > texture_vector;
     std::vector < GLfloat > normals_vector;
     std::vector < GLuint > indices_vector;
     utils::loadOBJ(t_file_path,vertices_vector,texture_vector,normals_vector,indices_vector);

    /*for( GLfloat i : vertices_vector){
        std::cout << i << std::endl;
    }
    std::cout << "-----" << std::endl;
    for( GLfloat i : indices_vector){
        std::cout << i << std::endl;
    }
    std::cout << "-----" << std::endl;
    for( GLfloat i : texture_vector){
        std::cout << i << std::endl;
    }*/
    return loadToVAO( vertices_vector, indices_vector, texture_vector );
 }

