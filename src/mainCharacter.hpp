
#pragma once
#include <glm/glm.hpp>
#include "glimac/freeflyCamera.hpp"

class MainCharacter {
private:
    glm::vec3 m_position;
    glm::vec3 m_velocity;
    // FreeflyCamera camera;

public:
    MainCharacter()
        : m_position(0.f, 0.f, 0.f), m_velocity(0.f, 0.f, 0.f){};

    void      update();
    void      moveUp();
    void      moveDown();
    void      moveLeft();
    void      moveRight();
    void      moveForward();
    void      moveBackward();
    void      stopMovement();
    glm::vec3 getPosition();
};
