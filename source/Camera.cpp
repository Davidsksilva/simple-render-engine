#include "Camera.hpp"

Camera::Camera(){

    position = glm::vec3(0,0,0);
}

void Camera::move(){

    if( sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
        position.z -= 0.02f;
    }

    if( sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
        position.x += 0.02f;
    }

    if( sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
        position.x -= 0.02f;
    }

    if( sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
        position.z += 0.02f;
    }

}

GLfloat Camera::getPitch(){

    return this->pitch;
}

GLfloat Camera::getYaw(){

    return this->yaw;
}

glm::vec3 Camera::getPosition(){

    return this->position;
}