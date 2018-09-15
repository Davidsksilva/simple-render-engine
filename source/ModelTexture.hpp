#ifndef MODEL_TEXTURE_HPP
#define MODEL_TEXTURE_HPP
#include "includes.hpp"

class ModelTexture{
    private:

    GLuint textureID;

    

    public:
    ModelTexture();
    ModelTexture( GLuint id );
    GLuint getID();
};

#endif // MODEL_TEXTURE_HPP