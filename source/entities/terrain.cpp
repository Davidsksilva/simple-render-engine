#include "terrain.hpp"

Terrain::Terrain( GLuint p_grid_x, GLuint p_grid_z, GLfloat p_size,GLfloat p_vertex_count,Loader& p_loader, ModelTexture p_texture ) 
                : m_texture(p_texture),m_size(p_size),m_vertex_count(p_vertex_count), m_x(p_grid_x * m_size),m_z(p_grid_z * m_size),
                m_model(generateTerrain(p_loader)){

}

RawModel Terrain::generateTerrain(Loader& p_loader){

    GLuint count = m_vertex_count * m_vertex_count;
    GLuint vertex_pointer = 0;

    std::vector<GLfloat> vertices;
    vertices.resize(count * 3);
    std::vector<GLfloat> normals;
    normals.resize(count * 3);
    std::vector<GLfloat> texture_coordinates;
    texture_coordinates.resize(count * 2);
    std::vector<GLuint> indices;
    indices.resize(6 * (m_vertex_count -1) * (m_vertex_count -1));
    
    for( int i = 0; i < m_vertex_count; i++ ){

        for(int j = 0; j < m_vertex_count; j++){

            vertices[vertex_pointer*3] =  (GLfloat)j/((GLfloat)m_vertex_count -1) * m_size;
            vertices[vertex_pointer*3+1] = 0;
            vertices[vertex_pointer*3+2] = (GLfloat)i/((GLfloat) m_vertex_count -1) * m_size;

            normals[vertex_pointer*3] = 0;
            normals[vertex_pointer*3+1] = 1;
            normals[vertex_pointer*3+2] = 0;

            texture_coordinates[vertex_pointer*2] = (GLfloat)j/((GLfloat) m_vertex_count -1);
            texture_coordinates[vertex_pointer*2+1] = (GLfloat)i/((GLfloat) m_vertex_count -1);
            vertex_pointer++;

        }
    }
    GLuint pointer = 0;
    for( int gz = 0; gz < m_vertex_count -1; gz++ ){

        for ( int gx = 0; gx < m_vertex_count -1; gx++){

            int top_left = (gz * m_vertex_count) + gx;
            int top_right = top_left + 1;
            int bottom_left = ((gz+1)*m_vertex_count) + gx;
            int bottom_right = bottom_left +1;
            indices[pointer++] = top_left;
            indices[pointer++] = bottom_left;
            indices[pointer++] = top_right;
            indices[pointer++] = top_right;
            indices[pointer++] = bottom_left;
            indices[pointer++] = bottom_right;
        }
    }
         
    return p_loader.loadToVAO( vertices, indices, texture_coordinates, normals );

}

GLfloat Terrain::getX(){

    return m_x;
}

GLfloat Terrain::getZ(){

    return m_z;
}

RawModel Terrain::getModel(){

    return m_model;
}

ModelTexture Terrain::getTexture(){

    return m_texture;
}
