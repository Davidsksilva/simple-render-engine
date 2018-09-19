#include "ShaderProgram.hpp"
#include <glm/gtc/type_ptr.hpp>

std::string readFile( const char* filePath ){
    std::string content;
    std::ifstream fileStream( filePath, std::ios::in );

    // Check if file exists
    if( !fileStream.is_open() ){
        std::cerr << "Could not read file " << filePath << " File does not exist" << std::endl;
        return "";
    }

    std::string line = "";

    // Read fale and store content
    while( !fileStream.eof() ) {
        std::getline( fileStream, line );
        content.append( line + "\n" );
    }

    fileStream.close();
    return content;
}
GLuint ShaderProgram::loadShader( const char* file, GLuint type ){

    GLuint shaderID = glCreateShader( type );
    
    // Retrieve Shader Source
    std::string shaderString= readFile( file );
    const char* shaderSource = shaderString.c_str();

    // Compile Shader
    glShaderSource( shaderID, 1, &shaderSource, NULL );
    glCompileShader( shaderID );

    GLint result = GL_FALSE;
    GLint logLength;

    // Check vertex shader
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &result);
    glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &logLength);
    std::vector <GLchar> vertShaderError((logLength > 1) ? logLength : 1);
    glGetShaderInfoLog(shaderID, logLength, NULL, &vertShaderError[0]);
    std::cout << &vertShaderError[0] << std::endl;

    return shaderID;
}
ShaderProgram::ShaderProgram(const char* vertexFile,const char* fragmentFile){

    //Loading Shaders
    vertexShaderID = loadShader( vertexFile,GL_VERTEX_SHADER );
    fragmentShaderID = loadShader( fragmentFile, GL_FRAGMENT_SHADER );
    
}

void ShaderProgram::createProgram(){

    programID = glCreateProgram();
    glAttachShader( programID, vertexShaderID );
    glAttachShader( programID, fragmentShaderID );
    bindAttributes();
    glLinkProgram(programID);
    glValidateProgram(programID);
    getAllUniformLocations();
}

void ShaderProgram::bindAttribute(GLint attribute, const char* variableName){

    glBindAttribLocation(programID, attribute, variableName);
}

void ShaderProgram::start(){

    glUseProgram(programID);
}

void ShaderProgram::stop(){

    glUseProgram(0);
}

GLuint ShaderProgram::getUniformLocation( std::string uniformName ){

    glGetUniformLocation(programID, uniformName.c_str);
}

void ShaderProgram::loadFloat( GLuint location, GLfloat value ){

    glUniform1f(  location, value );
}

void ShaderProgram::loadVector( GLuint location, glm::vec3 vector){

    glUniform3f( location, vector.x, vector.y, vector.z  );
}

void ShaderProgram::loadBool( GLuint location, bool value ){

    GLfloat to_load = 0.0f;

    value ? to_load = 1.0f : to_load = 0.0f;

    glUniform1f( location, to_load );
}

void ShaderProgram::loadMatrix( GLuint location, glm::mat4 matrix ){

    glUniformMatrix4fv( location, 1, GL_FALSE, glm::value_ptr(matrix));
}

void ShaderProgram::cleanUp(){

    stop();
    glDetachShader( programID, vertexShaderID );
    glDetachShader( programID, fragmentShaderID );
    glDeleteShader( vertexShaderID );
    glDeleteShader( fragmentShaderID );
    glDeleteProgram( programID );
}