#ifndef TERRAIN_SHADER_HPP
#define TERRAIN_SHADER_HPP

#include "shader_program.hpp"
#include "../includes/utilities.hpp"
#include "../engine_core/light.hpp"
#include "../models/model_texture.hpp"

class TerrainShader : public ShaderProgram{

    protected:

    GLuint m_loc_transformation_matrix;
    GLuint m_loc_projection_matrix;
    GLuint m_loc_view_matrix;
    GLuint m_loc_light_position;
    GLuint m_loc_light_color;
    GLuint m_loc_light_intensity;
    GLuint m_loc_specular_power;
    GLuint m_loc_specular_intensity;

    void bindAttributes () override;
    void getAllUniformLocations () override;

    public:
    
    ~TerrainShader();
    TerrainShader();

    void loadTransformationMatrix( const glm::mat4 p_matrix );
    void loadProjectionMatrix( const glm::mat4 p_matrix );
    void loadViewMatrix ( const Camera p_camera );
    void loadLight( Light p_light );
    void loadSpecular( ModelTexture p_model_texture );

};
#endif // TERRAIN_SHADER_HPP