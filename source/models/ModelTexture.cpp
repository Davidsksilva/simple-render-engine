#include "ModelTexture.hpp"

ModelTexture::ModelTexture( const GLuint t_id ){
    
    m_texture_id = t_id;
}
ModelTexture::ModelTexture() : m_texture_id ( 0 ){

}
GLuint ModelTexture::getID(){

    return m_texture_id;
}