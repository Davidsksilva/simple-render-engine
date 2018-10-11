#ifndef MASTER_RENDERER_HPP
#define MASTER_RENDERER_HPP

#include "../includes/includes.hpp"
#include "../shaders/static_shader.hpp"
#include "../models/textured_model.hpp"
#include "../entities/entity.hpp"
#include "light.hpp"
#include "camera.hpp"

#include "renderer.hpp"
#include <map>

class MasterRenderer{

    private:

    StaticShader m_shader;
    Renderer m_renderer;
    Light& m_light;
    Camera& m_camera;
    GLuint m_display_height;
    GLuint m_display_width;
    std::map < TexturedModel, std::vector< Entity >> m_entities;

    public:

    MasterRenderer( StaticShader t_shader,Light& t_light,Camera& t_camera,  GLfloat t_r, GLfloat t_g, GLfloat t_b );
    void render( Light t_light, Camera t_camera );
    void renderFBO( Light t_light, Camera t_camera );
    void processEntity( const Entity t_entity );
    void setBackgroundColor( GLfloat t_r, GLfloat t_g, GLfloat t_b );
    void setLightIntensity( GLfloat t_value );
    void setLightColor( glm::vec3 t_value );
    void setLightPosition( glm::vec3 t_position);
    glm::vec3 getLightPosition();
    glm::vec3 getCameraPosition();
    void setCameraPosition( glm::vec3 t_position );
    GLfloat getCameraPitch();
    void setCameraPitch( GLfloat t_pitch );
    GLfloat getCameraYaw();
    void setCameraYaw( GLfloat t_yaw );
    
    void cleanUp();
    GLuint getTextureFBO();

};

#endif //MASTER_RENDERER_HPP
