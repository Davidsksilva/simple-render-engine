#include "entity_renderer.hpp"

EntityRenderer::EntityRenderer( StaticShader p_shader, GLfloat p_r, GLfloat p_g, GLfloat p_b, glm::mat4 p_projection_matrix ){

    m_shader = p_shader;
    m_background_color.x = p_r;
    m_background_color.y = p_g;
    m_background_color.z = p_b;
    p_shader.start();
    p_shader.loadProjectionMatrix(p_projection_matrix);
    p_shader.stop();
}

EntityRenderer::EntityRenderer() : m_shader(StaticShader()),m_background_color(0,0,0){
    
}


void EntityRenderer::clear(){

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // Set Background Color
    glClearColor(m_background_color.x, m_background_color.y, m_background_color.z, 1);

    glEnable    ( GL_DEPTH_TEST );

}



void EntityRenderer::setBackgroundColor ( GLfloat p_r, GLfloat p_g, GLfloat p_b ){

    m_background_color.x = p_r;
    m_background_color.y = p_g;
    m_background_color.z = p_b;
}

void EntityRenderer::render( std::map< TexturedModel, std::vector < Entity>> p_entities ){

    for( auto const& [model, entities] : p_entities){

        prepareTexturedModel(model);
        for( Entity entity : entities){
            prepareInstance(entity);
            glDrawElements( GL_TRIANGLES,model.getRawModel().getVertexCount(), GL_UNSIGNED_INT, 0 );
        }
        unbindTexturedModel();
    }

}

void EntityRenderer::prepareTexturedModel ( TexturedModel p_model ){

    RawModel raw_model  = p_model.getRawModel();

    // Bind VAO and VBOS ( Position, Texture)
    glBindVertexArray(raw_model .getVaoID() );
    glEnableVertexAttribArray( 0 );
    glEnableVertexAttribArray( 1 );
    glEnableVertexAttribArray( 2 );
    ModelTexture texture = p_model.getTexture();
    m_shader.loadSpecular(texture);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture( GL_TEXTURE_2D, p_model.getTexture().getID());
}

void EntityRenderer::unbindTexturedModel(){

    // Disable VBOs
    glDisableVertexAttribArray( 0 );
    glDisableVertexAttribArray( 1 );
    glDisableVertexAttribArray( 2 );
    // Unbind VAO
    glBindVertexArray( 0 );

}

void EntityRenderer::prepareInstance( Entity p_entity){

    glm::mat4 transformationMatrix = utils::createTransformationMatrix( p_entity.getPosition(), p_entity.getRotation(), p_entity.getScale() );
    m_shader.loadTransformationMatrix( transformationMatrix );
}