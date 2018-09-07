#include "Renderer.hpp"

void Renderer::prepare(){

    // Clear Color Buffer
    glClear(GL_COLOR_BUFFER_BIT);
    // Set Background Color
    glClearColor(1, 0, 1, 1);
    
}

void Renderer::render( RawModel model ){

    // Bind VAO
    glBindVertexArray( model.getVaoID() );
    // Enable VBO
    glEnableVertexAttribArray( 0 );
    // Draw Triangles using Index Buffers
    glDrawElements( GL_TRIANGLES, model.getVertexCount(), GL_UNSIGNED_INT, 0 );
    // Disable VBO
    glDisableVertexAttribArray( 0 );
    // Unbind VAO
    glBindVertexArray( 0 );

}