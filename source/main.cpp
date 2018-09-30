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
#include "imgui/imgui.h"
#include "imgui/imgui-SFML.h"
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

int main( void )
{

    Display::create();
    ImGui::SFML::Init(*Display::m_window);
    Display::clear(1.0, 1.0, 1.0);
    
    Loader loader = Loader();
    StaticShader shader = StaticShader();
    Renderer renderer = Renderer( shader , 0, 0 ,0);

    RawModel model = loader.loadObj("source/res/models/grass.obj");
    TexturedModel staticModel = TexturedModel (model, ModelTexture( loader.loadTexture( "source/res/img/grass.png" ),10.0f,1.0f ));
    Entity entity = Entity( staticModel, glm::vec3(0.0f,-1.0f,-1.0f), glm::vec3(0,0,0), 1.0f );
    Light light = Light(glm::vec3(200,200,100), glm::vec3(1,1,1), 0.2f);
    bool show_demo_window = true;
    Camera camera = Camera();
    sf::Clock deltaClock;
    float color[3] = { 0.f, 0.f, 0.f };
    // Main Loop
    renderer.createFBO();

glBindFramebuffer(GL_FRAMEBUFFER, 0);  
    while(Display::isOpen()){
        
        // entity.increasePosition(0,0,-0.1f);
        glViewport( 0, 0, 512, 512);
        camera.move();
        entity.increaseRotation(0,0.01f,0);
        renderer.prepare();
        renderer.bindFBO();
        renderer.prepare();
        
        renderer.clear();
        shader.start();
        shader.loadLight(light);
        shader.loadViewMatrix( camera );
        
        renderer.render( entity, shader ); 
       
        
        
        sf::Event evnt;
       
       renderer.unbindFBO();
       
        
        // Checking window events
       while( Display::m_window->pollEvent( evnt ) ){
            ImGui::SFML::ProcessEvent(evnt);
            //Check if event is closing
            if( evnt.type == sf::Event::Closed ){
                Display::close();
            }
        }
        //
        ImGui::SFML::Update(*Display::m_window, deltaClock.restart() );

        //ImGui::ShowDemoWindow(&show_demo_window);
        ImGui::SetNextWindowSize(ImVec2(512,512), ImGuiSetCond_FirstUseEver);
        ImGui::Begin("Rendering");
        {   
            ImVec2 pos = ImGui::GetCursorScreenPos();
            auto tex = renderer.fbo_texture;


            ImGui::GetWindowDrawList()->AddImage(
                (void*)tex, ImGui::GetCursorScreenPos(),
                ImVec2(ImGui::GetCursorScreenPos().x + 512, 
ImGui::GetCursorScreenPos().y + 512),ImVec2(0,1), ImVec2(1,0));
        }
        ImGui::End();
        ImGui::Begin("Background Color");

        if (ImGui::ColorEdit3("Background color", color)) {
            // this code gets called if color value changes, so
            // the background color is upgraded automatically!
            renderer.setBackgroundColor( color[0], color[1], color[2] );
        }
        ImGui::End();
        ImGui::SFML::Render(*Display::m_window);
        shader.stop();
        Display::update();
        

        //Display::checkForClose();
    }

    // Clean up VAOs and VBOs to avoid memory leak
    shader.cleanUp();
    loader.cleanUp();
    renderer.deleteFBO();
    ImGui::SFML::Shutdown();
    return 0;
}