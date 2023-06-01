#include "boids.hpp"
#include <cmath>
#include "glm/ext/quaternion_trigonometric.hpp"
#include "glm/ext/scalar_constants.hpp"
#include "glm/fwd.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/random.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/trigonometric.hpp"
#include "p6/p6.h"

// constructeur paramétrique
Boid::Boid(glm::vec3 position, glm::vec3 velocity)
    : m_position(position), m_velocity(velocity)
{
}

Boid::Boid(const p6::Context& ctx) // aléatoire
    : m_position(glm::vec3(
        p6::random::number(-ctx.aspect_ratio(), ctx.aspect_ratio()),
        p6::random::number(-1.f, 1.f),
        p6::random::number(-1.f, 1.f)
    ))
    , m_velocity(glm::vec3(
          p6::random::number(-0.2f, 0.2f),
          p6::random::number(-0.2f, 0.2f),
          p6::random::number(-0.2f, 0.2f)
      ))
{
}

glm::vec3 Boid::render(p6::Context& ctx)
{
    // p6::Angle theta = getAngle() + p6::Angle(90_degrees);
    // ctx.fill          = {1, 0.2, 0.2};
    // ctx.stroke_weight = 0.;
    // ctx.equilateral_triangle(p6::Center{m_position}, p6::Radius{0.05f}, getAngle());

    //  donne les nouveaux coordonnées en fonction des vélocités
    m_position += m_velocity;

    if (m_position.x > 3.5f)
    {
        m_position.x = 3.5f;
        m_velocity.x *= -1;
    }
    else if (m_position.x < -3.5f)
    {
        m_position.x = -3.5f;
        m_velocity.x *= -1;
    }

    if (m_position.y > 3.8f)
    {
        m_position.y = 3.8f;
        m_velocity.y *= -1;
    }
    else if (m_position.y < -3.8f)
    {
        m_position.y = -3.8f;
        m_velocity.y *= -1;
    }

    if (m_position.z > 2.8f)
    {
        m_position.z = 2.8f;
        m_velocity.z *= -1;
    }
    else if (m_position.z < -2.8f)
    {
        m_position.z = -2.8f;
        m_velocity.z *= -1;
    }

    return m_position;
}

float Boid::distanceBetween(Boid boid)
{
    return glm::distance(m_position, boid.m_position);
}

p6::Angle Boid::getAngle()
{
    return p6::Angle(m_velocity);
}

glm::vec3 Boid::getPosition()
{
    return m_position;
}

glm::vec3 Boid::getVelocity()
{
    return m_velocity;
}

glm::vec3 Boid::alignementRule(std::vector<Boid> boids, strengths strengths)
{
    glm::vec3 alignVec{0.f};
    size_t    count = 0;
    for (auto& boid : boids) // équivaut à 'for (size_t i = 0; i < boids.size(); i++)'
    {
        if (boid.distanceBetween(*this) < strengths.m_distance) // équivaut à  'if (boids[i].distanceBetween(*this) < dist)'
        {
            glm::vec3 updateVel = glm::mix(this->m_velocity, boid.getVelocity(), 0.1);

            alignVec += (updateVel);
            count++;
        }
    }

    if (count > 0)
    {
        alignVec /= static_cast<float>(count);
    }
    return alignVec;
}

glm::vec3 Boid::separationRule(std::vector<Boid> boids, strengths strengths)
{
    glm::vec3 separationVec{0.f};
    size_t    count = 0;
    for (auto& boid : boids)
    {
        if (boid.distanceBetween(*this) < strengths.m_distance) // équivaut à  'if (boids[i].distanceBetween(*this) < dist)'
        {
            separationVec += (this->m_position - boid.getPosition()) / 1000.f;
            count++;
        }
    }

    if (count > 0)
    {
        separationVec /= static_cast<float>(count);
    }

    return separationVec;
}

glm::vec3 Boid::cohesionRule(std::vector<Boid> boids, strengths strengths)
{
    glm::vec3 cohesionVec{0.f};
    size_t    count = 0;
    for (auto& boid : boids)
    {
        if (boid.distanceBetween(*this) < strengths.m_distance) // équivaut à  'if (boids[i].distanceBetween(*this) < dist)'
        {
            cohesionVec += boid.m_velocity;
            count++;
        }
    }

    if (count > 0)
    {
        cohesionVec /= static_cast<float>(count);
    }

    return cohesionVec;
}

void Boid::applyRules(std::vector<Boid> boids, strengths strengths)
{
    this->m_velocity += this->separationRule(boids, strengths) * static_cast<float>(strengths.m_separationStrength);
    this->m_velocity += this->alignementRule(boids, strengths) * static_cast<float>(strengths.m_alignmentStrength);
    this->m_velocity += this->cohesionRule(boids, strengths) * static_cast<float>(strengths.m_cohesionStrength);

    this->maxSpeed(strengths);
}

void Boid::maxSpeed(strengths strengths)
{
    if (glm::length(this->m_velocity) > strengths.m_vitesseMax)
    {
        glm::vec3 normalized_vec = glm::normalize(this->m_velocity);
        this->m_velocity         = normalized_vec * strengths.m_vitesseMax;
    }
}
