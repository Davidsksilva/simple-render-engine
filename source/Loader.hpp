#ifndef LOADER_HPP
#define LOADER_HPP

#include <iostream>
#include "RawModel.hpp"
#include <vector>
#define GLEW_STATIC
#include <GL/glew.h>

class Loader{

    public:

    RawModel loadToVAO( const std::vector<GLfloat>& positions, const std::vector<GLuint>& indices );

    void cleanUp();

    private:

    std::vector<GLuint> vaos;
    std::vector<GLuint> vbos;

    GLuint createVAO();

    void storeDataInAttributeList( int attributeNumber, const std::vector<GLfloat>& data );

    void unbindVAO();

    void bindIndicesBuffer( std::vector<GLuint> indices );

};

#endif // LOADER_HPP