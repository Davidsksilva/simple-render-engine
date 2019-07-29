#include "terrain_renderer.hpp"

TerrainRenderer::TerrainRenderer( TerrainShader p_shader, glm::mat4 p_projection_matrix ){

    m_shader = p_shader;
    m_shader.start();
    m_shader.loadProjectionMatrix(p_projection_matrix);
    m_shader.stop(); 
}

TerrainRenderer::TerrainRenderer() : m_shader(TerrainShader()){

}

void TerrainRenderer::render( std::vector <Terrain> p_terrains ){

    for(Terrain terrain : p_terrains){
        prepareTerrain(terrain);
        loadModelMatrix(terrain);
        glDrawElements( GL_TRIANGLES,terrain.getModel().getVertexCount(), GL_UNSIGNED_INT, 0 );
        unbindTexturedModel();
    }

}

void TerrainRenderer::prepareTerrain ( Terrain& p_terrain ){

    RawModel raw_model  = p_terrain.getModel();

    // Bind VAO and VBOS ( Position, Texture)
    glBindVertexArray(raw_model .getVaoID() );
    glEnableVertexAttribArray( 0 );
    glEnableVertexAttribArray( 1 );
    glEnableVertexAttribArray( 2 );
    ModelTexture texture = p_terrain.getTexture();
    m_shader.loadSpecular(texture);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture( GL_TEXTURE_2D, texture.getID());
}

void TerrainRenderer::unbindTexturedModel(){

    // Disable VBOs
    glDisableVertexAttribArray( 0 );
    glDisableVertexAttribArray( 1 );
    glDisableVertexAttribArray( 2 );
    // Unbind VAO
    glBindVertexArray( 0 );

}

void TerrainRenderer::loadModelMatrix( Terrain& p_terrain){

    glm::mat4 transformationMatrix = utils::createTransformationMatrix( glm::vec3(0,0,0), glm::vec3(0,0,0), glm::vec3(1,1,1) );
    m_shader.loadTransformationMatrix( transformationMatrix );
}