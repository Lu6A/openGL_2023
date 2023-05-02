#include "glm/fwd.hpp"
#include "p6/p6.h"
#include "strengths.hpp"

#pragma once

class Boid3D {
private:
    glm::vec3 m_position;
    glm::vec3 m_velocity;

public:
    Boid3D(glm::vec3 position, glm::vec3 velocity);
    Boid3D(const p6::Context& ctx);
    ~Boid3D() = default;
    void      render(p6::Context& ctx);
    float     distanceBetween(Boid3D boid);
    p6::Angle getAngle();
    glm::vec3 getPosition();
    glm::vec3 getVelocity();
    void      setVelocity(glm::vec3 velocity);
    glm::vec3 alignementRule(std::vector<Boid3D> boids, float dist);
    glm::vec3 separationRule(std::vector<Boid3D> boids, float dist);
    glm::vec3 cohesionRule(std::vector<Boid3D> boids, float dist);
    void      applyRules(std::vector<Boid3D> boids, float dist, strengths strengths);
    void      maxSpeed();
};
