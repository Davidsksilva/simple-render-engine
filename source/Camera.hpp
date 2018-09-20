#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "includes.hpp"

class Camera {

    private:

    glm::vec3 position;
    GLfloat pitch;
    GLfloat yaw;
    GLfloat roll;

    public: 

    Camera();
    void move();

    glm::vec3 getPosition();
    GLfloat getPitch();
    GLfloat getYaw();

};

#endif // CAMERA_HPP