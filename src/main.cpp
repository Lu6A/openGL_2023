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

    program._program.use();

    ///////////// GESTION DES OBJETS ///////////////

    ////chargement des modèles////
    Model mouche = Model();
    mouche.loadModel("fly.obj");

    glEnable(GL_DEPTH_TEST);

    ////gestion des VBO////

    mouche.createVBO();
    mouche.createVAO();

    ///////////// GESTION DES BOIDS ///////////////
    Field field(50, ctx);

    ctx.update = [&]() {
        std::vector<glm::vec3> positions = field.fieldDraw(ctx);
        field.applyRules(strengths);

        program._program.use();

        ///////////// GESTION DE LA CAMERA ///////////////
        glm::mat4 viewMatrix = camera.getViewMatrix();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 ProjMatrix   = glm::perspective(glm::radians(70.f), 800.f / 600.f, 0.1f, 100.f);
        glm::mat4 MVMatrix     = glm::translate(glm::mat4(1), glm::vec3(0, 0, -5));
        glm::mat4 NormalMatrix = glm::transpose(glm::inverse(MVMatrix));

        glBindVertexArray(mouche.get_vao());

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
            glUniformMatrix4fv(program.uMVPMatrix, 1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix));
            glUniformMatrix4fv(program.uMVMatrix, 1, GL_FALSE, glm::value_ptr(MVMatrix));
            glUniformMatrix4fv(program.uNormalMatrix, 1, GL_FALSE, glm::value_ptr(NormalMatrix));
            glDrawArrays(GL_TRIANGLES, 0, mouche.getVertices().size());
        };

        // debinder le vbo
        glBindVertexArray(0);
    };

    ctx.start();
}
