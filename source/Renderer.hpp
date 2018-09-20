#include "includes.hpp"
#include "models/TexturedModel.hpp"
#include "models/RawModel.hpp"
#include "Entity.hpp"
#include "shaders/StaticShader.hpp"
#include "includes/utilities.hpp"
#include "Display.hpp"

class Renderer{

    private:

    constexpr static GLfloat FOV = 100.0f;
    constexpr static GLfloat NEAR_PLANE = 0.01f;
    constexpr static GLfloat FAR_PLANE = 1000.0f;
    
    glm::mat4 projectionMatrix;

    void createProjectionMatrix();

    public:

    Renderer( StaticShader shader );
    void prepare();
    void render( Entity entity, StaticShader  shader );
    
};