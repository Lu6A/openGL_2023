#pragma once

#include "glm/ext/matrix_transform.hpp"
#include "glm/ext/scalar_constants.hpp"
#include "glm/fwd.hpp"
#include "glm/glm.hpp"

class FreeflyCamera {
private:
    glm::vec3 m_position;
    float     m_phi;
    float     m_teta;
    glm::vec3 m_LeftVector;
    glm::vec3 m_FrontVector;
    glm::vec3 m_UpVector;
    float     m_distance;

    void computeDirectionVectors();

public:
    FreeflyCamera()
        : m_position(glm::vec3(0, 0, 0)), m_phi(glm::pi<float>()), m_teta(0), m_distance(5.f)
    {
        computeDirectionVectors();
    };

    void      moveLeft(float t);
    void      moveFront(float t);
    void      rotateLeft(float degrees);
    void      rotateUp(float degrees);
    glm::vec3 getPosition() const;

    void setDistance(float t) {}

    glm::mat4 getViewMatrix() const;
};