#include "Camera.h"

Camera::Camera()
    : m_pos(0,0,0), m_viewDir(0,0,-1),
    m_U(1,0,0), m_V(0,1,0), m_W(0,0,1),
    aspectRatio(1.0)
    {}

glm::mat4 Camera::getViewMatrix(){
    glm::mat4 M_view = glm::lookAt(m_pos, m_pos - m_W, m_V);
    return M_view;
}

glm::mat4 Camera::getPerspectiveMatrix(){
    glm::mat4 perspMat = glm::perspective(glm::radians(45.0f), aspectRatio, 5.0f, -5.0f);
    return perspMat;
}

glm::mat4 Camera::getOrthographicMatrix(){
    float halfWidth = 15.0 / 2.0;
    float halfHeight = halfWidth / aspectRatio;

    glm::mat4 orthoMatrix = glm::ortho(-halfWidth, halfWidth, -halfHeight, halfHeight, -5.0f, 5.0f);
    return orthoMatrix;
}

void Camera::setPosition(glm::vec3 pos){
    m_pos = pos;
}