#include "RawModel.hpp"

RawModel::RawModel() : m_vao_id ( 0 ), m_vertex_count ( 0 ){

}
RawModel::RawModel( const GLuint t_vao_id, const GLuint t_vertex_count ){

    // Set inicial attributes
    m_vao_id = t_vao_id;
    m_vertex_count = t_vertex_count;
}

GLuint RawModel::getVaoID(){

    // VAO ID getter
    return  m_vao_id;
}

GLuint RawModel::getVertexCount(){

    // Vertex Count getter
    return m_vertex_count;
}