#ifndef RAWLODEL_HPP
#define RAWLODEL_HPP

#include <iostream>
#include "includes.hpp"

class RawModel{
    private:
    GLuint vaoID, vertexCount;

    public:
    RawModel(GLuint vaoID, GLuint vertexCount){
        this->vaoID = vaoID;
        this->vertexCount = vertexCount;
    };

    GLuint getVaoID(){
        return  vaoID;
    }

    GLuint getVertexCount(){
        return vertexCount;
    }

};

#endif // RAWLODEL_HPP