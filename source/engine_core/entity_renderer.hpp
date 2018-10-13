#ifndef ENTITY_RENDERER_HPP
#define ENTITY_RENDERER_HPP

#include "../includes/includes.hpp"
#include "../models/textured_model.hpp"
#include "../models/raw_model.hpp"
#include "../entities/entity.hpp"
#include "../shaders/static_shader.hpp"
#include "../includes/utilities.hpp"
#include "display.hpp"
#include <map>


class EntityRenderer{

    private:

    glm::vec3 m_background_color;
    StaticShader m_shader;

    void prepareTexturedModel(  TexturedModel t_model );
    void unbindTexturedModel();
    void prepareInstance( Entity t_entity );
    
    public:
    
    void clear();
    EntityRenderer();
    EntityRenderer( StaticShader p_shader , GLfloat p_r, GLfloat p_g, GLfloat p_b ,glm::mat4 p_projection_matrix);
    void render( std::map <TexturedModel, std::vector <Entity>> p_entities);
    void setBackgroundColor ( GLfloat p_r, GLfloat p_g, GLfloat p_b );
    
};

#endif // ENTITY_RENDERER_HPP
