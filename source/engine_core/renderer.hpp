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
    glm::vec3 m_background_color;
    
    glm::mat4 projectionMatrix;

    void createProjectionMatrix();

    GLuint m_fbo;

  
    public:
    GLuint createFBO();
    void bindFBO();
    void unbindFBO();
    void deleteFBO();
    void clear();

    GLuint fbo_texture;
    Renderer( StaticShader t_shader , GLfloat t_r, GLfloat t_g, GLfloat t_b );
    void prepare();
    void render( Entity t_entity, StaticShader  t_shader );
    void setBackgroundColor ( GLfloat t_r, GLfloat t_g, GLfloat t_b );
    
};