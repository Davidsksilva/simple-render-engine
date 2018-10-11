#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "../includes/includes.hpp"
#include "../models/textured_model.hpp"
#include "../models/raw_model.hpp"
#include "../entities/entity.hpp"
#include "../shaders/static_shader.hpp"
#include "../includes/utilities.hpp"
#include "display.hpp"
#include <map>


class Renderer{

    private:

    constexpr static GLfloat kFOV = 100.0f;
    constexpr static GLfloat kNEAR_PLANE = 0.01f;
    constexpr static GLfloat kFAR_PLANE = 1000.0f;
    glm::vec3 m_background_color;
    
    glm::mat4 projectionMatrix;
    StaticShader m_shader;

    //void createProjectionMatrix(GLuint t_width, GLuint t_height);
   void createProjectionMatrix();
    void prepareTexturedModel(  TexturedModel t_model );
    void unbindTexturedModel();
    void prepareInstance( Entity t_entity );

    GLuint m_fbo;
    GLuint m_height;
    GLuint m_width;
    GLuint m_rbo;
  
    public:

    GLuint createFBO();
    void bindFBO();
    void unbindFBO();
    void deleteFBO();
    void clear();

    GLuint fbo_texture;
    Renderer( StaticShader t_shader , GLfloat t_r, GLfloat t_g, GLfloat t_b );
    void render( std::map <TexturedModel, std::vector <Entity>> t_entities);
    void prepare();
    void setBackgroundColor ( GLfloat t_r, GLfloat t_g, GLfloat t_b );
    
};

#endif // RENDERER_HPP
