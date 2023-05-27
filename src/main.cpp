#include <iostream>
#include <vector>
#include "boids/boids.hpp"
#include "boids/field.hpp"
#include "boids/strengths.hpp"
#include "glimac/common.hpp"
#include "glimac/freeflyCamera.hpp"
#include "glimac/sphere_vertices.hpp"
#include "glm/ext/quaternion_trigonometric.hpp"
#include "glm/ext/scalar_constants.hpp"
#include "glm/fwd.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/trigonometric.hpp"
#include "loadingProgram.hpp"
#include "mainCharacter.hpp"
#include "model.hpp"
#include "p6/p6.h"

strengths strengths = {1, 1, 1, 0.06f, glm::length(glm::vec3(0.003f, 0.003f, 0.003f))};

int main()
{
    // creation du contexte p6
    auto ctx = p6::Context{{800, 600, "Boids"}};
    ctx.maximize_window();

    MainCharacter mainCharacter = MainCharacter();

    ///////////// GESTION DE LA CAMERA ///////////////

    FreeflyCamera camera;
    glm::mat4     viewCamera = camera.getViewMatrix();

    bool right_rot  = false;
    bool left_rot   = false;
    bool up_rot     = false;
    bool down_rot   = false;
    bool right_move = false;
    bool left_move  = false;
    bool front_move = false;
    bool back_move  = false;

    // ctx.mouse_scrolled = [&](p6::MouseScroll scroll) {
    //     camera.zoom(-scroll.dy);
    // };

    /////////////// GESTION DES SHADERS ///////////////

    Program program;

    ///////////// GESTION DES TEXTURES ///////////////

    program._program.use();

    ///////////// GESTION DES OBJETS ///////////////

    ////chargement des modèles////
    Model mouche = Model();
    mouche.loadModel("fly.obj");

    Model tortue = Model();
    tortue.loadModel("turtle.obj");

    glEnable(GL_DEPTH_TEST);

    ////gestion des VBO////

    mouche.createVBO();
    mouche.createVAO();

    tortue.createVBO();
    tortue.createVAO();

    ///////////// GESTION DES BOIDS ///////////////
    Field field(50, ctx);

    ctx.update = [&]() {
        std::vector<glm::vec3> positions = field.fieldDraw(ctx);
        field.applyRules(strengths);

        program._program.use();

        ///////////// GESTION DE LA CAMERA ///////////////

        if (right_rot)
        {
            camera.rotateLeft(-1.f);
        }
        if (left_rot)
        {
            camera.rotateLeft(1.f);
        }
        if (up_rot)
        {
            camera.rotateUp(1.f);
        }
        if (down_rot)
        {
            camera.rotateUp(-1.f);
        }
        if (left_move)
        {
            // camera.moveLeft(0.5f);
            mainCharacter.moveLeft();
        }
        if (right_move)
        {
            // camera.moveLeft(-0.5f);
            mainCharacter.moveRight();
        }
        if (front_move)
        {
            // camera.moveFront(-0.5f);
            mainCharacter.moveForward();
        }
        if (back_move)
        {
            // camera.moveFront(0.5f);
            mainCharacter.moveBackward();
        }

        ///////////// GESTION DES MOUVEMENTS DU PERSONNAGE ///////////////

        ctx.key_pressed = [&left_move, &right_move, &front_move, &back_move](p6::Key key) {
            if (key.physical == GLFW_KEY_LEFT)
            {
                left_move = true;
            }
            if (key.physical == GLFW_KEY_RIGHT)
            {
                right_move = true;
            }
            if (key.physical == GLFW_KEY_UP)
            {
                front_move = true;
            }
            if (key.physical == GLFW_KEY_DOWN)
            {
                back_move = true;
            }
        };

        ctx.key_released = [&left_move, &right_move, &front_move, &back_move, &mainCharacter](p6::Key key) {
            if (key.physical == GLFW_KEY_LEFT)
            {
                left_move = false;
                mainCharacter.stopMovement();
            }
            if (key.physical == GLFW_KEY_RIGHT)
            {
                right_move = false;
                mainCharacter.stopMovement();
            }
            if (key.physical == GLFW_KEY_UP)
            {
                front_move = false;
                mainCharacter.stopMovement();
            }
            if (key.physical == GLFW_KEY_DOWN)
            {
                back_move = false;
                mainCharacter.stopMovement();
            }
        };

        ctx.mouse_dragged = [&camera](const p6::MouseDrag& button) {
            camera.rotateLeft(button.delta.x * 5);
            camera.rotateUp(-button.delta.y * 5);
        };

        ctx.mouse_scrolled = [&](p6::MouseScroll scroll) {
            camera.moveFront(-scroll.dy);
        };

        glm::mat4 viewMatrix = camera.getViewMatrix();

        mainCharacter.update();

        ///////////// GESTION DE LA CAMERA ///////////////
        // glm::mat4 viewMatrix = camera.getViewMatrix();

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

        glBindVertexArray(tortue.get_vao());
        MVMatrix = glm::translate(glm::mat4{1.f}, {0.f, 0.f, 0.f});
        MVMatrix = glm::translate(MVMatrix, mainCharacter.getPosition());
        MVMatrix = glm::scale(MVMatrix, glm::vec3{0.05f});
        MVMatrix = viewMatrix * MVMatrix;

        glUniformMatrix4fv(program.uMVPMatrix, 1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix));
        glUniformMatrix4fv(program.uMVMatrix, 1, GL_FALSE, glm::value_ptr(MVMatrix));
        glUniformMatrix4fv(program.uNormalMatrix, 1, GL_FALSE, glm::value_ptr(NormalMatrix));
        glDrawArrays(GL_TRIANGLES, 0, tortue.getVertices().size());

        glBindVertexArray(0);

        camera.followCharacter(mainCharacter.getPosition());
    };

    ctx.start();
}
