#include <cstddef>
#include <vector>
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

int main()
{
    // creation du contexte p6
    auto ctx = p6::Context{{1280, 720, "TP6 EX1"}};
    ctx.maximize_window();

    // // chargement des shaders
    // const p6::Shader shader = p6::load_shader(
    //     "shaders/3D.vs.glsl",
    //     "shaders/multitext3D.fs.glsl"
    // );
    // shader.use();

    // // récupération des locations de variables uniformes
    // GLuint U_MVP_MATRIX_LOCATION    = glGetUniformLocation(shader.id(), "uMVPMatrix");
    // GLuint U_MV_MATRIX_LOCATION     = glGetUniformLocation(shader.id(), "uMVMatrix");
    // GLuint U_NORMAL_MATRIX_LOCATION = glGetUniformLocation(shader.id(), "uNormalMatrix");
    // GLint  U_TEXTURE_1              = glGetUniformLocation(shader.id(), "uTexture1");
    // GLint  U_TEXTURE_2              = glGetUniformLocation(shader.id(), "uTexture2");

    // glEnable(GL_DEPTH_TEST);

    // // matrices ?
    // glm::mat4 ProjMatrix   = glm::perspective(glm::radians(70.0f), 800.0f / 600.0f, 0.1f, 100.0f); // param perspective(float fovy, float aspect, float znear, float far)
    // glm::mat4 MVMatrix     = glm::translate(glm::mat4(1), glm::vec3(0, 0, -5));
    // glm::mat4 NormalMatrix = glm::transpose(glm::inverse(MVMatrix));

    // // creation du vbo
    // GLuint vbo;
    // glGenBuffers(1, &vbo);

    // // chargement des images
    // img::Image texture_earth = p6::load_image_buffer(
    //     "assets/textures/EarthMap.jpg"
    // );

    // img::Image texture_clouds = p6::load_image_buffer(
    //     "assets/textures/CloudMap.jpg"
    // );

    // img::Image texture_moon = p6::load_image_buffer(
    //     "assets/textures/MoonMap.jpg"
    // );

    // GLuint textureEarth, textureClouds, textureMoon;

    // // binding du vbo et link des textures
    // glBindBuffer(GL_ARRAY_BUFFER, vbo);

    // glGenTextures(1, &textureEarth);
    // glBindTexture(GL_TEXTURE_2D, textureEarth); // Binding de la texture
    // glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture_earth.width(), texture_earth.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, texture_earth.data());
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // glBindTexture(GL_TEXTURE_2D, 0);

    // glGenTextures(1, &textureMoon);
    // glBindTexture(GL_TEXTURE_2D, textureMoon); // Binding de la texture
    // glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture_moon.width(), texture_moon.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, texture_moon.data());
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // glBindTexture(GL_TEXTURE_2D, 0);

    // glGenTextures(1, &textureClouds);
    // glBindTexture(GL_TEXTURE_2D, textureClouds); // Binding de la texture
    // glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture_clouds.width(), texture_clouds.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, texture_clouds.data());
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // glBindTexture(GL_TEXTURE_2D, 0);

    // // remplissage VBO
    // const std::vector<glimac::ShapeVertex> vertices = glimac::sphere_vertices(1.f, 32, 16);
    // glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glimac::ShapeVertex), vertices.data(), GL_STATIC_DRAW);

    // // debinder le VBO
    // glBindBuffer(GL_ARRAY_BUFFER, 0);

    // // création du VAO
    // GLuint vao;
    // glGenVertexArrays(1, &vao);

    // // binder le VAO
    // glBindVertexArray(vao);

    // // activation des attributs de vertex
    // static constexpr GLuint VERTEX_ATTR_POSITION = 0;
    // static constexpr GLuint VERTEX_NORMAL        = 1;
    // static constexpr GLuint TEXT_COORD           = 2;

    // glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
    // glEnableVertexAttribArray(VERTEX_NORMAL);
    // glEnableVertexAttribArray(TEXT_COORD);

    // // spécification des attributs de vertex
    // glBindBuffer(GL_ARRAY_BUFFER, vbo);
    // glVertexAttribPointer(VERTEX_ATTR_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(glimac::ShapeVertex), (const GLvoid*)offsetof(glimac::ShapeVertex, position));
    // glVertexAttribPointer(VERTEX_NORMAL, 3, GL_FLOAT, GL_FALSE, sizeof(glimac::ShapeVertex), (const GLvoid*)offsetof(glimac::ShapeVertex, normal));
    // glVertexAttribPointer(TEXT_COORD, 2, GL_FLOAT, GL_FALSE, sizeof(glimac::ShapeVertex), (const GLvoid*)offsetof(glimac::ShapeVertex, texCoords));
    // glBindBuffer(GL_ARRAY_BUFFER, 0);
    // glBindVertexArray(0);

    // uint nbLunes = 32;

    // // initialisation de la camera
    // TrackballCamera trackballCamera;

    // std::vector<glm::vec3> rotateAxes;
    // std::vector<glm::vec3> translations;

    // for (int i = 0; i < nbLunes; i++)
    // {
    //     rotateAxes.push_back(glm::sphericalRand(1.0f));
    //     translations.push_back(glm::sphericalRand(2.0f));
    // }

    // ///////////////////////////////////////////////
    // ///////////////BOUCLE D'AFFICHAGE//////////////
    // ///////////////////////////////////////////////

    // ctx.update = [&]() {
    //     ////gestion camera////
    //     glm::mat4 ViewMatrix = trackballCamera.getViewMatrix();

    //     // recupération des evenements//
    //     ctx.mouse_dragged = [&trackballCamera](const p6::MouseDrag& button) {
    //         trackballCamera.rotateLeft(button.delta.x * 50);
    //         trackballCamera.rotateUp(button.delta.y * 50);
    //     };

    //     // shader.use();

    //     // nettoyage de la fenêtre
    //     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //     glUniform1i(U_TEXTURE_1, 0);
    //     glUniform1i(U_TEXTURE_2, 1);
    //     glBindVertexArray(vao);

    //     // d'autres matrices ?

    //     ////// TERRE //////

    //     // on la dessine
    //     glm::mat4 Mrotate      = glm::rotate(MVMatrix, ctx.time(), glm::vec3(0.0f, 1.0f, 0.0f));
    //     glm::mat4 ProjMatrix   = glm::perspective(glm::radians(70.f), 800.f / 600.f, 0.1f, 100.f);
    //     glm::mat4 MVMatrix     = glm::translate(glm::mat4(1), glm::vec3(0, 0, -5));
    //     glm::mat4 NormalMatrix = glm::transpose(glm::inverse(MVMatrix));

    //     glUniformMatrix4fv(U_MVP_MATRIX_LOCATION, 1, GL_FALSE, glm::value_ptr(ProjMatrix * ViewMatrix));
    //     glUniformMatrix4fv(U_MV_MATRIX_LOCATION, 1, GL_FALSE, glm::value_ptr(ViewMatrix * Mrotate));
    //     glUniformMatrix4fv(U_NORMAL_MATRIX_LOCATION, 1, GL_FALSE, glm::value_ptr(NormalMatrix));

    //     // on charge les textures
    //     glActiveTexture(GL_TEXTURE0);
    //     glBindTexture(GL_TEXTURE_2D, textureEarth); // la texture earthTexture est bindée sur l'unité GL_TEXTURE0
    //     glActiveTexture(GL_TEXTURE1);
    //     glBindTexture(GL_TEXTURE_2D, textureClouds); // la texture cloudTexture est bindée sur l'unité GL_TEXTURE1

    //     glDrawArrays(GL_TRIANGLES, 0, vertices.size());

    //     // on décharge la texture de la terre localisée dans l'unité 0
    //     glActiveTexture(GL_TEXTURE0);

    //     ////// LUNES //////

    //     // on charge la texture de la Lune dans la "case 0"
    //     glBindTexture(GL_TEXTURE_2D, textureMoon);

    //     // on les dessine

    //     for (size_t i = 0; i < rotateAxes.size(); i++)
    //     {
    //         glm::mat4 MVMatrix2     = glm::translate(glm::mat4(1), glm::vec3(0, 0, -5));
    //         glm::mat4 NormalMatrix2 = glm::transpose(glm::inverse(MVMatrix2));
    //         MVMatrix2               = glm::rotate(MVMatrix2, ctx.time(), rotateAxes.at(i)); // Translation * Rotation
    //         MVMatrix2               = glm::translate(MVMatrix2, translations.at(i));        // Translation * Rotation * Translation
    //         MVMatrix2               = glm::scale(MVMatrix2, glm::vec3(0.2, 0.2, 0.2));      // Translation * Rotation * Translation * Scale
    //         glUniformMatrix4fv(U_MVP_MATRIX_LOCATION, 1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix2));
    //         glUniformMatrix4fv(U_MV_MATRIX_LOCATION, 1, GL_FALSE, glm::value_ptr(MVMatrix2));
    //         glUniformMatrix4fv(U_NORMAL_MATRIX_LOCATION, 1, GL_FALSE, glm::value_ptr(NormalMatrix2));
    //         glDrawArrays(GL_TRIANGLES, 0, vertices.size());
    //     }

    //     // debinder le vbo et toutes les textures
    //     glBindVertexArray(0);
    //     glActiveTexture(GL_TEXTURE0);
    //     glBindTexture(GL_TEXTURE_2D, 0);
    //     glActiveTexture(GL_TEXTURE1);
    //     glBindTexture(GL_TEXTURE_2D, 0);
    // };

    // // Should be done last. It starts the infinite loop.
    // ctx.start();

    // glDeleteTextures(1, &textureClouds);
    // glDeleteTextures(1, &textureEarth);
    // glDeleteTextures(1, &textureMoon);
    // glDeleteBuffers(1, &vbo);
    // glDeleteVertexArrays(1, &vao);
}