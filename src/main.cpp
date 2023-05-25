#include <iostream>
#include <vector>
#include "boids/boids.hpp"
#include "boids/field.hpp"
#include "boids/strengths.hpp"
#include "cube.hpp"
#include "glimac/common.hpp"
#include "glimac/freeflyCamera.hpp"
#include "glimac/sphere_vertices.hpp"
#include "glimac/trackballCamera.hpp"
#include "glm/ext/quaternion_trigonometric.hpp"
#include "glm/ext/scalar_constants.hpp"
#include "glm/fwd.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "model.hpp"
#include "p6/p6.h"

strengths strengths = {1, 1, 1, 0.06f, glm::length(glm::vec3(0.003f, 0.003f, 0.003f))};

int main()
{
    // creation du contexte p6
    auto ctx = p6::Context{{800, 600, "Boids"}};
    ctx.maximize_window();

    ///////////// GESTION DE LA CAMERA ///////////////

    TrackballCamera camera;

    ctx.mouse_scrolled = [&](p6::MouseScroll scroll) {
        camera.zoom(-scroll.dy);
    };

    /////////////// GESTION DES BOIDS ///////////////

    // chargement des shaders
    const p6::Shader shader = p6::load_shader(
        "shaders/3D.vs.glsl",
        "shaders/normals.fs.glsl"
    );
    shader.use();

    // récupération des locations de variables uniformes
    GLuint U_MVP_MATRIX_LOCATION    = glGetUniformLocation(shader.id(), "uMVPMatrix");
    GLuint U_MV_MATRIX_LOCATION     = glGetUniformLocation(shader.id(), "uMVMatrix");
    GLuint U_NORMAL_MATRIX_LOCATION = glGetUniformLocation(shader.id(), "uNormalMatrix");

    glEnable(GL_DEPTH_TEST);

    Cube cube(0.5);
    shader.use();
    cube.draw();

    Model mouche = Model();

    mouche.loadModel("fly.obj");
    // Get the vertices and number of vertices
    std::vector<glimac::ShapeVertex> m_vertices    = mouche.getVertices();
    GLsizei                          m_vertexCount = mouche.getNumVertices();

    // CREATION DU VBO
    GLuint vbo;
    glGenBuffers(1, &vbo);

    // binding du vbo
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    // remplissage VBO
    glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(glimac::ShapeVertex), m_vertices.data(), GL_STATIC_DRAW);

    // debinder le VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // création du vao
    GLuint vao;
    glGenVertexArrays(1, &vao);

    // binder le VAO
    glBindVertexArray(vao);

    // activation des attributs de vertex
    static constexpr GLuint VERTEX_ATTR_POSITION = 0;
    static constexpr GLuint VERTEX_ATTR_NORMAL   = 1;

    glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
    glEnableVertexAttribArray(VERTEX_ATTR_NORMAL);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    glVertexAttribPointer(VERTEX_ATTR_POSITION, 2, GL_FLOAT, GL_FALSE, sizeof(glimac::ShapeVertex), (const GLvoid*)offsetof(glimac::ShapeVertex, position)); // specification des attributs de vertex

    glVertexAttribPointer(VERTEX_ATTR_NORMAL, 2, GL_FLOAT, GL_FALSE, sizeof(glimac::ShapeVertex), (const GLvoid*)offsetof(glimac::ShapeVertex, normal));

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    Field field(50, ctx);

    ctx.update = [&]() {
        shader.use();
        cube.draw();
        std::vector<glm::vec3> positions = field.fieldDraw(ctx);
        field.applyRules(strengths);

        ///////////// GESTION DE LA CAMERA ///////////////
        glm::mat4 viewMatrix = camera.getViewMatrix();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glBindVertexArray(vao);

        glm::mat4 ProjMatrix   = glm::perspective(glm::radians(70.f), 800.f / 600.f, 0.1f, 100.f);
        glm::mat4 MVMatrix     = glm::translate(glm::mat4(1), glm::vec3(0, 0, -5));
        glm::mat4 NormalMatrix = glm::transpose(glm::inverse(MVMatrix));

        // for (size_t i = 0; i < field.getBoids().size(); i++)
        // {
        //     MVMatrix = glm::translate(glm::mat4{1.f}, {0.f, 0.f, 0.f}); // Translation
        //     MVMatrix = glm::translate(MVMatrix, positions[i]);          // Translation * Rotation * Translation
        //     MVMatrix = glm::scale(MVMatrix, glm::vec3{0.02f});
        //     MVMatrix = viewMatrix * MVMatrix;

        //     glUniformMatrix4fv(U_MVP_MATRIX_LOCATION, 1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix));
        //     glUniformMatrix4fv(U_MV_MATRIX_LOCATION, 1, GL_FALSE, glm::value_ptr(MVMatrix /*Boids*/));
        //     glUniformMatrix4fv(U_NORMAL_MATRIX_LOCATION, 1, GL_FALSE, glm::value_ptr(NormalMatrix));
        //     glDrawArrays(GL_TRIANGLES, 0, m_vertices.size());
        // };

        // debinder le vbo
        glBindVertexArray(0);
    };

    ctx.start();
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);
}
