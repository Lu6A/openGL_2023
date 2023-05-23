#include <cstddef>
#include <vector>
#include "boids/boids.hpp"
#include "boids/field.hpp"
#include "boids/strengths.hpp"
#include "glimac/common.hpp"
#include "glimac/sphere_vertices.hpp"
#include "glm/ext/quaternion_trigonometric.hpp"
#include "glm/ext/scalar_constants.hpp"
#include "glm/fwd.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/random.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/trigonometric.hpp"
#include "p6/p6.h"

strengths strengths = {1, 1, 1, 0.06f, glm::length(glm::vec3(0.007f, 0.007f, 0.007f))};

int main()
{
    p6::Context ctx({800, 600, "Boids"});
    ctx.maximize_window();

    const p6::Shader shader = p6::load_shader(
        "shaders/3D.vs.glsl",
        "shaders/normals.fs.glsl"
    );

    shader.use();

    GLuint U_MVP_MATRIX_LOCATION    = glGetUniformLocation(shader.id(), "uMVPMatrix");
    GLuint U_MV_MATRIX_LOCATION     = glGetUniformLocation(shader.id(), "uMVMatrix");
    GLuint U_NORMAL_MATRIX_LOCATION = glGetUniformLocation(shader.id(), "uNormalMatrix");

    glEnable(GL_DEPTH_TEST);

    // creation du vbo
    GLuint vbo;
    glGenBuffers(1, &vbo);

    // binding du vbo
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    // debindage de la texture
    glBindTexture(GL_TEXTURE_2D, 0);

    // remplissage VBO
    const std::vector<glimac::ShapeVertex> vertices = glimac::sphere_vertices(1.f, 32, 16);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glimac::ShapeVertex), vertices.data(), GL_STATIC_DRAW);

    // debinder le VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // création du VAO
    GLuint vao;
    glGenVertexArrays(1, &vao);

    // binder le VAO
    glBindVertexArray(vao);

    // activation des attributs de vertex
    static constexpr GLuint VERTEX_ATTR_POSITION = 0;
    static constexpr GLuint VERTEX_NORMAL        = 1;

    glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
    glEnableVertexAttribArray(VERTEX_NORMAL);

    // spécification des attributs de vertex

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(VERTEX_ATTR_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(glimac::ShapeVertex), (const GLvoid*)offsetof(glimac::ShapeVertex, position));
    glVertexAttribPointer(VERTEX_NORMAL, 3, GL_FLOAT, GL_FALSE, sizeof(glimac::ShapeVertex), (const GLvoid*)offsetof(glimac::ShapeVertex, normal));
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    Field field(3, ctx);

    ctx.update = [&]() {
        shader.use();
        std::vector<glm::vec3> positions = field.fieldDraw(ctx);
        field.applyRules(strengths);

        std::cout << positions[0].x << " " << positions[0].y << " " << positions[0].z << std::endl;

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glBindVertexArray(vao);

        glm::mat4 ProjMatrix   = glm::perspective(glm::radians(70.f), 800.f / 600.f, 0.1f, 100.f);
        glm::mat4 MVMatrix     = glm::translate(glm::mat4(1), glm::vec3(0, 0, -5));
        glm::mat4 NormalMatrix = glm::transpose(glm::inverse(MVMatrix));

        for (size_t i = 0; i < 3; i++)
        {
            MVMatrix = glm::translate(glm::mat4{1.f}, {0.f, 0.f, 0.f}); // Translation
            MVMatrix = glm::translate(MVMatrix, positions[i]);          // Translation * Rotation * Translation
            MVMatrix = glm::scale(MVMatrix, glm::vec3{0.1f});

            // glm::mat4 MVMatrixBoids = glm::translate(glm::mat4{1.f}, {1.f, 1.f, -1.f}); // Translation
            // MVMatrixBoids           = glm::translate(MVMatrixBoids, positions[i]);      // Translation * Rotation * Translation
            // MVMatrixBoids           = glm::scale(MVMatrixBoids, glm::vec3{1., 1., 1.}); // Translation * Rotation * Translation * Scale
            // MVMatrixBoids           = MVMatrix * MVMatrixBoids;
            glUniformMatrix4fv(U_MVP_MATRIX_LOCATION, 1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix));
            glUniformMatrix4fv(U_MV_MATRIX_LOCATION, 1, GL_FALSE, glm::value_ptr(MVMatrix /*Boids*/));
            glUniformMatrix4fv(U_NORMAL_MATRIX_LOCATION, 1, GL_FALSE, glm::value_ptr(NormalMatrix));
            glDrawArrays(GL_TRIANGLES, 0, vertices.size());
        };

        // debinder le vbo
        glBindVertexArray(0);
    };

    ctx.start();
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);
}
