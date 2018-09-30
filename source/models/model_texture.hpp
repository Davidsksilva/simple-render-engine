#ifndef MODEL_TEXTURE_HPP
#define MODEL_TEXTURE_HPP
#include "../includes/includes.hpp"

class ModelTexture{
    private:

    GLuint m_texture_id;
    GLfloat m_specular_power;
    GLfloat m_specular_intensity;

    public:
    ModelTexture();
    ModelTexture( const GLuint t_id , const GLfloat t_specular_power, const GLfloat t_specular_intensity);

    GLuint getID();

    void setSpecularPower( GLfloat t_value );
    GLfloat getSpecularPower();

    void setSpecularIntensity( GLfloat t_value );
    GLfloat getSpecularIntensity();
};

#endif // MODEL_TEXTURE_HPP