#include "renderer.hpp"

Renderer::Renderer( StaticShader t_shader, GLfloat t_r, GLfloat t_g, GLfloat t_b  ){

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
    glClearColor(m_background_color.x, m_background_color.y, m_background_color.z, 1);

    glEnable    ( GL_DEPTH_TEST );

    
    
}

void Renderer::clear(){

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // Set Background Color
    glClearColor(1, 1, 1, 1);

    glEnable    ( GL_DEPTH_TEST );


    
}

void Renderer::render( Entity t_entity, StaticShader  t_shader ){

    TexturedModel model = t_entity.getModel();
    RawModel raw_model  = model.getRawModel();

    // Bind VAO and VBOS ( Position, Texture)
    glBindVertexArray(raw_model .getVaoID() );
    glEnableVertexAttribArray( 0 );
    glEnableVertexAttribArray( 1 );
    glEnableVertexAttribArray( 2 );

    glm::mat4 transformationMatrix = utils::createTransformationMatrix( t_entity.getPosition(), t_entity.getRotation(), t_entity.getScale() );
    t_shader.loadTransformationMatrix( transformationMatrix );
    ModelTexture texture = model.getTexture();
    t_shader.loadSpecular(texture);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture( GL_TEXTURE_2D, model.getTexture().getID());
    // Draw Triangles using Index Buffers
    glDrawElements( GL_TRIANGLES,raw_model .getVertexCount(), GL_UNSIGNED_INT, 0 );
    // Disable VBOs
    glDisableVertexAttribArray( 0 );
    glDisableVertexAttribArray( 1 );
    glDisableVertexAttribArray( 2 );
    // Unbind VAO
    glBindVertexArray( 0 );

}

void Renderer::createProjectionMatrix(){

    projectionMatrix = glm::perspective( glm::radians( kFOV ), (GLfloat) Display::kWIDTH / (GLfloat) Display::kHEIGHT, kNEAR_PLANE, kFAR_PLANE );

}

void Renderer::setBackgroundColor ( GLfloat t_r, GLfloat t_g, GLfloat t_b ){

    m_background_color.x = t_r;
    m_background_color.y = t_g;
    m_background_color.z = t_b;
}

GLuint Renderer::createFBO(){

     GLuint fbo_id;
     glGenFramebuffers(1, &fbo_id);
     glBindFramebuffer( GL_FRAMEBUFFER, fbo_id );

    

     GLuint texture;
     glGenTextures(1,&texture);
     glBindTexture( GL_TEXTURE_2D, texture );

    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, 512, 512,0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

     glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
     glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
     /*glTexImage2D( 
        GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, 512, 512, 0, 
        GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, NULL
        );*/
    //glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, texture, 0);
    glFramebufferTexture2D( GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);
    GLuint rbo;
    glGenRenderbuffers(1, &rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, rbo);
    glRenderbufferStorage( GL_RENDERBUFFER, GL_DEPTH_STENCIL, 512, 512);
    glBindRenderbuffer(GL_RENDERBUFFER,0);
    glFramebufferRenderbuffer( GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);

    fbo_texture = texture;
    m_fbo = fbo_id;
 }

 void Renderer:: bindFBO(){

     glBindFramebuffer( GL_FRAMEBUFFER, m_fbo);
 }

 void Renderer::unbindFBO(){

     glBindFramebuffer(GL_FRAMEBUFFER, 0);
 }

 void Renderer::deleteFBO(){

     glDeleteFramebuffers(1, &m_fbo);
 }

    