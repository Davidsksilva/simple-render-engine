#ifndef LOADER_HPP
#define LOADER_HPP

#include <iostream>
#include "RawModel.hpp"
#include <vector>
#define GLEW_STATIC
#include <GL/glew.h>

class Loader{

    public:

    RawModel loadToVAO( const std::vector<float>& positions );

    void cleanUp();

    private:

    std::vector<GLuint> vaos;
    std::vector<GLuint> vbos;

    GLuint createVAO();

    void storeDataInAttributeList(int attributeNumber, const std::vector<float>& data);

    void unbindVAO();

};

#endif // LOADER_HPP