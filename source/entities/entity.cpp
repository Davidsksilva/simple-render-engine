#include "entity.hpp"

Entity::Entity( const TexturedModel t_model, const glm::vec3 t_position, const glm::vec3 t_rotation, const GLfloat t_scale )
            : m_model( t_model), m_position(t_position), m_rotation(t_rotation), m_scale(t_scale){

}

void Entity::increasePosition( const GLfloat t_dx, const GLfloat t_dy, const GLfloat t_dz ){

    m_position.x += t_dx;
    m_position.y += t_dy;
    m_position.z += t_dz;
}

void Entity::increaseRotation( const GLfloat t_dx, const GLfloat t_dy, const GLfloat t_dz ){

    m_rotation.x += t_dx;
    m_rotation.y += t_dy;
    m_rotation.z += t_dz;
}

TexturedModel Entity::getModel() const {

    return m_model;
}

void Entity::setModel(TexturedModel model){

    m_model = model;
}

glm::vec3 Entity::getPosition(){

    return m_position;
}

void Entity::setPosition(glm::vec3 position){

    m_position = position;
}

glm::vec3 Entity::getRotation(){

    return m_rotation;
}

void Entity::setRotation(glm::vec3 rotation){

    m_rotation = rotation;
}

glm::vec3 Entity::getScale(){

    return glm::vec3( m_scale, m_scale, m_scale);
}

void Entity::setScale(GLfloat scale){

    m_scale = scale;
}