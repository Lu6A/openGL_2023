#pragma once

#include "boids.hpp"

class Field {
private:
    size_t            N;     // nombre de boids dans le fiels
    std::vector<Boid> boids; // vecteur qui prend les boids
    float             area;  // area autour d'un boid (ref pour appliquer les forces)

public:
    Field(size_t N, const p6::Context& ctx); // constructeur paramétrique
    ~Field() = default;

    std::vector<glm::vec3> fieldDraw(p6::Context& ctx);
    void                   applyRules(strengths strengths);
    std::vector<Boid>&     getBoids() { return boids; }
};
