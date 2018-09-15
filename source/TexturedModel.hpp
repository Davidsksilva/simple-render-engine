#ifndef TEXTURED_MODEL_HPP
#define TEXTURED_MODEL_HPP

#include "includes.hpp"
#include "ModelTexture.hpp"
#include "RawModel.hpp"

class TexturedModel{

    private:

    RawModel rawModel;
    ModelTexture texture;

    public:

    TexturedModel();
    TexturedModel( RawModel model, ModelTexture texture );

    RawModel getRawModel();
    ModelTexture getTexture();

};

#endif // TEXTURED_MODEL_HPP