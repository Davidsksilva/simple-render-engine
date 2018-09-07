#include "Display.hpp"
#include "includes.hpp"
#include "Loader.hpp"
#include "Renderer.hpp"
 
int main(int argc, char** argv)
{
    Display::create();
    //Display::clear(1.0, 1.0, 1.0);
    Loader loader = Loader();
    Renderer renderer = Renderer();
    std::vector<float>vertices = {
        -0.5f, 0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.5f, 0.5f, 0.0f,
        -0.5f, 0.5f, 0.f
    };

    RawModel model = loader.loadToVAO(vertices);

    while(Display::isOpen()){

        renderer.prepare();
        renderer.render(model);

        Display::update();
        Display::checkForClose();
    }

    loader.cleanUp();
    return 0;
}