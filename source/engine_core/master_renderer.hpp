#ifndef MASTER_RENDERER_HPP
#define MASTER_RENDERER_HPP

#include "../includes/includes.hpp"
#include "../shaders/static_shader.hpp"
#include "../models/textured_model.hpp"
#include "../entities/entity.hpp"
#include "light.hpp"
#include "camera.hpp"
#include "entity_renderer.hpp"
#include "terrain_renderer.hpp"
#include <map>

class MasterRenderer{

    private:

    constexpr static GLfloat kFOV = 100.0f;
    constexpr static GLfloat kNEAR_PLANE = 0.01f;
    constexpr static GLfloat kFAR_PLANE = 1000.0f;

    StaticShader m_shader;
    TerrainShader m_terrain_shader;
    EntityRenderer m_entity_renderer;
    TerrainRenderer m_terrain_renderer;

    Light& m_light;
    Camera& m_camera;
    GLuint m_display_height;
    GLuint m_display_width;
    std::map < TexturedModel, std::vector< Entity >> m_entities;
    std::vector <Terrain> m_terrains;
    glm::mat4 m_projection_matrix;
    GLuint fbo_texture;
    GLuint m_fbo;
    GLuint m_rbo;
  
    public:

    MasterRenderer( StaticShader t_shader,Light& t_light,Camera& t_camera,  GLfloat t_r, GLfloat t_g, GLfloat t_b );
    void createProjectionMatrix();
    void render( Light p_light, Camera p_camera );
    void renderFBO( Light p_light, Camera p_camera );
    void processEntity( const Entity p_entity );
    void processTerrain(const Terrain p_terrain);
    void setBackgroundColor( GLfloat p_r, GLfloat p_g, GLfloat p_b );
    void setLightIntensity( GLfloat p_value );
    void setLightColor( glm::vec3 p_value );
    void setLightPosition( glm::vec3 p_position);
    glm::vec3 getLightPosition();
    glm::vec3 getCameraPosition();
    void setCameraPosition( glm::vec3 p_position );
    GLfloat getCameraPitch();
    void setCameraPitch( GLfloat p_pitch );
    GLfloat getCameraYaw();
    void setCameraYaw( GLfloat p_yaw );
    void prepare();
    void cleanUp();
    GLuint getTextureFBO();
    GLuint createFBO();
    void bindFBO();
    void unbindFBO();
    void deleteFBO();

};

#endif //MASTER_RENDERER_HPP
