#include "model.hpp"
#include <iostream>
#include <vector>
#include "glimac/common.hpp"
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
}
