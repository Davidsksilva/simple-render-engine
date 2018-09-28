#ifndef LIGHT_HPP
#define LIGHT_HPP

#include "../includes/includes.hpp"

class Light{

    private:

    glm::vec3 m_position;
    glm::vec3 m_color;

    public:

    Light( glm::vec3 t_position, glm::vec3 t_colour );

    void setColor( glm::vec3 t_value );
    glm::vec3 getColor();

    void setPosition( glm::vec3 t_value );
    glm::vec3 getPosition();
};


#endif // LIGHT_HPP