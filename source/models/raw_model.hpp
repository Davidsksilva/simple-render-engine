#ifndef RAWLODEL_HPP
#define RAWLODEL_HPP

#include "../includes/includes.hpp"

class RawModel{

    private:

    // Declaring ID of model VAO and the vertex count
    GLuint m_vao_id;
    GLuint m_vertex_count;

    public:
    RawModel();
    RawModel( const GLuint t_vao_id, const GLuint t_vertex_count );
    GLuint getVaoID();
    GLuint getVertexCount();

};

#endif // RAWLODEL_HPP