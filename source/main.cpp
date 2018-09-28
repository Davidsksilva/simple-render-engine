#include "includes/includes.hpp"
#include "includes/utilities.hpp"
#include "shaders/static_shader.hpp"
#include "models/raw_model.hpp"
#include "models/model_texture.hpp"
#include "models/textured_model.hpp"
#include "entities/entity.hpp"
#include "engine_core/camera.hpp"
#include "engine_core/loader.hpp"
#include "engine_core/renderer.hpp"
#include "engine_core/display.hpp"
#include "engine_core/light.hpp"

int main( void )
{

    Display::create();
    Display::clear(1.0, 1.0, 1.0);
    
    Loader loader = Loader();
    StaticShader shader = StaticShader();
    Renderer renderer = Renderer( shader );

    RawModel model = loader.loadObj("source/res/models/rock.obj");
    ModelTexture texture = ModelTexture( loader.loadTexture( "source/res/img/rock.png" ) );
    TexturedModel staticModel = TexturedModel(model,texture);
    Entity entity = Entity( staticModel, glm::vec3(0,0.0f,-2.0f), glm::vec3(0,0,0), 1.0f );
    Light light = Light(glm::vec3(0,0,2), glm::vec3(1,1,1));
    
    Camera camera = Camera();
    
    // Main Loop
    while(Display::isOpen()){
        // entity.increasePosition(0,0,-0.1f);
        camera.move();
        entity.increaseRotation(0,0.01f,0);
        renderer.prepare();
        shader.start();
        shader.loadLight(light);
        shader.loadViewMatrix( camera );
        renderer.render( entity, shader ); // erro aqui

        shader.stop();

        Display::update();
        Display::checkForClose();
    }

    // Clean up VAOs and VBOs to avoid memory leak
    shader.cleanUp();
    loader.cleanUp();
    return 0;
}