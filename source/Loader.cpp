#include "Loader.hpp"

RawModel Loader::loadToVAO(const std::vector<float>& positions ){
    GLuint vaoID = createVAO();
    storeDataInAttributeList( 0, positions );
    unbindVAO();
    return RawModel( vaoID, positions.size()/3 );
}

void Loader::cleanUp(){
    for(unsigned int i = 0; i < vaos.size(); i++ )
        glDeleteVertexArrays(1,&vaos[i]);
    for(unsigned int i = 0; i < vbos.size(); i++)
        glDeleteBuffers(1,&vbos[i]);
}

GLuint Loader::createVAO(){
    // Create VAO
    GLuint vaoID;
    vaos.push_back(vaoID);
    glGenVertexArrays(1, &vaoID);
    glBindVertexArray(vaoID);
    return vaoID;
}

void Loader::storeDataInAttributeList(int attributeNumber, const std::vector<float>& data){
    // Store data in VBO
    GLuint vboID;
    glGenBuffers(1,&vboID);
    vbos.push_back(vboID);
    glBindBuffer(GL_ARRAY_BUFFER,vboID);
    glBufferData(GL_ARRAY_BUFFER,data.size() * sizeof ( data.at( 0 ) ),data.data(),GL_STATIC_DRAW);
    glVertexAttribPointer(attributeNumber,3,GL_FLOAT,false,0,0);
    //glEnableVertexAttribArray(  attributeNumber );
    glBindBuffer(GL_ARRAY_BUFFER,0);
}

void Loader::unbindVAO(){
    glBindVertexArray(0);
}

