#include "includes.hpp"


class ShaderProgram{

    protected:

    GLuint programID;
    GLuint vertexShaderID;
    GLuint  fragmentShaderID;

    GLuint loadShader(const char* file, GLuint type);
    void createProgram();

    void bindAttribute( GLint attribute, const char* variableName );
    virtual void bindAttributes() = 0;
    
    GLuint getUniformLocation( std::string uniformName );
    virtual void getAllUniformLocations() = 0;

    void loadFloat( GLuint location, GLfloat value );
    void loadVector( GLuint location, glm::vec3 vector );
    void loadBool ( GLuint location, bool value );
    void loadMatrix ( GLuint location, glm::mat4 matrix );

    public:
    
    void  start();
    void stop();
    void cleanUp();
    ShaderProgram(const char* vertexFile,const char* fragmentFile);
        
};