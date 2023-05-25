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
