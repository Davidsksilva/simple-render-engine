#include "utilities.hpp"
#include <fstream>
#include <sstream>

glm::mat4 utils::createRotationMatrix( const glm::vec3 t_rotation ){

    // Create a 4x4 indentity matrix
    glm::mat4 rot_x_matrix = glm::mat4(1.0f);

    // Create rotation_matrix on X axis
    rot_x_matrix[1][1] = glm::cos( t_rotation.x );
    rot_x_matrix[1][2] = - glm::sin( t_rotation.x );
    rot_x_matrix[2][1] = glm::sin( t_rotation.x );
    rot_x_matrix[2][2] = glm::cos( t_rotation.x );

    // Create a 4x4 indentity matrix
    glm::mat4 rot_y_matrix = glm::mat4(1.0f);

    // Create Rotation Matrix on Y axis
    rot_y_matrix[0][0] = glm::cos( t_rotation.y );
    rot_y_matrix[0][2] = glm::sin( t_rotation.y );
    rot_y_matrix[2][0] = - glm::sin( t_rotation.y );
    rot_y_matrix[2][2] = glm::cos( t_rotation.y );

    // Create a 4x4 indentity matrix
    glm::mat4 rot_z_matrix = glm::mat4(1.0f);

    // Create Rotation Matrix on Z axis

    rot_z_matrix[0][0] = glm::cos( t_rotation.z );
    rot_z_matrix[0][1] = - glm::sin( t_rotation.z );
    rot_z_matrix[1][0] = glm::sin( t_rotation.z );
    rot_z_matrix[1][1] = glm::cos( t_rotation.z );

    return rot_z_matrix * rot_y_matrix * rot_x_matrix;
}

glm::mat4 utils::createTransformationMatrix( const glm::vec3 t_translation, const glm::vec3 t_rotation, const glm::vec3 t_scale ){

    glm::mat4 scale_matrix = glm::scale( t_scale );
    glm::mat4 translation_matrix = glm::translate( t_translation );
    glm::mat4 rotation_matrix = createRotationMatrix( t_rotation );

    return translation_matrix * rotation_matrix * scale_matrix;
}

glm::mat4 utils::createViewMatrix( Camera t_camera ){

    glm::mat4 view_matrix  = glm::mat4(1.0f);

    view_matrix = glm::rotate( view_matrix, glm::radians( t_camera.getPitch() ), { 1, 0, 0} );
    view_matrix = glm::rotate( view_matrix, glm::radians( t_camera.getYaw() ), { 0, 1, 0} );
    view_matrix = glm::translate( view_matrix, -t_camera.getPosition() );

    return view_matrix;
}

std::string utils::readFile( const char* t_file_path ){

    std::ifstream file_stream( t_file_path, std::ios::in );

    // Check if file exists
    if( !file_stream.is_open() ){
        std::cerr << "Could not read file " << t_file_path << " File does not exist" << std::endl;
        return "";
    }

    std::string line = "";
    std::string content;
    
    // Read fale and store content
    while( !file_stream.eof() ) {

        std::getline( file_stream, line );
        content.append( line + "\n" );
    }

    file_stream.close();
    return content;
}

static void splitString( std::string t_string, const char t_delimiter, std::vector < std::string >& t_vector){

    std::string temp = "";
    for( char& c : t_string ){
        if(c != t_delimiter){
            temp.insert( temp.end(), c );
        }
        else{
            if(!temp.empty()){
                t_vector.push_back(temp);
            }
            temp = "";
        }
    }

    if(!temp.empty()){
        t_vector.push_back(temp);
    }

}

static void processVertex( std::vector < GLuint >& t_indices_vector,std::vector < GLfloat >& t_vertices_vector,
                            std::vector < GLfloat >& t_normals_vector,std::vector < GLfloat >& t_texture_vector, 
                            std::vector <std::string>& t_vertex_str, std::vector <glm::vec2>& t_temp_texture,
                            std::vector <glm::vec3>& t_temp_normals, std::vector <glm::vec3>& t_temp_vertices, GLuint * index_cout){
    
    // Push vertex refered by the index
    t_vertices_vector.push_back(t_temp_vertices[std::stoi(t_vertex_str[0])-1].x);
    t_vertices_vector.push_back(t_temp_vertices[std::stoi(t_vertex_str[0])-1].y);
    t_vertices_vector.push_back(t_temp_vertices[std::stoi(t_vertex_str[0])-1].z);
    
    // Push texture coords refered by the index
    t_texture_vector.push_back(t_temp_texture[std::stoi(t_vertex_str[1]) -1].x);
    t_texture_vector.push_back(t_temp_texture[std::stoi(t_vertex_str[1]) -1].y);

    // Push normals refered by the index
    t_normals_vector.push_back(t_temp_normals[std::stoi(t_vertex_str[2]) -1].x);
    t_normals_vector.push_back(t_temp_normals[std::stoi(t_vertex_str[2]) -1].y);
    t_normals_vector.push_back(t_temp_normals[std::stoi(t_vertex_str[2]) -1].z);

    // Push the index in order
    for( GLuint v = 0; v < 3; v++){
        t_indices_vector.push_back(*index_cout);
        (*index_cout)++;
    }

}
bool utils::loadOBJ( const char* t_file_path, std::vector < GLfloat >& t_vertices_vector, 
                    std::vector < GLfloat >& t_texture_vector, std::vector < GLfloat >& t_normals_vector ,
                    std::vector <GLuint>& t_indices_vector){


    std::ifstream file_stream( t_file_path, std::ios::in );

    // Check if the file exists
    if ( !file_stream.is_open() ){

        std::cerr << "Could not read  file " << t_file_path << " File does not exist" << std::endl;
        return false;
    }

    // Initialize temporary variables

    std::string line = "";

    std::vector <glm::vec3> temp_vertices;
    std::vector <glm::vec2> temp_texture;
    std::vector <glm::vec3> temp_normals;

    std::vector < GLuint > uv_indices;
    std::vector < GLuint > normal_indices;

    GLuint index_count = 0;

    while( 1 ){

          
        std::getline( file_stream, line ) ;

        // Check if file is empty
        if(line.empty()){
            break;
        }

        // Split line by white space
        std::istringstream iss( line );
        std::vector<std::string> result{ std::istream_iterator<std::string>(iss),{}};
        
        // Identify line by the first element
        if( result[0].compare("v") == 0 ){

            temp_vertices.push_back(glm::vec3(std::strtof(result[1].c_str(),0),std::strtof(result[2].c_str(),0),std::strtof(result[3].c_str(),0)));
        }
        else if( result[0].compare("vt") == 0 ){

            temp_texture.push_back(glm::vec2(std::strtof(result[1].c_str(),0),std::strtof(result[2].c_str(),0)));
        }
        else if( result[0].compare("vn") == 0 ){

            temp_normals.push_back(glm::vec3(std::strtof(result[1].c_str(),0),std::strtof(result[2].c_str(),0),std::strtof(result[3].c_str(),0)));
        }
        else if( result[0].compare("f") == 0 ){
           
            std::vector < std::string > first_vertex;

            splitString( result[1] , '/', first_vertex );

            processVertex(t_indices_vector,t_vertices_vector,t_normals_vector,t_texture_vector, first_vertex,temp_texture,temp_normals,temp_vertices,&index_count);

            std::vector < std::string > second_vertex;

            splitString( result[2] , '/', second_vertex);

            processVertex(t_indices_vector,t_vertices_vector,t_normals_vector,t_texture_vector, second_vertex,temp_texture,temp_normals,temp_vertices,&index_count);

            std::vector < std::string > third_vertex;

            splitString( result[3] , '/', third_vertex);

            processVertex(t_indices_vector,t_vertices_vector,t_normals_vector,t_texture_vector, third_vertex,temp_texture,temp_normals,temp_vertices,&index_count);

        }
    }
    file_stream.close();
    return true;

}

    




