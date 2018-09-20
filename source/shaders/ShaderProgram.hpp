#ifndef SHADER_PROGRAM_HPP
#define SHADER_PROGRAM_HPP

#include "../includes.hpp"


class ShaderProgram{

    protected:

    GLuint m_program_id;
    GLuint m_vertex_shader_id;
    GLuint m_fragment_shader_id;

    GLuint loadShader(const char* t_file, const GLuint t_type);
    void createProgram();

    void bindAttribute( const GLint t_attribute, const char* t_variableName );
    virtual void bindAttributes() = 0;
    
    GLuint getUniformLocation( const char* t_uniformName );
    virtual void getAllUniformLocations() = 0;

    void loadFloat( const GLuint t_location, const GLfloat t_value );
    void loadVector( const GLuint t_location, const glm::vec3 t_vector );
    void loadBool ( const GLuint t_location, const bool t_value );
    void loadMatrix ( const GLuint t_location, const glm::mat4 t_matrix );

    
    public:
    
    void start();
    void stop();
    void cleanUp();
    virtual ~ShaderProgram() = 0;
    ShaderProgram( const char* t_vertexFile ,const char* t_fragmentFile );
        
};

#endif // SHADER_PROGRAM_HPP