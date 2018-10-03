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
#include "engine_core/master_renderer.hpp"
#include "engine_core/display.hpp"
#include "engine_core/light.hpp"
#include "interface/interface.hpp"
#include "imgui/imgui.h"
#include "imgui/imgui-SFML.h"
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
//#define ImGuiConfigFlags_DockingEnable 1<< 6

int main( void )
{

    Display::create();
    Display::clear(1.0f, 1.0f, 1.0f);

    ImGui::SFML::Init(*Display::m_window);

    
    Loader loader = Loader();
    StaticShader shader = StaticShader();

    RawModel model_raw = loader.loadObj("source/res/models/grass.obj");
    ModelTexture model_texture = ModelTexture( loader.loadTexture( "source/res/img/grass.png" ),10.0f,1.0f );
    TexturedModel model = TexturedModel (model_raw, model_texture);

    Entity entity = Entity( model, glm::vec3(0.0f,-1.0f,-1.0f), glm::vec3(0.0f,0.0f,0.0f), 1.0f );
    Light light = Light(glm::vec3(200.0f,200.0f,100.0f), glm::vec3(1.0f,1.0f,1.0f), 0.2f);
    Camera camera = Camera();

    MasterRenderer master_renderer = MasterRenderer( shader, 0.0f, 0.0f, 0.0f);
    sf::Clock deltaClock;
    UserInterface user_interface = UserInterface(master_renderer, deltaClock);
  

    
    bool show_demo_window = false;
    while(Display::isOpen()){
        
        // entity.increasePosition(0,0,-0.1f);
        glViewport( 0, 0, 512, 512);
        //camera.move();
        entity.increaseRotation(0,0.01f,0);
        master_renderer.processEntity(entity);
        //master_renderer.render(light, camera);
        master_renderer.renderFBO(light, camera );
    
        user_interface.startInterface();
        
        Display::update();
        
        Display::checkForClose();
    }


    shader.cleanUp();
    master_renderer.cleanUp();
    ImGui::SFML::Shutdown();
    return 0;
}