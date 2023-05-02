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

// write a function that draw a cube with a texture in openGL (use the function glDrawArrays) and use it in the main function. It should have the size of aspect ratio of the window.

struct environmentProgram {
    p6::Shader m_Program;

    GLint uMVPMatrix;
    GLint uMVMatrix;
    GLint uNormalMatrix;
    GLint uEnvironmentTexture;

    environmentProgram()
        : m_Program{p6::load_shader("shaders/environment.vs.glsl", "shaders/environment.fs.glsl")}
    {
        uMVPMatrix    = glGetUniformLocation(m_Program.id(), "uMVPMatrix");
        uMVMatrix     = glGetUniformLocation(m_Program.id(), "uMVMatrix");
        uNormalMatrix = glGetUniformLocation(m_Program.id(), "uNormalMatrix");
        uEarthTexture = glGetUniformLocation(m_Program.id(), "uEarthTexture");
        uCloudTexture = glGetUniformLocation(m_Program.id(), "uCloudTexture");
    }
};

// void draw_cube(GLuint vbo, GLuint texture, glm::mat4 ProjMatrix, glm::mat4 MVMatrix, glm::mat4 NormalMatrix, GLint U_MVP_MATRIX_LOCATION, GLint U_MV_MATRIX_LOCATION, GLint U_NORMAL_MATRIX_LOCATION, GLint U_TEXTURE_1, GLint U_TEXTURE_2) {
//     // binding du vbo et link des textures
//     glBindBuffer(GL_ARRAY_BUFFER, vbo);
//     glBindTexture(GL_TEXTURE_2D, texture);
//
//     // envoi des matrices
//     glUniformMatrix4fv(U_MVP_MATRIX_LOCATION, 1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix));
//     glUniformMatrix4fv(U_MV_MATRIX_LOCATION, 1, GL_FALSE, glm::value_ptr(MVMatrix));
//     glUniformMatrix4fv(U_NORMAL_MATRIX_LOCATION, 1, GL_FALSE, glm::value_ptr(NormalMatrix));
//
//     // envoi des textures
//     glUniform1i(U_TEXTURE_1, 0);
//     glUniform1i(U_TEXTURE_2, 1);
//
//     // envoi des vertices
//     glEnableVertexAttribArray(0);
//     glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const GLvoid*) offsetof(ShapeVertex, position));
//     glEnableVertexAttribArray(1);
//     glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const GLvoid*) offsetof(ShapeVertex, normal));
//     glEnableVertexAttribArray(2);
//     glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const GLvoid*) offsetof(ShapeVertex, texCoords));
//
//     // dessin
//     glDrawArrays(GL_TRIANGLES, 0, 3 * sphere.getVertexCount());
//
//     // debinding
//     glDisableVertexAttribArray(0);
//     glDisableVertexAttribArray(1);
//     glDisableVertexAttribArray(2);
// }
