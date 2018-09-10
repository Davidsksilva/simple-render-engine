#include "Display.hpp"
#include "includes.hpp"
#include "Loader.hpp"
#include "Renderer.hpp"
#include "StaticShader.hpp"
 
int main(int argc, char** argv)
{
    // Create Display
    Display::create();
    // Cleearing display with white color
    Display::clear(1.0, 1.0, 1.0);
    // Create loader object
    Loader loader = Loader();
    // Create renderer object
    Renderer renderer = Renderer();
    // Create Shader
    StaticShader shader = StaticShader();

    std::vector<GLfloat>vertices = {
        -0.5f,0.5f,0.0f,
        -0.5f,-0.5f,0.0f,
        0.5f,-0.5,0.0f,
        0.5,0.5f,0.0f
    };

    std::vector<GLuint>indices = {
        0,1,3,
        3,1,2
    };

    RawModel model = loader.loadToVAO( vertices, indices );

    // While the window is open
    while(Display::isOpen()){
        // Prepare renderer
        renderer.prepare();
        shader.start();
        renderer.render(model);
        shader.stop();
        // Update display
        Display::update();
        // Check for close event
        Display::checkForClose();
    }
    // Clean up VAOs and VBOs to avoid memory leak
    shader.cleanUp();
    loader.cleanUp();
    return 0;
}