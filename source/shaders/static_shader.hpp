#ifndef STATIC_SHADER_HPP
#define STATIC_SHADER_HPP
#include "shader_program.hpp"
#include "../includes/utilities.hpp"
#include "../engine_core/light.hpp"

class Camera;


class StaticShader : public ShaderProgram{
    
    protected:

    GLuint m_loc_transformation_matrix;
    GLuint m_loc_projection_matrix;
    GLuint m_loc_view_matrix;
    GLuint m_loc_light_position;
    GLuint m_loc_light_color;

    void bindAttributes () override;
    void getAllUniformLocations () override;

    public:
    
    ~StaticShader();
    StaticShader();

    void loadTransformationMatrix( const glm::mat4 t_matrix );
    void loadProjectionMatrix( const glm::mat4 t_matrix );
    void loadViewMatrix ( const Camera t_camera );
    void loadLight( Light t_light );
};

#endif // STATIC_SHADER_HPP