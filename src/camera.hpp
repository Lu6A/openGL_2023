// #pragma once

// #include <glm/glm.hpp>

// // code une classe camera qui permet de se déplacer dans la scène grâce aux flèches du clavier
// class Camera {
// private:
//     // position de la caméra
//     glm::vec3 m_position = glm::vec3(0.f, 0.f, 0.f);
//     // orientation de la caméra
//     glm::vec3 m_orientation = glm::vec3(0.f, 0.f, 0.f);

// // public:
//     // constructeur
//     Camera() = default;
//     // destructeur
//     ~Camera() = default;

//     // méthode qui permet de se déplacer dans la scène
//     void move(const glm::vec3& t);

//     // méthode qui permet de tourner dans la scène
//     void rotate(const glm::vec3& r);

//     // méthode qui permet de récupérer la position de la caméra
//     const glm::vec3& position() const;

//     // méthode qui permet de récupérer l'orientation de la caméra
//     const glm::vec3& orientation() const;

//     // méthode qui permet de récupérer la matrice de vue
//     glm::mat4 viewMatrix() const;
// };