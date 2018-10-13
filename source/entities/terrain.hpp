#ifndef TERRAIN_HPP
#define TERRAIN_HPP

#include "../includes/includes.hpp"
#include "../models/raw_model.hpp"
#include "../models/model_texture.hpp"
#include "../engine_core/loader.hpp"

class Terrain{

    private:

    GLfloat m_size;
    GLfloat m_vertex_count;

    GLfloat m_x;
    GLfloat m_z;
    RawModel m_model;
    ModelTexture m_texture;

    RawModel generateTerrain(Loader& p_loader);

    public:

    Terrain( GLuint p_grid_x, GLuint p_grid_z, GLfloat p_size,GLfloat p_vertex_count,Loader& p_loader, ModelTexture p_texture );
    GLfloat getX();
    GLfloat getZ();
    RawModel getModel();
    ModelTexture getTexture();
};

#endif // TERRAIN_HPP