#include "master_renderer.hpp"

MasterRenderer::MasterRenderer(  StaticShader p_shader, Light& p_light, Camera& p_camera, GLfloat p_r, GLfloat p_g, GLfloat p_b )
                                : m_light(p_light),m_camera(p_camera){

    m_shader = StaticShader();
    m_terrain_shader = TerrainShader();
    createProjectionMatrix();
    m_entity_renderer = EntityRenderer(m_shader, p_r, p_g, p_b, m_projection_matrix);
    m_terrain_renderer = TerrainRenderer(m_terrain_shader,m_projection_matrix);
    //m_entity_renderer.createFBO();
    createFBO();
}

void MasterRenderer::render( Light p_light, Camera p_camera ){

    prepare();
    m_shader.start();
    m_shader.loadLight( m_light );
    m_shader.loadViewMatrix(  m_camera );
    m_entity_renderer.render(m_entities);
    m_shader.stop();
    m_entities.clear();
}

void MasterRenderer::renderFBO( Light p_light, Camera p_camera ){

    m_entity_renderer.clear();
   // m_terrain_renderer.clear();
    bindFBO();
    prepare();
    m_shader.start();
    m_shader.loadLight( m_light );
    m_shader.loadViewMatrix(  m_camera );
    m_entity_renderer.render(m_entities);
    m_shader.stop();
    m_terrain_shader.start();
    m_terrain_shader.loadLight(m_light);
    m_terrain_shader.loadViewMatrix(m_camera);
    m_terrain_renderer.render(m_terrains);
    m_terrain_shader.stop();
    unbindFBO();
    m_entities.clear();
    m_terrains.clear();
    

}

void MasterRenderer::processTerrain(const Terrain p_terrain){

    m_terrains.push_back(p_terrain);
}
void MasterRenderer::setLightIntensity( GLfloat p_value ){

    m_light.setIntensity(p_value);
}

void MasterRenderer::setLightColor( glm::vec3 p_value ){

    m_light.setColor(p_value);
}
GLuint MasterRenderer::getTextureFBO(){

    return fbo_texture;
}


void MasterRenderer::processEntity( const Entity p_entity ){

    auto model = p_entity.getModel();

    if (m_entities.count(model)){

        m_entities[model].push_back( p_entity);
    }
    else{
        std::vector < Entity > new_batch;
        new_batch.push_back( p_entity );
        m_entities[ model ] = new_batch;
    }
}

void MasterRenderer::cleanUp(){

    m_shader.cleanUp();
    m_terrain_shader.cleanUp();
    deleteFBO();
    
}

void MasterRenderer::prepare(){

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // Set Background Color
    
    glClearColor(1, 1, 1, 1);
    glEnable    ( GL_DEPTH_TEST );

}

void MasterRenderer::createProjectionMatrix(){

    m_projection_matrix = glm::perspective( glm::radians( kFOV ), (GLfloat) Display::kWIDTH / (GLfloat) Display::kHEIGHT, kNEAR_PLANE, kFAR_PLANE );
}

void MasterRenderer::setBackgroundColor ( GLfloat p_r, GLfloat p_g, GLfloat p_b ){

    m_entity_renderer.setBackgroundColor(p_r,p_g,p_b);
}

glm::vec3 MasterRenderer::getCameraPosition(){

    return m_camera.getPosition();
}

void MasterRenderer::setCameraPosition( glm::vec3 p_position ){

    m_camera.setPosition(p_position);
}

GLfloat MasterRenderer::getCameraPitch(){

    return m_camera.getPitch();
}

void MasterRenderer::setCameraPitch( GLfloat p_pitch ){

    m_camera.setPitch(p_pitch);
}

GLfloat MasterRenderer::getCameraYaw(){

    return m_camera.getYaw();
}

void MasterRenderer::setCameraYaw( GLfloat p_yaw ){

    m_camera.setYaw(p_yaw);
}

void MasterRenderer::setLightPosition( glm::vec3 p_position){

    m_light.setPosition(p_position);
}

glm::vec3 MasterRenderer::getLightPosition(){

    return m_light.getPosition();
}

GLuint MasterRenderer::createFBO(){
    
    GLuint fbo;
    glGenFramebuffers(1, &fbo);
    glBindFramebuffer( GL_FRAMEBUFFER, fbo );
    GLuint texture;
    glGenTextures(1,&texture);
    glBindTexture( GL_TEXTURE_2D, texture );

    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, Display::kWIDTH, Display::kHEIGHT,0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glFramebufferTexture2D( GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);
    GLuint rbo;
    glGenRenderbuffers(1, &rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, rbo);
    glRenderbufferStorage( GL_RENDERBUFFER, GL_DEPTH_STENCIL, Display::kWIDTH, Display::kHEIGHT);
    glBindRenderbuffer(GL_RENDERBUFFER,0);
    glFramebufferRenderbuffer( GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);

    fbo_texture = texture;
    m_fbo = fbo;
    m_rbo = rbo;
 }

 void MasterRenderer::bindFBO(){

     glBindFramebuffer( GL_FRAMEBUFFER, m_fbo);
 }

 void MasterRenderer::unbindFBO(){

     glBindFramebuffer(GL_FRAMEBUFFER, 0);
 }

 void MasterRenderer::deleteFBO(){

     glDeleteFramebuffers(1, &m_fbo);
     glDeleteRenderbuffers(1, &m_rbo);
 }

