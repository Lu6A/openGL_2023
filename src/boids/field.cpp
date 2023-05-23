#include "field.hpp"

// constructeur paramétrique
Field::Field(size_t n, const p6::Context& ctx)
    : N(n), area(0.2)
{
    for (size_t i = 0; i < n; i++)
    {
        boids.push_back(Boid(ctx)); // aléatoire
    }
}

std::vector<glm::vec3> Field::fieldDraw(p6::Context& ctx)
{
    std::vector<glm::vec3> positions;
    for (size_t i = 0; i < N; i++)
    {
        positions.push_back(boids[i].render(ctx));
    }

    return positions;
}

void Field::applyRules(strengths strengths)
{
    for (auto& boid : boids) // équivaut à 'for (size_t i = 0; i < boids.size(); i++)'
    {
        boid.applyRules(this->boids, strengths);
    }
}
