#include "model_texture.hpp"

ModelTexture::ModelTexture( const GLuint t_id , const GLfloat t_specular_power, const GLfloat t_specular_intensity)
                             : m_texture_id(t_id), m_specular_power(t_specular_power),m_specular_intensity(t_specular_intensity) {
    
}

ModelTexture::ModelTexture() : m_texture_id ( 0 ){

}

GLuint ModelTexture::getID() const{

    return m_texture_id;
}

void ModelTexture::setSpecularIntensity( GLfloat t_value  ){

    m_specular_intensity = t_value;
}

GLfloat ModelTexture::getSpecularIntensity(){

    return m_specular_intensity;
}

void ModelTexture::setSpecularPower( GLfloat t_value ){

    m_specular_power = t_value;
}

GLfloat ModelTexture::getSpecularPower(){

    return m_specular_power;
}