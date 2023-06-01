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
#include "img/src/Image.h"
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

    // bool leftRot  = false;
    // bool rightRot = false;
    // bool upRot    = false;
    // bool downRot  = false;

    bool leftMove  = false;
    bool rightMove = false;
    bool upMove    = false;
    bool downMove  = false;

    // ctx.mouse_scrolled = [&](p6::MouseScroll scroll) {
    //     camera.zoom(-scroll.dy);
    // };

    /////////////// GESTION DES SHADERS ///////////////

    Program program;

    ///////////// GESTION DES TEXTURES ///////////////

    img::Image nemoMap     = p6::load_image_buffer("assets/textures/clownfish.png");
    img::Image tortueMap   = p6::load_image_buffer("assets/textures/tortue.jpg");
    img::Image cubeMap     = p6::load_image_buffer("assets/textures/cube.jpg");
    img::Image anemone1Map = p6::load_image_buffer("assets/textures/anemone1.jpg");
    img::Image anemone2Map = p6::load_image_buffer("assets/textures/anemone2.jpg");
    img::Image ancreMap    = p6::load_image_buffer("assets/textures/ancre.jpg");
    img::Image plongeurMap = p6::load_image_buffer("assets/textures/plongeur.jpg");
    img::Image huitreMap   = p6::load_image_buffer("assets/textures/huitre.jpg");

    program._program.use();

    GLuint texNemo = 0;
    glGenTextures(1, &texNemo);

    glBindTexture(GL_TEXTURE_2D, texNemo);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, nemoMap.width(), nemoMap.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, nemoMap.data());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBindTexture(GL_TEXTURE_2D, 0);

    GLuint texTortue = 0;
    glGenTextures(1, &texTortue);

    glBindTexture(GL_TEXTURE_2D, texTortue);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tortueMap.width(), tortueMap.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, tortueMap.data());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBindTexture(GL_TEXTURE_2D, 0);

    GLuint texCube = 0;
    glGenTextures(1, &texCube);

    glBindTexture(GL_TEXTURE_2D, texCube);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, cubeMap.width(), cubeMap.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, cubeMap.data());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBindTexture(GL_TEXTURE_2D, 0);

    GLuint texAncre = 0;
    glGenTextures(1, &texAncre);

    glBindTexture(GL_TEXTURE_2D, texAncre);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, ancreMap.width(), ancreMap.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, ancreMap.data());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBindTexture(GL_TEXTURE_2D, 0);

    GLuint texAnemone1 = 0;
    glGenTextures(1, &texAnemone1);

    glBindTexture(GL_TEXTURE_2D, texAnemone1);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, anemone1Map.width(), anemone1Map.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, anemone1Map.data());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBindTexture(GL_TEXTURE_2D, 0);

    GLuint texAnemone2 = 0;
    glGenTextures(1, &texAnemone2);

    glBindTexture(GL_TEXTURE_2D, texAnemone2);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, anemone2Map.width(), anemone2Map.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, anemone2Map.data());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBindTexture(GL_TEXTURE_2D, 0);

    GLuint texPlongeur = 0;
    glGenTextures(1, &texPlongeur);

    glBindTexture(GL_TEXTURE_2D, texPlongeur);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, plongeurMap.width(), plongeurMap.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, plongeurMap.data());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBindTexture(GL_TEXTURE_2D, 0);

    GLuint texHuitre = 0;
    glGenTextures(1, &texHuitre);

    glBindTexture(GL_TEXTURE_2D, texHuitre);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, huitreMap.width(), huitreMap.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, huitreMap.data());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBindTexture(GL_TEXTURE_2D, 0);

    // glBindTexture(GL_TEXTURE_2D, 0);

    ///////////// GESTION DES OBJETS ///////////////

    // chargement des modèles////
    Model nemo = Model();
    nemo.loadModel("nemo.obj");

    Model tortue = Model();
    tortue.loadModel("turtle.obj");

    Model cube = Model();
    cube.loadModel("cube.obj");

    Model ancre = Model();
    ancre.loadModel("ancre.obj");

    Model anemone1 = Model();
    anemone1.loadModel("anemone1.obj");
    glEnable(GL_DEPTH_TEST);

    Model anemone2 = Model();
    anemone2.loadModel("anemone2.obj");
    glEnable(GL_DEPTH_TEST);

    Model plongeur = Model();
    plongeur.loadModel("plongeur.obj");
    glEnable(GL_DEPTH_TEST);

    Model huitre = Model();
    huitre.loadModel("huitre.obj");
    glEnable(GL_DEPTH_TEST);

    ////gestion des VBO////

    nemo.createVBO();
    nemo.createVAO();

    tortue.createVBO();
    tortue.createVAO();

    cube.createVBO();
    cube.createVAO();

    ancre.createVBO();
    ancre.createVAO();

    anemone1.createVBO();
    anemone1.createVAO();

    anemone2.createVBO();
    anemone2.createVAO();

    huitre.createVBO();
    huitre.createVAO();

    plongeur.createVBO();
    plongeur.createVAO();

    ///////////// GESTION DES BOIDS ///////////////
    Field field(50, ctx);

    ctx.update = [&]() {
        std::vector<glm::vec3> positions = field.fieldDraw(ctx);
        field.applyRules(strengths);

        program._program.use();

        ctx.imgui = [&]() {
            // Show a simple window
            ImGui::Begin("Test");
            ImGui::SliderFloat("distance Between Boids", &strengths.m_distance, 0.001, 10);
            ImGui::SliderInt("separation Strength", &(strengths.m_separationStrength), 0, 2);
            ImGui::SliderInt("cohesion Strength", &(strengths.m_cohesionStrength), 0, 10);
            ImGui::SliderInt("alignment Strength", &(strengths.m_alignmentStrength), 0, 10);
            ImGui::SliderFloat("maximum speed", &(strengths.m_vitesseMax), 0.001, 0.02);

            ImGui::End();
            // Show the official ImGui demo window
            // It is very useful to discover all the widgets available in ImGui
        };

        ///////////// GESTION DE LA CAMERA ///////////////

        if (rightMove)
        {
            mainCharacter.rotateLeft(-0.5f);
        }
        if (leftMove)
        {
            mainCharacter.rotateLeft(+0.5f);
        }
        if (upMove)
        {
            mainCharacter.moveFront(0.05f);
        }
        if (downMove)
        {
            mainCharacter.moveFront(-0.05f);
        }

        ctx.key_pressed = [&rightMove, &upMove, &leftMove, &downMove](p6::Key key) {
            if (key.logical == "d")
            {
                rightMove = true;
            }
            if (key.logical == "q")
            {
                leftMove = true;
            }
            if (key.logical == "z")
            {
                upMove = true;
            }
            if (key.logical == "s")
            {
                downMove = true;
            }
        };

        ctx.key_released = [&rightMove, &upMove, &leftMove, &downMove](p6::Key key) {
            if (key.logical == "d")
            {
                rightMove = false;
            }
            if (key.logical == "q")
            {
                leftMove = false;
            }
            if (key.logical == "z")
            {
                upMove = false;
            }
            if (key.logical == "s")
            {
                downMove = false;
            }
        };

        ctx.mouse_dragged = [&mainCharacter](const p6::MouseDrag& button) {
            mainCharacter.rotateLeft(button.delta.x * 5);
            mainCharacter.rotateUp(-button.delta.y * 5);
        };

        ctx.mouse_scrolled = [&](p6::MouseScroll scroll) {
            mainCharacter.moveFront(-scroll.dy);
        };

        glm::mat4 viewMatrix = mainCharacter.getViewMatrix();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // LIGHT

        program._program.use();

        glm::vec3 lightPosition     = glm::vec3(0.f, 20.f, 0.f);
        glm::vec3 lightViewPosition = glm::vec3(viewMatrix * glm::vec4(lightPosition, 1.f));
        glUniform3fv(program.uLightPosition2, 1, glm::value_ptr(lightViewPosition));

        glm::vec3 intensity = glm::vec3(100.f, 300.f, 500.f);
        glUniform3fv(program.uLightIntensity2, 1, glm::value_ptr(intensity));

        glm::vec3 lightDir     = glm::vec3(1.f, -1.f, 1.f);
        glm::vec3 lightViewDir = glm::vec3(viewMatrix * glm::vec4(lightDir, 1.f));
        glUniform3fv(program.uLightDir, 1, glm::value_ptr(lightViewDir));

        intensity = glm::vec3(1.f, 1.f, 1.f);
        glUniform3fv(program.uLightIntensity3, 1, glm::value_ptr(intensity));

        ///////////// GESTION DE LA CAMERA ///////////////
        // glm::mat4 viewMatrix = camera.getViewMatrix();

        glm::mat4 ProjMatrix   = glm::perspective(glm::radians(70.f), ctx.aspect_ratio(), 0.1f, 100.f);
        glm::mat4 MVMatrix     = glm::translate(glm::mat4(1.0), glm::vec3(0., -5., -5.));
        MVMatrix               = viewMatrix * MVMatrix;
        glm::mat4 NormalMatrix = glm::transpose(glm::inverse(MVMatrix));

        ///////////// GESTION DES OBJETS ///////////////

        ////////// DESSIN DES NEMO //////////

        glBindVertexArray(nemo.getVao());

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texNemo); // bind txt moon à la place
        glUniform1i(program.uTexture, 0);

        for (size_t i = 0; i < field.getBoids().size(); i++)
        {
            MVMatrix = glm::translate(glm::mat4{1.f}, {0.f, 0.f, 0.f}); // Translation
            MVMatrix = glm::translate(MVMatrix, positions[i]);          // Translation * Rotation * Translation
            MVMatrix = glm::scale(MVMatrix, glm::vec3{10.f});
            MVMatrix = viewMatrix * MVMatrix;
            // glm::mat4 MVMatrixBoids = glm::translate(glm::mat4{1.f}, {1.f, 1.f, -1.f}); // Translation
            // MVMatrixBoids           = glm::translate(MVMatrixBoids, positions[i]);      // Translation * Rotation * Translation
            // MVMatrixBoids           = glm::scale(MVMatrixBoids, glm::vec3{1., 1., 1.}); // Translation * Rotation * Translation * Scale
            // MVMatrixBoids           = MVMatrix * MVMatrixBoids;
            glUniformMatrix4fv(program.uMVPMatrix, 1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix));
            glUniformMatrix4fv(program.uMVMatrix, 1, GL_FALSE, glm::value_ptr(MVMatrix));
            glUniformMatrix4fv(program.uNormalMatrix, 1, GL_FALSE, glm::value_ptr(NormalMatrix));
            glDrawArrays(GL_TRIANGLES, 0, nemo.getVertices().size());
        };

        ////////// DESSIN DU CUBE //////////

        glBindVertexArray(cube.getVao());

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texCube); // bind txt cube à la place

        glUniform1i(program.uTexture, 0);
        MVMatrix = glm::translate(glm::mat4{1.f}, {0.f, 0.f, 0.f});
        MVMatrix = viewMatrix * MVMatrix;

        glUniformMatrix4fv(program.uMVPMatrix, 1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix));
        glUniformMatrix4fv(program.uMVMatrix, 1, GL_FALSE, glm::value_ptr(MVMatrix));
        glUniformMatrix4fv(program.uNormalMatrix, 1, GL_FALSE, glm::value_ptr(NormalMatrix));

        glUniform3fv(program.uKd, 1, glm::value_ptr(glm::vec3(1.5f, 0.5f, 0.3f)));
        glUniform3fv(program.uKs, 1, glm::value_ptr(glm::vec3(1.5f, 0.9f, 0.6f)));
        glUniform1f(program.uShininess, 0.9f);

        glDrawArrays(GL_TRIANGLES, 0, cube.getVertices().size());

        glBindVertexArray(0);

        ////////// DESSIN DES ANEMONES 1 //////////

        glBindVertexArray(anemone1.getVao());

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texAnemone1); // bind txt cube à la place

        glUniform1i(program.uTexture, 0);
        MVMatrix = glm::translate(glm::mat4{1.f}, {0.f, 0.f, 0.f});
        MVMatrix = viewMatrix * MVMatrix;

        glUniformMatrix4fv(program.uMVPMatrix, 1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix));
        glUniformMatrix4fv(program.uMVMatrix, 1, GL_FALSE, glm::value_ptr(MVMatrix));
        glUniformMatrix4fv(program.uNormalMatrix, 1, GL_FALSE, glm::value_ptr(NormalMatrix));
        glDrawArrays(GL_TRIANGLES, 0, anemone1.getVertices().size());

        glBindVertexArray(0);

        ////////// DESSIN DES ANEMONES 2 //////////

        glBindVertexArray(anemone2.getVao());
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texAnemone2); // bind txt cube à la place

        glUniform1i(program.uTexture, 0);
        MVMatrix = glm::translate(glm::mat4{1.f}, {0.f, 0.f, 0.f});
        MVMatrix = viewMatrix * MVMatrix;

        glUniformMatrix4fv(program.uMVPMatrix, 1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix));
        glUniformMatrix4fv(program.uMVMatrix, 1, GL_FALSE, glm::value_ptr(MVMatrix));
        glUniformMatrix4fv(program.uNormalMatrix, 1, GL_FALSE, glm::value_ptr(NormalMatrix));
        glDrawArrays(GL_TRIANGLES, 0, anemone2.getVertices().size());

        glBindVertexArray(0);

        ////////// DESSIN DES HUITRES //////////

        glBindVertexArray(huitre.getVao());

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texHuitre); // bind txt cube à la place

        glUniform1i(program.uTexture, 0);
        MVMatrix = glm::translate(glm::mat4{1.f}, {0.f, 0.f, 0.f});
        MVMatrix = viewMatrix * MVMatrix;

        glUniformMatrix4fv(program.uMVPMatrix, 1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix));
        glUniformMatrix4fv(program.uMVMatrix, 1, GL_FALSE, glm::value_ptr(MVMatrix));
        glUniformMatrix4fv(program.uNormalMatrix, 1, GL_FALSE, glm::value_ptr(NormalMatrix));
        glDrawArrays(GL_TRIANGLES, 0, huitre.getVertices().size());

        glBindVertexArray(0);

        ////////// DESSIN DE L'ANCRE  //////////

        glBindVertexArray(ancre.getVao());

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texAncre); // bind txt cube à la place

        glUniform1i(program.uTexture, 0);
        MVMatrix = glm::translate(glm::mat4{1.f}, {0.f, 0.f, 0.f});
        MVMatrix = viewMatrix * MVMatrix;

        glUniformMatrix4fv(program.uMVPMatrix, 1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix));
        glUniformMatrix4fv(program.uMVMatrix, 1, GL_FALSE, glm::value_ptr(MVMatrix));
        glUniformMatrix4fv(program.uNormalMatrix, 1, GL_FALSE, glm::value_ptr(NormalMatrix));
        glDrawArrays(GL_TRIANGLES, 0, ancre.getVertices().size());

        glBindVertexArray(0);

        ////////// DESSIN DU PLONGEUR //////////

        glBindVertexArray(plongeur.getVao());

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texPlongeur); // bind txt cube à la place

        glUniform1i(program.uTexture, 0);

        MVMatrix = glm::translate(glm::mat4{1.f}, {0.f, 0.f, 0.f});
        MVMatrix = viewMatrix * MVMatrix;

        glUniformMatrix4fv(program.uMVPMatrix, 1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix));
        glUniformMatrix4fv(program.uMVMatrix, 1, GL_FALSE, glm::value_ptr(MVMatrix));
        glUniformMatrix4fv(program.uNormalMatrix, 1, GL_FALSE, glm::value_ptr(NormalMatrix));
        glDrawArrays(GL_TRIANGLES, 0, plongeur.getVertices().size());

        glBindVertexArray(0);

        ////////// DESSIN DE LA TORTUE //////////

        glBindVertexArray(tortue.getVao());

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texTortue); // bind txt tortue à la place
        glUniform1i(program.uTexture, 0);

        MVMatrix = glm::translate(glm::mat4{1.f}, {0.f, 0.f, 0.f});
        MVMatrix = glm::translate(MVMatrix, mainCharacter.getPosition());
        MVMatrix = glm::scale(MVMatrix, glm::vec3{1.f});
        MVMatrix = viewMatrix * MVMatrix;

        glUniformMatrix4fv(program.uMVPMatrix, 1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix));
        glUniformMatrix4fv(program.uMVMatrix, 1, GL_FALSE, glm::value_ptr(MVMatrix));
        glUniformMatrix4fv(program.uNormalMatrix, 1, GL_FALSE, glm::value_ptr(NormalMatrix));

        glDrawArrays(GL_TRIANGLES, 0, tortue.getVertices().size());

        lightPosition     = mainCharacter.getPosition() + glm::vec3(0.f, 5.f, 0.f);
        lightViewPosition = glm::vec3(viewMatrix * glm::vec4(lightPosition, 1.f));
        glUniform3fv(program.uLightPosition, 1, glm::value_ptr(lightViewPosition));

        intensity = glm::vec3(10.f, 0.f, 20.f);
        glUniform3fv(program.uLightIntensity, 1, glm::value_ptr(intensity));

        glBindVertexArray(0);
        glBindTexture(GL_TEXTURE_2D, 0);

        camera.followCharacter(mainCharacter.getPosition());
    };

    ctx.start();

    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
    glDeleteTextures(1, &texNemo);
    glDeleteTextures(1, &texTortue);
}