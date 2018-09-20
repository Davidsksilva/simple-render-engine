#ifndef MODEL_TEXTURE_HPP
#define MODEL_TEXTURE_HPP
#include "../includes.hpp"

class ModelTexture{
    private:

    GLuint m_texture_id;

    public:
    ModelTexture();
    ModelTexture( const GLuint t_id );
    GLuint getID();
};

#endif // MODEL_TEXTURE_HPP