#include "camera.hpp"

Camera::Camera() : m_position(glm::vec3( 0, 0, 0 )), m_yaw( 0.0f), m_pitch( 0.0f ){

}

void Camera::move(){

    if( sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
        m_position.z -= 0.02f;
    }

    if( sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
        m_position.x += 0.02f;
    }

    if( sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
        m_position.x -= 0.02f;
    }

    if( sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
        m_position.z += 0.02f;
    }

}

GLfloat Camera::getPitch(){

    return m_pitch;
}

GLfloat Camera::getYaw(){

    return m_yaw;
}

glm::vec3 Camera::getPosition(){

    return m_position;
}

void Camera::setPosition(glm::vec3 t_position){

    m_position = t_position;
}

void Camera::setPitch( GLfloat t_value){

    m_pitch = t_value;
}

void Camera::setYaw ( GLfloat t_value ){

    m_yaw = t_value;
}