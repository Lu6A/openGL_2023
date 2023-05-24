#include "trackballCamera.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/trigonometric.hpp"

TrackballCamera::TrackballCamera(float Distance, float AngleX, float AngleY)
    : m_distance(Distance), m_AngleX(AngleX), m_AngleY(AngleY) {}

void TrackballCamera::moveFront(float delta)
{
    m_distance -= delta;
}

void TrackballCamera::rotateLeft(float degrees)
{
    m_AngleY += degrees;
}

void TrackballCamera::rotateUp(float degrees)
{
    m_AngleX += degrees;
}

void TrackballCamera::zoom(float delta)
{
    float ZOOM_SPEED   = 0.2f;
    float MAX_DISTANCE = 100.f;
    float MIN_DISTANCE = 0.1f;

    // Calculez le facteur de zoom en fonction de la variation de déplacement de la molette de la souris
    float zoomFactor = 1.0f + delta * ZOOM_SPEED;

    // Mettez à jour la distance de la caméra par rapport au point de focalisation en utilisant le facteur de zoom
    m_distance *= zoomFactor;

    // Assurez-vous que la distance reste dans une plage valide pour éviter les valeurs négatives ou nulles
    m_distance = std::fmax(m_distance, MIN_DISTANCE);
    m_distance = std::fmin(m_distance, MAX_DISTANCE);
}

glm::mat4 TrackballCamera::getViewMatrix() const
{
    glm::mat4 matrix =
        glm::translate(glm::mat4(1.f), glm::vec3(0, 0, -m_distance));
    matrix = glm::rotate(matrix, glm::radians(m_AngleX), glm::vec3(1, 0, 0));
    matrix = glm::rotate(matrix, glm::radians(m_AngleY), glm::vec3(0, 1, 0));

    return matrix;
}