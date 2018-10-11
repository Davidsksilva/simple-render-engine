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
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include "interface/interface.hpp"
#include <stdio.h>

#include <GL/glew.h>    // Initialize with glewInit()

#include <GLFW/glfw3.h> // Include glfw3.h after our OpenGL definitions

static void glfw_error_callback(int error, const char* description)
{
    fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

int main(int, char**)
{
    
    Display::create(1920,1080,"Simon Engine");

    Loader loader = Loader();
    StaticShader shader = StaticShader();

    RawModel model_raw = loader.loadObj("source/res/models/grass.obj");
    ModelTexture model_texture = ModelTexture( loader.loadTexture( "source/res/img/grass.png" ),10.0f,1.0f );
    TexturedModel model = TexturedModel (model_raw, model_texture);

    Entity entity = Entity( model, glm::vec3(0.0f,-1.0f,-1.0f), glm::vec3(0.0f,0.0f,0.0f), 1.0f );
    Light light = Light(glm::vec3(0.0f,0.0f,0.0f), glm::vec3(1.0f,1.0f,1.0f), 0.5f);
    Camera camera = Camera();

    std::vector <Entity*> entities;
    //entities.push_back(&entity);

    MasterRenderer master_renderer = MasterRenderer( shader,light,camera, 0.0f, 0.0f, 0.0f);

    UserInterface user_interface = UserInterface(master_renderer);
    //user_interface.loadStyle();


    bool show_demo_window = true;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    float color[3] = {0.0f,0.0f,0.0f};

    

    // Main loop
    while (!glfwWindowShouldClose(Display::window))
    {
         // entity.increasePosition(0,0,-0.1f);
        glViewport( 0, 0, 1121, 687);
        camera.move();
        //entity.increaseRotation(0,0.01f,0);
        //std::cout << entities.size() << std::endl;
        for( Entity* ent : entities){
            master_renderer.processEntity(*ent);
        }
        master_renderer.renderFBO(light, camera );

        user_interface.startInterface(entities);

        Display::update();
        
    }

    shader.cleanUp();
    master_renderer.cleanUp();
    Display::close();
    for( Entity* ent : entities){
        delete ent;
    }
    return 0;
}
