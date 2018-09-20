#include "StaticShader.hpp"

StaticShader::StaticShader() : ShaderProgram("source/data/shaders/vertexShader.glsl","source/data/shaders/fragmentShader.glsl"){

    createProgram();
}

StaticShader::~StaticShader(){

}

void StaticShader::bindAttributes(){

    bindAttribute(0, "position");
    bindAttribute(1, "textureCoords");

}

void StaticShader::getAllUniformLocations(){

    m_loc_transformation_matrix = getUniformLocation( "transformationMatrix" );
    m_loc_projection_matrix = getUniformLocation( "projectionMatrix" );
    m_loc_view_matrix = getUniformLocation( "viewMatrix" );
}

void StaticShader::loadTransformationMatrix( const glm::mat4 t_matrix ){

    loadMatrix( m_loc_transformation_matrix, t_matrix );
}

void StaticShader::loadProjectionMatrix( const glm::mat4 t_matrix ){

    loadMatrix( m_loc_projection_matrix, t_matrix );
}

void StaticShader::loadViewMatrix( const Camera t_camera ){

    glm::mat4 matrix = utils::createViewMatrix( t_camera );
    loadMatrix( m_loc_view_matrix, matrix );
}