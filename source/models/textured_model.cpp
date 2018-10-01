#include "textured_model.hpp"

TexturedModel::TexturedModel() : m_raw_model(RawModel()), m_texture(ModelTexture()){

}
TexturedModel::TexturedModel( const RawModel t_model, const ModelTexture t_texture ){

    m_raw_model = t_model;
    m_texture = t_texture;
}

RawModel TexturedModel::getRawModel() const {

    return m_raw_model;
}

ModelTexture TexturedModel::getTexture() const{

    return m_texture;
}