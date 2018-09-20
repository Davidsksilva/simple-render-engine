#include "Renderer.hpp"

Renderer::Renderer( StaticShader shader ){

    createProjectionMatrix();
    shader.start();
    shader.loadProjectionMatrix(projectionMatrix);
    shader.stop();
}

void Renderer::prepare(){

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // Set Background Color
    glClearColor(0, 0, 0, 1);
    
}

void Renderer::render( Entity entity, StaticShader  shader ){

    TexturedModel model = entity.getModel();
    RawModel rawModel = model.getRawModel();

    // Bind VAO and VBOS ( Position, Texture)
    glBindVertexArray( rawModel.getVaoID() );
    glEnableVertexAttribArray( 0 );
    glEnableVertexAttribArray( 1 );

    glm::mat4 transformationMatrix = utils::createTransformationMatrix( entity.getPosition(), entity.getRotation(), entity.getScale() );
    shader.loadTransformationMatrix( transformationMatrix );


    glActiveTexture(GL_TEXTURE0);
    glBindTexture( GL_TEXTURE_2D, model.getTexture().getID());
    // Draw Triangles using Index Buffers
    glDrawElements( GL_TRIANGLES, rawModel.getVertexCount(), GL_UNSIGNED_INT, 0 );
    // Disable VBOs
    glDisableVertexAttribArray( 0 );
    glDisableVertexAttribArray( 1 );
    // Unbind VAO
    glBindVertexArray( 0 );

}

void Renderer::createProjectionMatrix(){

    projectionMatrix = glm::perspective( glm::radians( FOV ), (GLfloat) Display::WIDTH / (GLfloat) Display::HEIGHT, NEAR_PLANE, FAR_PLANE );

}