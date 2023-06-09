#pragma once

#include <glimac/common.hpp>
#include <string>
#include <vector>
#include "p6/p6.h"
#include "tiny_obj_loader.h"

class Model {
protected:
    GLuint                           m_vbo;
    GLuint                           m_vao;
    std::vector<glimac::ShapeVertex> m_vertices;
    std::vector<int>                 m_index;
    float                            m_Rotation;

public:
    Model() = default;

    ~Model()
    {
        glDeleteBuffers(1, &m_vbo);
        glDeleteVertexArrays(1, &m_vao);
    };

    void                             loadModel(const std::string& fileName);
    std::vector<glimac::ShapeVertex> getVertices() const { return m_vertices; }
    void                             createVBO();
    void                             createVAO();

    GLuint getVbo() { return m_vbo; };
    GLuint getVao() { return m_vao; };
};