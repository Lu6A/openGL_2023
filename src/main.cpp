#include <iostream>
#include <vector>
#include "boids/boids.hpp"
#include "boids/field.hpp"
#include "boids/strengths.hpp"
#include "glimac/common.hpp"
#include "glimac/freeflyCamera.hpp"
#include "glimac/sphere_vertices.hpp"
#include "glimac/trackballCamera.hpp"
#include "glm/ext/quaternion_trigonometric.hpp"
#include "glm/ext/scalar_constants.hpp"
#include "glm/fwd.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/trigonometric.hpp"
#include "loadingProgram.hpp"
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

    /////////////// GESTION DES SHADERS ///////////////

    Program program;

    ///////////// GESTION DES TEXTURES ///////////////

    program.use();

    // // récupération des locations de variables uniformes
    GLuint U_MVP_MATRIX_LOCATION    = glGetUniformLocation(shader.id(), "uMVPMatrix");
    GLuint U_MV_MATRIX_LOCATION     = glGetUniformLocation(shader.id(), "uMVMatrix");
    GLuint U_NORMAL_MATRIX_LOCATION = glGetUniformLocation(shader.id(), "uNormalMatrix");
    // GLint  U_TEXTURE_1              = glGetUniformLocation(shader.id(), "uTexture1");
    // GLint  U_TEXTURE_2              = glGetUniformLocation(shader.id(), "uTexture2");

    glEnable(GL_DEPTH_TEST);

    // // matrices ?
    // glm::mat4 ProjMatrix   = glm::perspective(glm::radians(70.0f), 800.0f / 600.0f, 0.1f, 100.0f); // param perspective(float fovy, float aspect, float znear, float far)
    // glm::mat4 MVMatrix     = glm::translate(glm::mat4(1), glm::vec3(0, 0, -5));
    // glm::mat4 NormalMatrix = glm::transpose(glm::inverse(MVMatrix));

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
    // static constexpr GLuint VERTEX_ATTR_TEXCOORDS = 2;

    glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
    glEnableVertexAttribArray(VERTEX_ATTR_NORMAL);
    // glEnableVertexAttribArray(VERTEX_ATTR_TEXCOORDS);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    glVertexAttribPointer(VERTEX_ATTR_POSITION, 2, GL_FLOAT, GL_FALSE, sizeof(glimac::ShapeVertex), (const GLvoid*)offsetof(glimac::ShapeVertex, position)); // specification des attributs de vertex

    glVertexAttribPointer(VERTEX_ATTR_NORMAL, 2, GL_FLOAT, GL_FALSE, sizeof(glimac::ShapeVertex), (const GLvoid*)offsetof(glimac::ShapeVertex, normal));

    // // activation des attributs de vertex
    // static constexpr GLuint VERTEX_ATTR_POSITION = 0;
    // static constexpr GLuint VERTEX_NORMAL        = 1;
    // static constexpr GLuint TEXT_COORD           = 2;

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // // spécification des attributs de vertex
    // glBindBuffer(GL_ARRAY_BUFFER, vbo);
    // glVertexAttribPointer(VERTEX_ATTR_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(glimac::ShapeVertex), (const GLvoid*)offsetof(glimac::ShapeVertex, position));
    // glVertexAttribPointer(VERTEX_NORMAL, 3, GL_FLOAT, GL_FALSE, sizeof(glimac::ShapeVertex), (const GLvoid*)offsetof(glimac::ShapeVertex, normal));
    // glVertexAttribPointer(TEXT_COORD, 2, GL_FLOAT, GL_FALSE, sizeof(glimac::ShapeVertex), (const GLvoid*)offsetof(glimac::ShapeVertex, texCoords));
    // glBindBuffer(GL_ARRAY_BUFFER, 0);
    // glBindVertexArray(0);

    Field field(50, ctx);

    ctx.update = [&]() {
        shader.use();
        std::vector<glm::vec3> positions = field.fieldDraw(ctx);
        field.applyRules(strengths);

        ///////////// GESTION DE LA CAMERA ///////////////
        glm::mat4 viewMatrix = camera.getViewMatrix();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glBindVertexArray(vao);

        glm::mat4 ProjMatrix   = glm::perspective(glm::radians(70.f), 800.f / 600.f, 0.1f, 100.f);
        glm::mat4 MVMatrix     = glm::translate(glm::mat4(1), glm::vec3(0, 0, -5));
        glm::mat4 NormalMatrix = glm::transpose(glm::inverse(MVMatrix));

        for (size_t i = 0; i < field.getBoids().size(); i++)
        {
            MVMatrix = glm::translate(glm::mat4{1.f}, {0.f, 0.f, 0.f}); // Translation
            MVMatrix = glm::translate(MVMatrix, positions[i]);          // Translation * Rotation * Translation
            MVMatrix = glm::scale(MVMatrix, glm::vec3{0.02f});
            MVMatrix = viewMatrix * MVMatrix;
            // glm::mat4 MVMatrixBoids = glm::translate(glm::mat4{1.f}, {1.f, 1.f, -1.f}); // Translation
            // MVMatrixBoids           = glm::translate(MVMatrixBoids, positions[i]);      // Translation * Rotation * Translation
            // MVMatrixBoids           = glm::scale(MVMatrixBoids, glm::vec3{1., 1., 1.}); // Translation * Rotation * Translation * Scale
            // MVMatrixBoids           = MVMatrix * MVMatrixBoids;
            glUniformMatrix4fv(U_MVP_MATRIX_LOCATION, 1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix));
            glUniformMatrix4fv(U_MV_MATRIX_LOCATION, 1, GL_FALSE, glm::value_ptr(MVMatrix /*Boids*/));
            glUniformMatrix4fv(U_NORMAL_MATRIX_LOCATION, 1, GL_FALSE, glm::value_ptr(NormalMatrix));
            glDrawArrays(GL_TRIANGLES, 0, m_vertices.size());
        };

        // debinder le vbo
        glBindVertexArray(0);
    };

    ctx.start();
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);
}
