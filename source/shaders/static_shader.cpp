#include "static_shader.hpp"

StaticShader::StaticShader() : ShaderProgram("source/res/shaders/vertexShader.glsl","source/res/shaders/fragmentShader.glsl"){

    createProgram();
}

StaticShader::~StaticShader(){

}

void StaticShader::bindAttributes(){

    bindAttribute(0, "position");
    bindAttribute(1, "textureCoords");
    bindAttribute(2, "normal");

}

void StaticShader::getAllUniformLocations(){

    m_loc_transformation_matrix = getUniformLocation( "transformationMatrix" );
    m_loc_projection_matrix = getUniformLocation( "projectionMatrix" );
    m_loc_view_matrix = getUniformLocation( "viewMatrix" );
    m_loc_light_color = getUniformLocation( "lightColor");
    m_loc_light_position = getUniformLocation( "lightPosition");
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

void StaticShader::loadLight( Light t_light ){

    loadVector( m_loc_light_color, t_light.getColor());
    loadVector( m_loc_light_position, t_light.getPosition());
}