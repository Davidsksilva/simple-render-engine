#include "Renderer.hpp"

void Renderer::prepare(){

    // Clear Color Buffer
    glClear(GL_COLOR_BUFFER_BIT);
    // Set Background Color
    glClearColor(0, 0, 0, 1);
    
}

void Renderer::render( TexturedModel texturedModel ){
    RawModel model = texturedModel.getRawModel();
    // Bind VAO
    glBindVertexArray( model.getVaoID() );
    // Enable VBO - Positions
    glEnableVertexAttribArray( 0 );
    // Eanble VBO - Textures
    glEnableVertexAttribArray( 1 );
    glActiveTexture(GL_TEXTURE0);
    glBindTexture( GL_TEXTURE_2D, texturedModel.getTexture().getID());
    // Draw Triangles using Index Buffers
    glDrawElements( GL_TRIANGLES, model.getVertexCount(), GL_UNSIGNED_INT, 0 );
    // Disable VBOs
    glDisableVertexAttribArray( 0 );
    glDisableVertexAttribArray( 1 );
    // Unbind VAO
    glBindVertexArray( 0 );

}