#include "master_renderer.hpp"

MasterRenderer::MasterRenderer(  StaticShader t_shader, Light& t_light, Camera& t_camera, GLfloat t_r, GLfloat t_g, GLfloat t_b ) 
: m_shader(t_shader), m_renderer (Renderer(t_shader, t_r, t_g, t_b)), m_light(t_light), m_camera(t_camera){

    m_renderer.createFBO();
}

void MasterRenderer::render( Light t_light, Camera t_camera ){

    m_renderer.prepare();
    m_shader.start();
    m_shader.loadLight( m_light );
    m_shader.loadViewMatrix(  m_camera );
    m_renderer.render(m_entities);
    m_shader.stop();
    m_entities.clear();
}

void MasterRenderer::renderFBO( Light t_light, Camera t_camera ){

    m_renderer.clear();
    m_renderer.bindFBO();
    m_renderer.prepare();
    m_shader.start();
    m_shader.loadLight( m_light );
    m_shader.loadViewMatrix(  m_camera );
    m_renderer.render(m_entities);
    m_renderer.unbindFBO();
    m_shader.stop();
    m_entities.clear();

}

void MasterRenderer::setLightIntensity( GLfloat t_value ){

    m_light.setIntensity(t_value);
}

void MasterRenderer::setLightColor( glm::vec3 t_value ){

    m_light.setColor(t_value);
}
GLuint MasterRenderer::getTextureFBO(){

    return m_renderer.fbo_texture;
}


void MasterRenderer::processEntity( const Entity t_entity ){

    auto model = t_entity.getModel();

    if (m_entities.count(model)){

        m_entities[model].push_back( t_entity);
    }
    else{
        std::vector < Entity > new_batch;
        new_batch.push_back( t_entity );
        m_entities[ model ] = new_batch;
    }
}

void MasterRenderer::cleanUp(){

    m_shader.cleanUp();
    m_renderer.deleteFBO();
}

void MasterRenderer::setBackgroundColor ( GLfloat t_r, GLfloat t_g, GLfloat t_b ){

    m_renderer.setBackgroundColor(t_r,t_g,t_b);
}

glm::vec3 MasterRenderer::getCameraPosition(){

    return m_camera.getPosition();
}

void MasterRenderer::setCameraPosition( glm::vec3 t_position ){

    m_camera.setPosition(t_position);
}

GLfloat MasterRenderer::getCameraPitch(){

    return m_camera.getPitch();
}

void MasterRenderer::setCameraPitch( GLfloat t_pitch ){

    m_camera.setPitch(t_pitch);
}

GLfloat MasterRenderer::getCameraYaw(){

    return m_camera.getYaw();
}

void MasterRenderer::setCameraYaw( GLfloat t_yaw ){

    m_camera.setYaw(t_yaw);
}

void MasterRenderer::setLightPosition( glm::vec3 t_position){

    m_light.setPosition(t_position);
}

glm::vec3 MasterRenderer::getLightPosition(){

    return m_light.getPosition();
}
void MasterRenderer::setDisplayHeight ( GLuint t_value){

	m_display_height = t_value;
}
GLuint MasterRenderer::getDisplayHeight(){

	return m_display_height;
}
void MasterRenderer::setDisplayWidth (GLuint t_value){

	m_display_width = t_value;
}
GLuint MasterRenderer::getDisplayWidth (){

	return m_display_width;
}

