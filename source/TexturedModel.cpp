#include "TexturedModel.hpp"

TexturedModel::TexturedModel( RawModel model, ModelTexture texture ){

    this->rawModel = model;
    this->texture = texture;
}

RawModel TexturedModel::getRawModel(){

    return this->rawModel;
}

ModelTexture TexturedModel::getTexture(){

    return this->texture;
}