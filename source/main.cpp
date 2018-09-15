#include "includes.hpp"
#include "RawModel.hpp"
#include "Display.hpp"
#include "StaticShader.hpp"
#include "Loader.hpp"
#include "Renderer.hpp"
#include "ModelTexture.hpp"
#include "TexturedModel.hpp"


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
     std::vector<GLfloat>verticess = {
        -1.0f,1.0f,0.0f,
        -1.0f,-1.0f,0.0f,
        1.0f,-1.0,0.0f,
        1.0f,1.0f,0.0f
    };


    std::vector<GLuint>indices = {
        0,1,3,
        3,1,2
    };

    std::vector<GLfloat>textureCoords = {
        0,0,
        0,1,
        1,1,
        1,0
    };

    RawModel model = loader.loadToVAO( vertices, indices, textureCoords );
    ModelTexture texture = ModelTexture( loader.loadTexture( "source/res/checkerboard.png" ) );
    TexturedModel texturedModel = TexturedModel(model,texture);
    
    // While the window is open
    while(Display::isOpen()){
        // Prepare renderer
        renderer.prepare();
        shader.start();
        renderer.render(texturedModel);
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