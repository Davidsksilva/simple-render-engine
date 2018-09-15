#include "ModelTexture.hpp"

ModelTexture::ModelTexture( GLuint id ){
    this->textureID = id;
}
ModelTexture::ModelTexture() : textureID ( 0 ){

}
GLuint ModelTexture::getID(){
    return this->textureID;
}