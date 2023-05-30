#include "mainCharacter.hpp"
#include <math.h>

void MainCharacter::update()
{
    m_position += m_velocity;
    // camera.followCharacter(m_position);
    //     std::cout << "New position: (" << m_position.x << ", " << m_position.y << ", " << m_position.z << ")" << std::endl;
}

void MainCharacter::moveUp()
{
    m_velocity.y = 0.05f;
}

void MainCharacter::moveDown()
{
    m_velocity.y = -0.05f;
}

void MainCharacter::moveLeft()
{
    m_velocity.x = -0.05f;
}

void MainCharacter::moveRight()
{
    m_velocity.x = 0.05f;
}

void MainCharacter::moveForward()
{
    m_velocity.z = -0.05f;
}

void MainCharacter::moveBackward()
{
    m_velocity.z = 0.05f;
}

void MainCharacter::stopMovement()
{
    m_velocity = glm::vec3(0.0f, 0.0f, 0.0f);
}

glm::vec3 MainCharacter::getPosition()
{
    return m_position;
}