// #include "camera.hpp"

// void Camera::move(const glm::vec3& t)
// {
//     m_position += t;
// }

// // méthode qui permet de tourner dans la scène
// void Camera::rotate(const glm::vec3& r)
// {
//     m_orientation += r;
// }

// // méthode qui permet de récupérer la position de la caméra
// const glm::vec3& Camera::position() const
// {
//     return m_position;
// }

// // méthode qui permet de récupérer l'orientation de la caméra
// const glm::vec3& Camera::orientation() const
// {
//     return m_orientation;
// }

// // méthode qui permet de récupérer la matrice de vue
// glm::mat4 Camera::viewMatrix() const
// {
//     return glm::translate(glm::mat4(1.f), m_position) * glm::yawPitchRoll(m_orientation.y, m_orientation.x, m_orientation.z);
// }