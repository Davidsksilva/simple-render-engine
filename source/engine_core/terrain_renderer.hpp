#ifndef TERRAIN_RENDERER_HPP
#define TERRAIN_RENDERER_HPP

#include "../shaders/terrain_shader.hpp"
#include "../includes/includes.hpp"
#include "../entities/terrain.hpp"
#include "../models/textured_model.hpp"


class TerrainRenderer {

    private:

    TerrainShader m_shader;


    void render( std::map< TexturedModel, std::vector < Terrain>> p_entities );
    
    public:
    TerrainRenderer();
    TerrainRenderer( TerrainShader p_shader, glm::mat4 p_projection_matrix );
    void prepareTerrain ( Terrain& p_terrain );
    void loadModelMatrix( Terrain& p_terrain);
    void render( std::vector <Terrain> p_terrains );
    void unbindTexturedModel();


};

#endif // TERRAIN_RENDERER_HPP