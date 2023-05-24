#include "cube.hpp"

Cube::Cube(float size)
    : m_size(size)
{
    // Calculer les coordonnées des sommets
    float x = size / 2.0f;
    float y = size / 2.0f;
    float z = size / 2.0f;

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    vertices = {
        -x, -y, -z,
        x, -y, -z,
        x, y, -z,
        -x, y, -z,
        -x, -y, z,
        x, -y, z,
        x, y, z,
        -x, y, z};

    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

    // Définir les indices des triangles
    indices = {
        0, 1, 2,
        2, 3, 0,
        1, 5, 6,
        6, 2, 1,
        4, 7, 6,
        6, 5, 4,
        0, 3, 7,
        7, 4, 0,
        3, 2, 6,
        6, 7, 3,
        0, 4, 5,
        5, 1, 0};

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);
}

void Cube::draw() const
{
    // Dessiner le cube avec le VAO et l'IBO
    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}