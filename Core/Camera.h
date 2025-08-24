//
// Created by 장지성 on 25. 8. 18..
//

#ifndef GLENGINE_CAMERA_H
#define GLENGINE_CAMERA_H

#include <algorithm>
#include <glfw/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace glEngine::Core
{

class Camera {
public:
    explicit Camera
        (glm::vec3 pos
        , float yaw = -90.0f
        , float pitch = 0.0f
        , float fov = 60.0f
        , float nearZ = 0.1f
        , float farZ = 1000.0f);

    void Update(GLFWwindow* window, float deltaTime, int frameBufferWidth, int frameBufferHeight);

    [[nodiscard]] auto GetView() const { return glm::lookAt(m_pos, m_pos + m_front, m_up); }
    [[nodiscard]] auto GetProjection(float aspect) const { return glm::perspective(glm::radians(m_fov), std::max(0.0001f, aspect), m_nearZ, m_farZ); }
    [[nodiscard]] auto GetPos() const { return m_pos; }
    [[nodiscard]] auto GetFront() const { return m_front; }
private:
    void setPos(const glm::vec3& pos) { m_pos = pos; }
    void setYaw(float yaw) { m_yaw = yaw; recomputeVectors(); }
    void setPitch(float pitch) { m_pitch = std::clamp(pitch, -89.0f, 89.0f); recomputeVectors(); }
    void setFov(float fov) { m_fov = std::clamp(fov, 15.0f, 100.0f); recomputeVectors(); }
    void recomputeVectors();

    glm::vec3 m_pos{};
    glm::vec3 m_front {0.0f, 0.0f, -1.0f };
    glm::vec3 m_right {1.0f, 0.0f, 0.0f };
    glm::vec3 m_up {0.0f, 1.0f, 0.0f };
    glm::vec3 m_worldUp {0.0f, 1.0f, 0.0f };
    float m_yaw = -90.0f;
    float m_pitch = 0.0f;
    float m_fov = 60.0f;
    float m_nearZ = 0.1f;
    float m_farZ = 1000.0f;
    float m_moveSpeed = 3.0f;
    float m_mouseSensitivity = 3.0f;
    float m_zoomSpeed = 2.0f;
    bool m_rotating = false;
    bool m_firstMove = true;
    double m_lastX = 0.0f;
    double m_lastY = 0.0f;
};

};
#endif //GLENGINE_CAMERA_H