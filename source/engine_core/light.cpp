#include "light.hpp"

Light::Light( glm::vec3 t_position, glm::vec3 t_color, GLfloat t_intensity ) : m_position(t_position), m_color(t_color) , m_intensity(t_intensity){

}

void Light::setColor( glm::vec3 t_value ){

    m_color = t_value;
}

glm::vec3 Light::getColor(){

    return m_color;
}

void Light::setPosition( glm::vec3 t_value ){

    m_position = t_value;
}

glm::vec3 Light::getPosition(){

    return m_position;
}

void Light::setIntensity( GLfloat t_value ){

    m_intensity = t_value;
}

GLfloat Light::getIntensity(){

    return m_intensity;
}