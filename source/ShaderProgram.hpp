#include "includes.hpp"


class ShaderProgram{

    protected:

    GLuint programID;
    GLuint vertexShaderID;
    GLuint  fragmentShaderID;

    GLuint loadShader(const char* file, GLuint type);

    void bindAttribute(GLint attribute, const char* variableName);
    virtual void bindAttributes() = 0;
    void createProgram();
    
    public:
    
    void  start();
    void stop();
    void cleanUp();
    ShaderProgram(const char* vertexFile,const char* fragmentFile);
        
};