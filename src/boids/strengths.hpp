#pragma once
#include "p6/p6.h"

struct strengths {
    int   m_separationStrength, m_cohesionStrength, m_alignmentStrength;
    float m_distance, m_vitesseMax;

    strengths(int separationStrength, int cohesionStrength, int alignmentStrength, float distance, float vitesseMax)
        : m_separationStrength(separationStrength), m_cohesionStrength(cohesionStrength), m_alignmentStrength(alignmentStrength), m_distance(distance), m_vitesseMax(vitesseMax)
    {
    }
};
