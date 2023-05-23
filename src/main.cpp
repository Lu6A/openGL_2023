#include <iostream>
#include <vector>
#include "glimac/common.hpp"
#include "glimac/default_shader.hpp"
#include "glimac/sphere_vertices.hpp"
#include "glm/fwd.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "model.hpp"
#include "p6/p6.h"

int main()
{
    auto ctx = p6::Context{{1280, 720, "BOIDS"}};
    ctx.maximize_window();

    // load shaders
    const p6::Shader shader = p6::load_shader(
        "shaders/3D.vs.glsl",
        "shaders/normals.fs.glsl"
    );

    GLuint U_MVP_MATRIX    = glGetUniformLocation(shader.id(), "uMVPMatrix");
    GLuint U_MV_MATRIX     = glGetUniformLocation(shader.id(), "uMVMatrix");
    GLuint U_NORMAL_MATRIX = glGetUniformLocation(shader.id(), "uNormalMatrix");

    // activer le test de profondeur du GPU
    glEnable(GL_DEPTH_TEST);

    // TABLEAU DE VERTICES
    const std::vector<glimac::ShapeVertex>
        vertices = glimac::sphere_vertices(1.f, 32, 16);

    // CREATION DU VBO
    GLuint vbo;
    glGenBuffers(1, &vbo);

    // binding du vbo
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    // remplissage VBO
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glimac::ShapeVertex), vertices.data(), GL_STATIC_DRAW);

    // debinder le VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // création du vao
    GLuint vao;
    glGenVertexArrays(1, &vao);

    // binder le VAO
    glBindVertexArray(vao);

    // activation des attributs de vertex
    static constexpr GLuint VERTEX_ATTR_POSITION  = 0;
    static constexpr GLuint VERTEX_ATTR_NORMAL    = 1;
    static constexpr GLuint VERTEX_ATTR_TEXCOORDS = 2;

    glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
    glEnableVertexAttribArray(VERTEX_ATTR_NORMAL);
    glEnableVertexAttribArray(VERTEX_ATTR_TEXCOORDS);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    glVertexAttribPointer(VERTEX_ATTR_POSITION, 2, GL_FLOAT, GL_FALSE, sizeof(glimac::ShapeVertex), (const GLvoid*)offsetof(glimac::ShapeVertex, position)); // specification des attributs de vertex

    glVertexAttribPointer(VERTEX_ATTR_NORMAL, 2, GL_FLOAT, GL_FALSE, sizeof(glimac::ShapeVertex), (const GLvoid*)offsetof(glimac::ShapeVertex, normal));

    glVertexAttribPointer(VERTEX_ATTR_TEXCOORDS, 2, GL_FLOAT, GL_FALSE, sizeof(glimac::ShapeVertex), (const GLvoid*)offsetof(glimac::ShapeVertex, texCoords));

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    Model mouche = Model();

    mouche.loadModel("fly.obj");

    ctx.update = [&]() {
        shader.use();
        glClearColor(0.f, 0.f, 0.f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glBindVertexArray(vao);

        glm::mat4 VMatrix = glm::mat4(1);

        glm::mat4 ProjMatrix   = glm::perspective(glm::radians(70.f), ctx.aspect_ratio(), 0.1f, 100.f);
        glm::mat4 MMatrix      = glm::translate(glm::mat4(1), glm::vec3(0, 0, -5));
        glm::mat4 MVMatrix     = VMatrix * MMatrix;
        glm::mat4 NormalMatrix = glm::transpose(glm::inverse(MVMatrix));

        glUniformMatrix4fv(U_MVP_MATRIX, 1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix));
        glUniformMatrix4fv(U_MV_MATRIX, 1, GL_FALSE, glm::value_ptr(MVMatrix));
        glUniformMatrix4fv(U_NORMAL_MATRIX, 1, GL_FALSE, glm::value_ptr(NormalMatrix));

        // glBindTexture(GL_TEXTURE_2D, textures);
        // glUniform1i(UTEXTURE, 0);

        glDrawArrays(GL_TRIANGLES, 0, vertices.size());

        // glBindTexture(GL_TEXTURE_2D, 0);
        glBindVertexArray(0);
    };

    // Should be done last. It starts the infinite loop.
    ctx.start();

    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);
}
