#include "includes/includes.hpp"
#include "shaders/static_shader.hpp"
#include "models/raw_model.hpp"
#include "models/model_texture.hpp"
#include "models/textured_model.hpp"
#include "entities/entity.hpp"
#include "engine_core/camera.hpp"
#include "engine_core/loader.hpp"
#include "engine_core/renderer.hpp"
#include "engine_core/display.hpp"

int main( void )
{

    Display::create();
    Display::clear(1.0, 1.0, 1.0);
    
    Loader loader = Loader();
    StaticShader shader = StaticShader();
    Renderer renderer = Renderer( shader );

    
    

    std::vector<GLfloat>vertices = {
        -0.5f,0.5f,-0.5f,	
        -0.5f,-0.5f,-0.5f,	
        0.5f,-0.5f,-0.5f,	
        0.5f,0.5f,-0.5f,		
        
        -0.5f,0.5f,0.5f,	
        -0.5f,-0.5f,0.5f,	
        0.5f,-0.5f,0.5f,	
        0.5f,0.5f,0.5f,
        
        0.5f,0.5f,-0.5f,	
        0.5f,-0.5f,-0.5f,	
        0.5f,-0.5f,0.5f,	
        0.5f,0.5f,0.5f,
        
        -0.5f,0.5f,-0.5f,	
        -0.5f,-0.5f,-0.5f,	
        -0.5f,-0.5f,0.5f,	
        -0.5f,0.5f,0.5f,
        
        -0.5f,0.5f,0.5f,
        -0.5f,0.5f,-0.5f,
        0.5f,0.5f,-0.5f,
        0.5f,0.5f,0.5f,
        
        -0.5f,-0.5f,0.5f,
        -0.5f,-0.5f,-0.5f,
        0.5f,-0.5f,-0.5f,
        0.5f,-0.5f,0.5f
				
    };

    std::vector<GLuint>indices = {
        0,1,3,	
        3,1,2,	
        4,5,7,
        7,5,6,
        8,9,11,
        11,9,10,
        12,13,15,
        15,13,14,	
        16,17,19,
        19,17,18,
        20,21,23,
        23,21,22
    };

    std::vector<GLfloat>textureCoords = {
        0,0,
        0,1,
        1,1,
        1,0,			
        0,0,
        0,1,
        1,1,
        1,0,			
        0,0,
        0,1,
        1,1,
        1,0,
        0,0,
        0,1,
        1,1,
        1,0,
        0,0,
        0,1,
        1,1,
        1,0,
        0,0,
        0,1,
        1,1,
        1,0
    };

    RawModel model = loader.loadToVAO( vertices, indices, textureCoords );
    ModelTexture texture = ModelTexture( loader.loadTexture( "source/data/img/checkerboard.png" ) );
    TexturedModel staticModel = TexturedModel(model,texture);
    Entity entity = Entity( staticModel, glm::vec3(0,0,-5.0f), glm::vec3(0,0,0), 1.0f );
    Camera camera = Camera();
    
    // Main Loop
    while(Display::isOpen()){
       // entity.increasePosition(0,0,-0.1f);
        camera.move();
        entity.increaseRotation(0.01f,0.01f,0);
        renderer.prepare();
        shader.start();
        shader.loadViewMatrix( camera );

        renderer.render( entity, shader );

        shader.stop();

        Display::update();
        Display::checkForClose();
    }

    // Clean up VAOs and VBOs to avoid memory leak
    shader.cleanUp();
    loader.cleanUp();
    return 0;
}