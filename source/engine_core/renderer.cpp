#include "renderer.hpp"

Renderer::Renderer( StaticShader t_shader, GLfloat t_r, GLfloat t_g, GLfloat t_b  ){

    m_shader = t_shader;
    m_background_color.x = t_r;
    m_background_color.y = t_g;
    m_background_color.z = t_b;
    createProjectionMatrix();
    t_shader.start();
    t_shader.loadProjectionMatrix(projectionMatrix);
    t_shader.stop();
}

void Renderer::prepare(){

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // Set Background Color
    
    glClearColor(1, 1, 1, 1);
    glEnable    ( GL_DEPTH_TEST );

}

void Renderer::clear(){

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // Set Background Color
    glClearColor(m_background_color.x, m_background_color.y, m_background_color.z, 1);

    glEnable    ( GL_DEPTH_TEST );

}

void Renderer::createProjectionMatrix(){

    projectionMatrix = glm::perspective( glm::radians( kFOV ), (GLfloat) Display::kWIDTH / (GLfloat) Display::kHEIGHT, kNEAR_PLANE, kFAR_PLANE );

}

void Renderer::setBackgroundColor ( GLfloat t_r, GLfloat t_g, GLfloat t_b ){

    m_background_color.x = t_r;
    m_background_color.y = t_g;
    m_background_color.z = t_b;
}

void Renderer::render( std::map< TexturedModel, std::vector < Entity>> t_entities ){

    for( auto const& [model, entities] : t_entities){

        prepareTexturedModel(model);
        for( Entity entity : entities){
            prepareInstance(entity);
            glDrawElements( GL_TRIANGLES,model.getRawModel().getVertexCount(), GL_UNSIGNED_INT, 0 );
        }
        unbindTexturedModel();
    }

}

void Renderer::prepareTexturedModel ( TexturedModel t_model ){

    RawModel raw_model  = t_model.getRawModel();

    // Bind VAO and VBOS ( Position, Texture)
    glBindVertexArray(raw_model .getVaoID() );
    glEnableVertexAttribArray( 0 );
    glEnableVertexAttribArray( 1 );
    glEnableVertexAttribArray( 2 );
    ModelTexture texture = t_model.getTexture();
    m_shader.loadSpecular(texture);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture( GL_TEXTURE_2D, t_model.getTexture().getID());
}

void Renderer::unbindTexturedModel(){

    // Disable VBOs
    glDisableVertexAttribArray( 0 );
    glDisableVertexAttribArray( 1 );
    glDisableVertexAttribArray( 2 );
    // Unbind VAO
    glBindVertexArray( 0 );

}

void Renderer::prepareInstance( Entity t_entity){

    glm::mat4 transformationMatrix = utils::createTransformationMatrix( t_entity.getPosition(), t_entity.getRotation(), t_entity.getScale() );
    m_shader.loadTransformationMatrix( transformationMatrix );
}
GLuint Renderer::createFBO(){
    
    GLuint fbo;
    glGenFramebuffers(1, &fbo);
    glBindFramebuffer( GL_FRAMEBUFFER, fbo );

    

    GLuint texture;
    glGenTextures(1,&texture);
    glBindTexture( GL_TEXTURE_2D, texture );

    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, 1121, 687,0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glFramebufferTexture2D( GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);
    GLuint rbo;
    glGenRenderbuffers(1, &rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, rbo);
    glRenderbufferStorage( GL_RENDERBUFFER, GL_DEPTH_STENCIL, 1121, 687);
    glBindRenderbuffer(GL_RENDERBUFFER,0);
    glFramebufferRenderbuffer( GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);

    fbo_texture = texture;
    m_fbo = fbo;
    m_rbo = rbo;
 }

 void Renderer:: bindFBO(){

     glBindFramebuffer( GL_FRAMEBUFFER, m_fbo);
 }

 void Renderer::unbindFBO(){

     glBindFramebuffer(GL_FRAMEBUFFER, 0);
 }

 void Renderer::deleteFBO(){

     glDeleteFramebuffers(1, &m_fbo);
     glDeleteRenderbuffers(1, &m_rbo);
 }

    
