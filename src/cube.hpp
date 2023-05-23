#pragma once

#include <glm/glm.hpp>
#include "glm/fwd.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "p6/p6.h"

class Cube {
private:
    std::vector<float>  vertices;
    std::vector<GLuint> indices;
    GLuint              vao, vbo, ibo;
    float               m_size;

public:
    explicit Cube(float size);

    void draw() const;
};

void display();
