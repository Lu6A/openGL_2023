#include "model.hpp"
#include "glimac/default_shader.hpp"
#include "glimac/sphere_vertices.hpp"
#include "glm/fwd.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "p6/p6.h"

void Model::loadModel(const std::string& fileName)
{
    // Load 3D object
    std::string                      inputfile = "assets/models/" + fileName;
    tinyobj::attrib_t                attrib;
    std::vector<tinyobj::shape_t>    shapes;
    std::vector<tinyobj::material_t> materials;

    std::string warn;
    std::string err;
    bool        success = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, inputfile.c_str(), nullptr);

    if (!err.empty())
    { // `err` may contain warning message.
        std::cerr << err << std::endl;
    }

    if (!success)
    {
        std::cout << "c'est pas chargé rip" << std::endl;
        exit(1);
    }

    // Le chargement a réussi
    // Vous pouvez accéder aux données du modèle à partir de la variable 'shapes' et 'materials'
    std::cout << "c'est chargé tkt" << std::endl;

    // Process the model data and prepare it for rendering
    for (const auto& shape : shapes)
    {
        for (const auto& index : shape.mesh.indices)
        {
            glimac::ShapeVertex vertex;

            // Retrieve vertex position
            vertex.position.x = attrib.vertices[3 * index.vertex_index + 0];
            vertex.position.y = attrib.vertices[3 * index.vertex_index + 1];
            vertex.position.z = attrib.vertices[3 * index.vertex_index + 2];

            // Retrieve vertex normal
            vertex.normal.x = attrib.normals[3 * index.normal_index + 0];
            vertex.normal.y = attrib.normals[3 * index.normal_index + 1];
            vertex.normal.z = attrib.normals[3 * index.normal_index + 2];

            // You can also retrieve texture coordinates if needed
            // vertex.texCoords.x = attrib.texcoords[2 * index.texcoord_index + 0];
            // vertex.texCoords.y = attrib.texcoords[2 * index.texcoord_index + 1];

            m_vertices.push_back(vertex);
        }
    }

    m_vertexCount = static_cast<GLsizei>(m_vertices.size());

    // Print some information about the loaded model
    std::cout << "Loaded model: " << fileName << std::endl;
    std::cout << "Number of vertices: " << m_vertexCount << std::endl;
    std::cout << "Number of shapes: " << shapes.size() << std::endl;
    std::cout << "Number of materials: " << materials.size() << std::endl;
}

void Model::createVBO()
{
    // creating & binding vbo
    m_vbo = 0;
    glGenBuffers(1, &m_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

    // creating vertices
    const std::vector<glimac::ShapeVertex> model_vertices = m_vertices;

    // sending data to GPU
    glBufferData(GL_ARRAY_BUFFER, model_vertices.size() * sizeof(glimac::ShapeVertex), model_vertices.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Model::createVAO()
{
    // creating & binding vao
    m_vao = 0;
    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);

    // binding vbo
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

    const GLuint VERTEX_ATTR_POSITION = 0;
    const GLuint VERTEX_ATTR_NORMAL   = 1;
    // const GLuint VERTEX_ATTR_TEXCOORDS = 2;

    glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
    glEnableVertexAttribArray(VERTEX_ATTR_NORMAL);
    // glEnableVertexAttribArray(VERTEX_ATTR_TEXCOORDS);

    glVertexAttribPointer(VERTEX_ATTR_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(glimac::ShapeVertex), (const GLvoid*)offsetof(glimac::ShapeVertex, position));
    glVertexAttribPointer(VERTEX_ATTR_NORMAL, 3, GL_FLOAT, GL_FALSE, sizeof(glimac::ShapeVertex), (const GLvoid*)offsetof(glimac::ShapeVertex, normal));
    // glVertexAttribPointer(VERTEX_ATTR_TEXCOORDS, 2, GL_FLOAT, GL_FALSE, sizeof(glimac::ShapeVertex),(const GLvoid*)offsetof(glimac::ShapeVertex, texCoords));

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}
