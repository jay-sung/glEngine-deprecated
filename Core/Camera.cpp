//
// Created by 장지성 on 25. 8. 18..
//

#include "Camera.h"

namespace glEngine::Core
{

Camera::Camera(glm::vec3 pos, float yaw, float pitch, float fov, float nearZ, float farZ)
    : m_pos(pos)
    , m_yaw(yaw)
    , m_pitch(pitch)
    , m_fov(fov)
    , m_nearZ(nearZ)
    , m_farZ(farZ)
{
    recomputeVectors();
}

void Camera::Update(GLFWwindow* window, float deltaTime, int frameBufferWidth, int frameBufferHeight)
{
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) m_pos += m_front * m_moveSpeed * deltaTime;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) m_pos -= m_front * m_moveSpeed * deltaTime;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) m_pos -= m_right * m_moveSpeed * deltaTime;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) m_pos += m_right * m_moveSpeed * deltaTime;
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) m_pos += m_worldUp * m_moveSpeed * deltaTime;
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) m_pos -= m_worldUp * m_moveSpeed * deltaTime;

    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
    {
        if (!m_rotating)
        {
            m_rotating = true;
            m_firstMove = true;
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        }
        double x;
        double y;
        glfwGetCursorPos(window, &x, &y);
        if (m_firstMove)
        {
            m_lastX = x;
            m_lastY = y;
            m_firstMove = false;
        }
        double dx = x - m_lastX;
        double dy = y - m_lastY;
        m_lastX = x;
        m_lastY = y;

        m_yaw += static_cast<float>(dx) * deltaTime * m_mouseSensitivity;
        m_pitch -= static_cast<float>(dy) * deltaTime * m_mouseSensitivity;
        m_pitch = std::clamp(m_pitch, -89.0f, 89.0f);
        recomputeVectors();
    }
    else if (m_rotating)
    {
        m_rotating = false;
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        m_firstMove = true;
    }

    (void)frameBufferWidth; (void)frameBufferHeight;
}

void Camera::recomputeVectors()
{
    float yawRadian = glm::radians(m_yaw);
    float pitchRadian = glm::radians(m_pitch);
    glm::vec3 front;
    front.x = cosf(pitchRadian) * cosf(yawRadian);
    front.y = sinf(pitchRadian);
    front.z = cosf(pitchRadian) * sinf(yawRadian);
    m_front = glm::normalize(front);
    m_right = glm::normalize(glm::cross(m_front, m_worldUp));
    m_up = glm::normalize(glm::cross(m_right, m_front));
}

};
