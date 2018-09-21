#include "../includes/includes.hpp"
#include "../models/textured_model.hpp"
#include "../models/raw_model.hpp"
#include "../entities/entity.hpp"
#include "../shaders/static_shader.hpp"
#include "../includes/utilities.hpp"
#include "display.hpp"

class Renderer{

    private:

    constexpr static GLfloat kFOV = 100.0f;
    constexpr static GLfloat kNEAR_PLANE = 0.01f;
    constexpr static GLfloat kFAR_PLANE = 1000.0f;
    
    glm::mat4 projectionMatrix;

    void createProjectionMatrix();

    public:

    Renderer( StaticShader t_shader );
    void prepare();
    void render( Entity t_entity, StaticShader  t_shader );
    
};