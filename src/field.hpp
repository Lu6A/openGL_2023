#include <cstddef>
#include <vector>
#include "boid.hpp"
#include "boids.hpp"
#include "glm/fwd.hpp"
#include "list"
#include "p6/p6.h"
#include "strengths.hpp"

#pragma once

class Field {
public:
    size_t              N;     // nombre de boids dans le fiels
    std::vector<Boid3D> boids; // vecteur qui prend les boids
    float               area;  // area autour d'un boid (ref pour appliquer les forces)

public:
    Field(size_t N, const p6::Context& ctx); // paramétrique

    ~Field() = default;

    void fieldDraw(p6::Context& ctx) const;
    void applyRules(float dist, strengths strengths);
};
