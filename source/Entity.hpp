#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "includes.hpp"
#include "models/TexturedModel.hpp"

class Entity{

    private:

    TexturedModel model;
    glm::vec3 position;
    glm::vec3 rotation;
    GLfloat scale;

    public:

    Entity( TexturedModel  model, glm::vec3 position, glm::vec3 rotation, GLfloat scale );

    void increasePosition( GLfloat dx, GLfloat dy, GLfloat dz );
    void increaseRotation( GLfloat dx, GLfloat dy, GLfloat dz );

    TexturedModel getModel();
    void setModel( TexturedModel model );

    glm::vec3 getPosition();
    void setPosition( glm::vec3 position );

    glm::vec3 getRotation();
    void setRotation( glm::vec3 rotation );

    glm::vec3 getScale();
    void setScale( GLfloat scale );



};

#endif // ENTITY_HPP