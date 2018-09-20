#include "Entity.hpp"

Entity::Entity( TexturedModel  model, glm::vec3 position, glm::vec3 rotation, GLfloat scale ){

    this->model = model;
    this->position = position;
    this->rotation = rotation;
    this->scale = scale;
}

void Entity::increasePosition( GLfloat dx, GLfloat dy, GLfloat dz ){

    this->position.x += dx;
    this->position.y += dy;
    this->position.z += dz;
}

void Entity::increaseRotation( GLfloat dx, GLfloat dy, GLfloat dz ){

    this->rotation.x += dx;
    this->rotation.y += dy;
    this->rotation.z += dz;
}


TexturedModel Entity::getModel(){

    return this->model;
}

void Entity::setModel(TexturedModel model){

    this->model = model;
}

glm::vec3 Entity::getPosition(){

    return this->position;
}

void Entity::setPosition(glm::vec3 position){

    this->position = position;
}

glm::vec3 Entity::getRotation(){

    return this->rotation;
}

void Entity::setRotation(glm::vec3 rotation){

    this->rotation = rotation;
}

glm::vec3 Entity::getScale(){

    return glm::vec3( this->scale, this->scale, this->scale);
}

void Entity::setScale(GLfloat scale){

    this->scale = scale;
}