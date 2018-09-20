#include "ShaderProgram.hpp"
#include <glm/gtc/type_ptr.hpp>
#include "../includes/utilities.hpp"


GLuint ShaderProgram::loadShader( const char* t_file, const GLuint t_type ){

    GLuint shader_id = glCreateShader( t_type );
    
    // Retrieve Shader Source
    std::string shader_string = utils::readFile( t_file );
    const char* shader_source = shader_string .c_str();

    // Compile Shader
    glShaderSource( shader_id, 1, &shader_source, NULL );
    glCompileShader( shader_id );

    GLint result = GL_FALSE;
    GLint log_length;

    // Check vertex shader
    glGetShaderiv(shader_id, GL_COMPILE_STATUS, &result);
    glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &log_length);
    std::vector <GLchar> vertShaderError((log_length > 1) ? log_length : 1);
    glGetShaderInfoLog(shader_id, log_length, NULL, &vertShaderError[0]);
    std::cout << &vertShaderError[0] << std::endl;

    return shader_id;
}

ShaderProgram::ShaderProgram( const char* t_vertexFile, const char* t_fragmentFile ){

    //Loading Shaders
    m_vertex_shader_id = loadShader( t_vertexFile,GL_VERTEX_SHADER );
    m_fragment_shader_id = loadShader( t_fragmentFile, GL_FRAGMENT_SHADER );
    
}

ShaderProgram::~ShaderProgram(){

}

void ShaderProgram::createProgram(){

    m_program_id = glCreateProgram();
    glAttachShader( m_program_id, m_vertex_shader_id );
    glAttachShader( m_program_id, m_fragment_shader_id );
    bindAttributes();
    glLinkProgram( m_program_id );
    glValidateProgram( m_program_id );
    getAllUniformLocations();
}

void ShaderProgram::bindAttribute( const GLint t_attribute, const char* t_variable_name ){

    glBindAttribLocation(m_program_id, t_attribute, t_variable_name);
}

void ShaderProgram::start(){

    glUseProgram( m_program_id );
}

void ShaderProgram::stop(){

    glUseProgram (0 );
}

GLuint ShaderProgram::getUniformLocation( const char* t_uniform_name ){

    return glGetUniformLocation( m_program_id, t_uniform_name );
}

void ShaderProgram::loadFloat( const GLuint t_location, const GLfloat t_value ){

    glUniform1f( t_location, t_value );
}

void ShaderProgram::loadVector( const GLuint t_location, const glm::vec3 t_vector){

    glUniform3f( t_location, t_vector.x, t_vector.y, t_vector.z  );
}

void ShaderProgram::loadBool( const GLuint t_location, const bool t_value ){

    GLfloat to_load = 0.0f;

    t_value ? to_load = 1.0f : to_load = 0.0f;

    glUniform1f( t_location, to_load );
}

void ShaderProgram::loadMatrix( const GLuint t_location, const glm::mat4 t_matrix ){

    glUniformMatrix4fv( t_location, 1, GL_FALSE, glm::value_ptr(t_matrix));
}

void ShaderProgram::cleanUp(){

    stop();
    glDetachShader( m_program_id, m_vertex_shader_id );
    glDetachShader( m_program_id, m_fragment_shader_id );
    glDeleteShader( m_vertex_shader_id );
    glDeleteShader( m_fragment_shader_id );
    glDeleteProgram( m_program_id );
}