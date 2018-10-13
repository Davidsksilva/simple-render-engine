#include "terrain_shader.hpp"

TerrainShader::TerrainShader() : ShaderProgram("source/res/shaders/terrainVertexShader.glsl","source/res/shaders/terrainFragmentShader.glsl"){

    createProgram();
}

TerrainShader::~TerrainShader(){

}

void TerrainShader::bindAttributes(){

    bindAttribute(0, "position");
    bindAttribute(1, "textureCoords");
    bindAttribute(2, "normal");

}

void TerrainShader::getAllUniformLocations(){

    m_loc_transformation_matrix = getUniformLocation( "transformationMatrix" );
    m_loc_projection_matrix = getUniformLocation( "projectionMatrix" );
    m_loc_view_matrix = getUniformLocation( "viewMatrix" );
    m_loc_light_color = getUniformLocation( "lightColor");
    m_loc_light_position = getUniformLocation( "lightPosition");
    m_loc_light_intensity = getUniformLocation("lightIntensity");
    m_loc_specular_intensity = getUniformLocation( "specularIntensity");
    m_loc_specular_power = getUniformLocation( "specularPower");
}

void TerrainShader::loadTransformationMatrix( const glm::mat4 p_matrix ){

    loadMatrix( m_loc_transformation_matrix, p_matrix );
}

void TerrainShader::loadProjectionMatrix( const glm::mat4 p_matrix ){

    loadMatrix( m_loc_projection_matrix, p_matrix );
}

void TerrainShader::loadViewMatrix( const Camera p_camera ){

    glm::mat4 matrix = utils::createViewMatrix( p_camera );
    loadMatrix( m_loc_view_matrix, matrix );
}

void TerrainShader::loadLight( Light p_light ){

    loadVector( m_loc_light_color, p_light.getColor());
    loadVector( m_loc_light_position, p_light.getPosition());
    loadFloat( m_loc_light_intensity, p_light.getIntensity());
}

void TerrainShader::loadSpecular( ModelTexture p_model_texture ){
    
    loadFloat( m_loc_specular_intensity, p_model_texture.getSpecularIntensity());
    loadFloat( m_loc_specular_power, p_model_texture.getSpecularPower());
}