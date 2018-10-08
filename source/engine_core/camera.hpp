#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "../includes/includes.hpp"

class Camera {

    private:

    glm::vec3 m_position;
    GLfloat m_pitch;
    GLfloat m_yaw;
    GLfloat m_roll;

    public: 

    Camera();
    void move();

    glm::vec3 getPosition();
    GLfloat getPitch();
    GLfloat getYaw();
    void setPosition( glm::vec3 t_position );
    void setPitch( GLfloat t_value );
    void setYaw( GLfloat t_value );

};

#endif // CAMERA_HPP