#include "Renderer.hpp"

void Renderer::prepare(){

    glClearColor(1, 0, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::render(RawModel model){

    glBindVertexArray(model.getVaoID());
    glEnableVertexAttribArray(0);
    glDrawArrays(GL_TRIANGLES,0,model.getVertexCount());
    glDisableVertexAttribArray(0);
    glBindVertexArray(0);

}