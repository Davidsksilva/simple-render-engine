#include "Loader.hpp"

RawModel Loader::loadToVAO( const std::vector<GLfloat>& positions,const std::vector<GLuint>& indices, const std::vector<GLfloat>& textureCoords){

    // Create VAO
    GLuint vaoID = createVAO();
    bindIndicesBuffer(indices);
    // Store model positions on VAO 0
    storeDataInAttributeList( 0, 3, positions );
    storeDataInAttributeList( 1, 2, textureCoords);
    // Unbind
    unbindVAO();
    // Return RawModel
    return RawModel( vaoID, indices.size() );
}

GLuint Loader::loadTexture( std::string fileName){
    sf::Image image;
    GLuint textureID ;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    // Load texture array from file
    if(!image.loadFromFile(fileName))
        std::cerr << "Problem loading texture image " << std::endl;


    // Set Wrapping
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // Set Filtering
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.getSize().x, image.getSize().y, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.getPixelsPtr());

    textures.push_back(textureID);
    return textureID;
}

void Loader::cleanUp(){
    
    // Delete all Vertex Arrays
    for(unsigned int i = 0; i < vaos.size(); i++ )
        glDeleteVertexArrays( 1, &vaos[i] );
    // Delete all Buffers
    for(unsigned int i = 0; i < vbos.size(); i++)
        glDeleteBuffers( 1, &vbos[i] );
    // Delete all Textures
    for(unsigned int i = 0; i < textures.size(); i++)
        glDeleteTextures(1,&textures[i]);
}

GLuint Loader::createVAO(){
    
    GLuint vaoID;
    // Create one Vertex Array (VAO) and keep address
    glGenVertexArrays( 1, &vaoID );
    // Add VAO to vector
    vaos.push_back( vaoID );
    // Bind VAO
    glBindVertexArray( vaoID );
    return vaoID;
}

void Loader::storeDataInAttributeList(int attributeNumber,  GLuint size, const std::vector<GLfloat>& data){

    GLuint vboID;
    // Generate buffer object of size 1 and store it in vboID
    glGenBuffers( 1,&vboID );
    // Add VBO to vector
    vbos.push_back( vboID );
    // Bind the Buffer
    glBindBuffer( GL_ARRAY_BUFFER, vboID );
    // Put the data on the buffer, the data will be modified once and will be used many times with GL drawing commands
    glBufferData( GL_ARRAY_BUFFER, data.size() * sizeof ( data.at( 0 )), data.data(), GL_STATIC_DRAW );
    glVertexAttribPointer( attributeNumber, size , GL_FLOAT, false, 0,0 );
    // Unbind Buffer
    glBindBuffer( GL_ARRAY_BUFFER, 0 );
}

void Loader::unbindVAO(){
    // Unbind the Vertex Array
    glBindVertexArray( 0 );
}

void Loader::bindIndicesBuffer( std::vector<GLuint> indices ){

    GLuint vboID;
    // Generate buffer object of size 1 and store it in vboID
    glGenBuffers( 1, &vboID );
    // Add VBO to vector
    vbos.push_back( vboID );
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, vboID );
    // Put the data on the buffer, the data will be modified once and will be used many times with GL drawing commands
    glBufferData( GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof( indices.at( 0 )), indices.data(), GL_STATIC_DRAW );


}

