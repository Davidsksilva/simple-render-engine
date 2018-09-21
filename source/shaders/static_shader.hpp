#ifndef STATIC_SHADER_HPP
#define STATIC_SHADER_HPP
#include "shader_program.hpp"
#include "../includes/utilities.hpp"

class Camera;

class StaticShader : public ShaderProgram{
    
    protected:

    GLuint m_loc_transformation_matrix;
    GLuint m_loc_projection_matrix;
    GLuint m_loc_view_matrix;

    void bindAttributes () override;
    void getAllUniformLocations () override;

    public:
    
    ~StaticShader();
    StaticShader();
    void loadTransformationMatrix( const glm::mat4 t_matrix );
    void loadProjectionMatrix( const glm::mat4 t_matrix );
    void loadViewMatrix ( const Camera t_camera );
};

#endif // STATIC_SHADER_HPP