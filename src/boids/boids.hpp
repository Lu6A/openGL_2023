#pragma once

#include "strengths.hpp"

class Boid {
private:
    glm::vec3 m_position;
    glm::vec3 m_velocity;

    float     distanceBetween(Boid boid); // calcule la distance entre 2 boids
    glm::vec3 alignementRule(std::vector<Boid> boids, strengths strengths);
    glm::vec3 separationRule(std::vector<Boid> boids, strengths strengths);
    glm::vec3 cohesionRule(std::vector<Boid> boids, strengths strengths);

public:
    Boid(glm::vec3 position, glm::vec3 velocity); // constructeur paramétrique
    Boid(const p6::Context& ctx);                 // constructeur boid aléatoire
    ~Boid() = default;                            // destructeur
    p6::Angle getAngle();
    glm::vec3 getPosition();
    glm::vec3 getVelocity();

    void render(p6::Context& ctx);
    void applyRules(std::vector<Boid> boids, strengths strengths);

    void maxSpeed(strengths strengths);
};
