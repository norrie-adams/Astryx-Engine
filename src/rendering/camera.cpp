#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp> 

Camera::Camera()
{
    position = glm::vec3(0.0f, 0.0f, 3.0f);
    front    = glm::vec3(0.0f, 0.0f, -1.0f);
    up       = glm::vec3(0.0f, 1.0f, 0.0f);
}

glm::mat4 Camera::getViewMatrix()
{
    return glm::lookAt(position, position + front, up);
}