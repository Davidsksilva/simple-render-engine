#include "master_renderer.hpp"

MasterRenderer::MasterRenderer(  StaticShader t_shader, Light& t_light, GLfloat t_r, GLfloat t_g, GLfloat t_b ) 
: m_shader(t_shader), m_renderer (Renderer(t_shader, t_r, t_g, t_b)), m_light(t_light){

    m_renderer.createFBO();
}

void MasterRenderer::render( Light t_light, Camera t_camera ){

    m_renderer.prepare();
    m_shader.start();
    m_shader.loadLight( m_light );
    m_shader.loadViewMatrix(  t_camera );
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
    m_shader.loadViewMatrix(  t_camera );
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
