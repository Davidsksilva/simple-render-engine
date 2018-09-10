#include "ShaderProgram.hpp"

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

void ShaderProgram::cleanUp(){

    stop();
    glDetachShader( programID, vertexShaderID );
    glDetachShader( programID, fragmentShaderID );
    glDeleteShader( vertexShaderID );
    glDeleteShader( fragmentShaderID );
    glDeleteProgram( programID );
}