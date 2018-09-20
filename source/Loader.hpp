#ifndef LOADER_HPP
#define LOADER_HPP

#include "includes.hpp"
#include "models/RawModel.hpp"



class Loader{

    public:

    RawModel loadToVAO( const std::vector<GLfloat>& positions, const std::vector<GLuint>& indices, const std::vector<GLfloat>& textureCoords);

    GLuint loadTexture(std::string fileName);

    void cleanUp();

    private:

    std::vector<GLuint> vaos;
    std::vector<GLuint> vbos;
    std::vector<GLuint> textures;

    GLuint createVAO();

    void storeDataInAttributeList( int attributeNumber, GLuint size, const std::vector<GLfloat>& data );

    void unbindVAO();

    void bindIndicesBuffer( std::vector<GLuint> indices );

};

#endif // LOADER_HPP