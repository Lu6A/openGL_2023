#pragma once
#include <glm/glm.hpp>

class MainCharacter {
private:
    glm::vec3 m_position;
    glm::vec3 m_velocity;
    float     m_Phi;   // coord spherique de F
    float     m_Theta; // coord spherique de F
    float     m_RotationAngle;

    glm::vec3 m_FrontVector; // vecteur F
    glm::vec3 m_LeftVector;  // vecteur L
    glm::vec3 m_UpVector;    // vecteur U

    void computeDirectionVectors();

public:
    MainCharacter();
    MainCharacter(glm::vec3 position, float phi, float theta);
    ~MainCharacter() = default;

    void setPosition(glm::vec3 posMainCharacter);

    glm::vec3 getPosition();
    void      setRotationAngle(float rotationAngle);
    float     getRotationAngle() const;

    void moveLeft(float t);
    void moveFront(float t);

    void rotateLeft(float degrees);
    void rotateUp(float degrees);

    glm::mat4 getViewMatrix() const;
};