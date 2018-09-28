#include "renderer.hpp"

Renderer::Renderer( StaticShader t_shader ){

    createProjectionMatrix();
    t_shader.start();
    t_shader.loadProjectionMatrix(projectionMatrix);
    t_shader.stop();
}

void Renderer::prepare(){

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // Set Background Color
    glClearColor(1, 1, 1, 1);
    
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