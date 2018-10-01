#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "../includes/includes.hpp"
#include "../models/textured_model.hpp"

class Entity{

    private:

    TexturedModel m_model;
    glm::vec3 m_position;
    glm::vec3 m_rotation;
    GLfloat m_scale;

    public:

    Entity( const TexturedModel  t_model, const glm::vec3 t_position, const glm::vec3 t_rotation, const GLfloat t_scale );

    void increasePosition( const GLfloat t_dx, const GLfloat t_dy, const GLfloat t_dz );
    void increaseRotation( const GLfloat t_dx, const GLfloat t_dy, const GLfloat t_dz );

    TexturedModel getModel() const;
    void setModel( const TexturedModel t_model );

    glm::vec3 getPosition();
    void setPosition( const glm::vec3 t_position );

    glm::vec3 getRotation();
    void setRotation( const glm::vec3 t_rotation );

    glm::vec3 getScale();
    void setScale( const GLfloat t_scale );



};

#endif // ENTITY_HPP