#ifndef UTILITIES_HPP
#define UTILITIES_HPP

#include <iostream>
#include <glm/glm.hpp>
#include <GL/glew.h>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/transform.hpp> 
#include "../Camera.hpp"


namespace utils{

    glm::mat4 createRotationMatrix( const glm::vec3 t_rotation );

    glm::mat4 createTransformationMatrix( const glm::vec3 t_translation, const glm::vec3 t_rotation, const glm::vec3 t_scale );

    glm::mat4 createViewMatrix( Camera t_camera );

    std::string readFile( const char* t_file_path );

}


#endif // UTILITIES_HPP

