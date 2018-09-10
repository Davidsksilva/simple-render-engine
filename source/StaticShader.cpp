#include "StaticShader.hpp"

StaticShader::StaticShader() : ShaderProgram("source/shaders/vertexShader.glsl","source/shaders/fragmentShader.glsl"){
    createProgram();
}
void StaticShader::bindAttributes(){
    bindAttribute(0, "position");

}