#ifndef RAWLODEL_HPP
#define RAWLODEL_HPP

#include "includes.hpp"

class RawModel{
    private:
    // Declaring ID of model VAO and the vertex count
    GLuint vaoID, vertexCount;

    public:
    RawModel( GLuint vaoID, GLuint vertexCount ){
        // Set inicial attributes
        this->vaoID = vaoID;
        this->vertexCount = vertexCount;
    };

    GLuint getVaoID(){
        // VAO ID getter
        return  vaoID;
    }

    GLuint getVertexCount(){
        // Vertex Count getter
        return vertexCount;
    }

};

#endif // RAWLODEL_HPP