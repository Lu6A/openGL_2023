#include "field.hpp"
#include <math.h>
#include <cmath>
#include <cstddef>
#include <iostream>
#include "boid.hpp"
#include "boids.hpp"
#include "glm/glm.hpp"

// constructeur paramétrique
Field::Field(size_t n, const p6::Context& ctx)
    : N(n), area(0.2)
{
    for (size_t i = 0; i < n; i++)
    {
        boids.push_back(Boid3D(ctx)); // aléatoire
    }
}

void Field::fieldDraw(p6::Context& ctx) const
{
    for (size_t i = 0; i < N; i++)
    {
        boids[i].render(ctx);
    }
}

void Field::applyRules(float dist, strengths strengths)
{
    for (auto& boid : boids) // équivaut à 'for (size_t i = 0; i < boids.size(); i++)'
    {
        boid.applyRules(this->boids, dist, strengths);
    }
}
