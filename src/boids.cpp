#include "boids.hpp"
#include <math.h>
#include <cmath>
#include <cstddef>
#include <iostream>
#include "boid.hpp"
#include "glm/ext/quaternion_geometric.hpp"
#include "glm/fwd.hpp"
#include "glm/glm.hpp"
#include "strengths.hpp"

// constructeur paramétrique

Boid3D::Boid3D(glm::vec3 position, glm::vec3 velocity)
    : m_position(position), m_velocity(velocity)
{
}

Boid3D::Boid3D(const p6::Context& ctx) // aléatoire
    : m_position(glm::vec3(p6::random::number(-ctx.aspect_ratio(), ctx.aspect_ratio()), p6::random::number(-1.f, 1.f))), m_velocity(glm::vec3(p6::random::number(-0.005, 0.005), p6::random::number(-0.005, 0.005)))
{
}

void Boid3D::render(p6::Context& ctx)
{
    // p6::Angle theta = getAngle() + p6::Angle(90_degrees);
    ctx.fill          = {1, 0.2, 0.2};
    ctx.stroke_weight = 0.;
    ctx.equilateral_triangle(p6::Center{m_position}, p6::Radius{0.05f}, getAngle());

    //  donne les nouveaux coordonnées en fonction des vélocités
    m_position += m_velocity;

    // // pour la continuité sur l'axe x;
    if (std::abs(m_position.x) > ctx.aspect_ratio())
    {
        m_position.x = -m_position.x; // si ça arrive sur un bord, ça repart du bord opposé
    }

    // pour la continuité sur l'axe y;
    if (std::abs(m_position.y) > 1)
    {
        m_position.y = -m_position.y; // si ça arrive sur un bord, ça repart du bord opposé
    }
}

float Boid3D::distanceBetween(Boid3D boid)
{
    return glm::distance(m_position, boid.m_position);
}

p6::Angle Boid3D::getAngle()
{
    return p6::Angle(m_velocity);
}

glm::vec3 Boid3D::getPosition()
{
    return m_position;
}

glm::vec3 Boid3D::getVelocity()
{
    return m_velocity;
}

void Boid3D::setVelocity(glm::vec3 velocity)
{
    // m_velocity = glm::normalize(velocity);
    m_velocity = velocity;
}

glm::vec3 Boid3D::alignementRule(std::vector<Boid3D> boids, float dist)
{
    glm::vec3 alignVec{0.f};
    size_t    count = 0;
    for (auto& boid : boids) // équivaut à 'for (size_t i = 0; i < boids.size(); i++)'
    {
        if (boid.distanceBetween(*this) < dist) // équivaut à  'if (boids[i].distanceBetween(*this) < dist)'
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

glm::vec3 Boid3D::separationRule(std::vector<Boid3D> boids, float dist)
{
    glm::vec3 separationVec{0.f};
    size_t    count = 0;
    for (auto& boid : boids)
    {
        if (boid.distanceBetween(*this) < dist) // équivaut à  'if (boids[i].distanceBetween(*this) < dist)'
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

glm::vec3 Boid3D::cohesionRule(std::vector<Boid3D> boids, float dist)
{
    glm::vec3 cohesionVec{0.f};
    size_t    count = 0;
    for (auto& boid : boids)
    {
        if (boid.distanceBetween(*this) < dist) // équivaut à  'if (boids[i].distanceBetween(*this) < dist)'
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

void Boid3D::applyRules(std::vector<Boid3D> boids, float dist, strengths strengths)
{
    this->m_velocity += this->separationRule(boids, dist) * static_cast<float>(strengths.m_separationStrength);
    this->m_velocity += this->alignementRule(boids, dist) * static_cast<float>(strengths.m_alignmentStrength);
    this->m_velocity += this->cohesionRule(boids, dist) * static_cast<float>(strengths.m_cohesionStrength);

    this->maxSpeed();
}

void Boid3D::maxSpeed()
{
    float vitesseMax = glm::length(glm::vec3(0.007, 0.007));

    if (glm::length(this->m_velocity) > vitesseMax)
    {
        glm::vec3 normalized_vec = glm::normalize(this->m_velocity);
        this->m_velocity         = normalized_vec * vitesseMax;
    }
}
