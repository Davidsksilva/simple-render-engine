#ifndef TEXTURED_MODEL_HPP
#define TEXTURED_MODEL_HPP

#include "../includes/includes.hpp"
#include "model_texture.hpp"
#include "raw_model.hpp"

class TexturedModel{

    private:

    RawModel m_raw_model;
    ModelTexture m_texture;

    public:

    TexturedModel();
    TexturedModel( const RawModel t_model, const ModelTexture t_texture );

    RawModel getRawModel();
    ModelTexture getTexture();

};

#endif // TEXTURED_MODEL_HPP