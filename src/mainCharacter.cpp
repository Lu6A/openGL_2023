#include "mainCharacter.hpp"
#include <math.h>
#include "glm/gtc/matrix_transform.hpp"
#include "p6/p6.h"

void MainCharacter::setPosition(glm::vec3 posMainCharacter)
{
    m_position = posMainCharacter;
}

glm::vec3 MainCharacter::getPosition()
{
    return m_position;
}

float MainCharacter::getRotationAngle() const
{
    return m_RotationAngle;
}

void MainCharacter::setRotationAngle(float rotationAngle)
{
    m_RotationAngle = rotationAngle;
}

MainCharacter::MainCharacter()
    : m_position(glm::vec3(0., 0., 0.)), m_Phi(p6::PI), m_Theta(0.), m_RotationAngle(0.)
{
    this->computeDirectionVectors();
}

MainCharacter::MainCharacter(glm::vec3 position, float phi, float theta)
    : m_position(position), m_Phi(phi), m_Theta(theta)
{
    this->computeDirectionVectors();
}

void MainCharacter::computeDirectionVectors()
{
    m_FrontVector = glm::vec3(glm::cos(m_Theta) * glm::sin(m_Phi), glm::sin(m_Theta), glm::cos(m_Theta) * glm::cos(m_Phi));
    m_LeftVector  = glm::vec3(glm::sin(m_Phi + (p6::PI / 2)), 0, glm::cos(m_Phi + (p6::PI / 2)));
    m_UpVector    = glm::cross(m_FrontVector, m_LeftVector);
}

void MainCharacter::moveLeft(float t)
{
    m_position += t * m_LeftVector;
    computeDirectionVectors();
}
void MainCharacter::moveFront(float t)
{
    m_position += t * m_FrontVector;
    computeDirectionVectors();
}

void MainCharacter::rotateLeft(float degrees)
{
    m_Phi += glm::radians(degrees);
    computeDirectionVectors();
}
void MainCharacter::rotateUp(float degrees)
{
    m_Theta += glm::radians(degrees);
    computeDirectionVectors();
}

glm::mat4 MainCharacter::getViewMatrix() const
{
    return glm::lookAt(m_position + glm::vec3(0.0f, 0.0f, -5.0f), m_position + m_FrontVector, m_UpVector); // Position du personnage principal
}