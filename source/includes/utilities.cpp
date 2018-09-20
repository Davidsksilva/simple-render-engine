#include "utilities.hpp"


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

    




