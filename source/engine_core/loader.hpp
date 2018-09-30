#ifndef LOADER_HPP
#define LOADER_HPP

#include "../includes/includes.hpp"
#include "../models/raw_model.hpp"
#include "../includes/utilities.hpp"


class Loader{

    public:

    RawModel loadToVAO( const std::vector<GLfloat>& t_positions, const std::vector<GLuint>& t_indices, 
                        const std::vector<GLfloat>& t_texture_coordinates, const std::vector<GLfloat>& t_normals );

    GLuint loadTexture( const std::string t_file_name);

    RawModel loadObj( const char* t_file_path );

    void cleanUp();


    private:

    std::vector<GLuint> m_vaos;
    std::vector<GLuint> m_vbos;
    std::vector<GLuint> m_textures;
    GLuint createVAO();



    void storeDataInAttributeList( const GLuint t_attribute_number, const GLuint t_size, const std::vector<GLfloat>& t_data );

    void unbindVAO();

    void bindIndicesBuffer( const std::vector<GLuint> t_indices );

};

#endif // LOADER_HPP