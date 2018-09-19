#include "StaticShader.hpp"

StaticShader::StaticShader() : ShaderProgram("source/shaders/vertexShader.glsl","source/shaders/fragmentShader.glsl"){

    createProgram();
}
void StaticShader::bindAttributes(){

    bindAttribute(0, "position");
    bindAttribute(1, "textureCoords");

}

void StaticShader::getAllUniformLocations(){

    loc_transformationMatrix = getUniformLocation( "transformationMatrix" );
}

void StaticShader::loadTransformationMatrix( glm::mat4 matrix ){

    loadMatrix( loc_transformationMatrix, matrix );
}