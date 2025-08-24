//
// Created by 장지성 on 25. 8. 11..
//

#include "App.h"

#include <memory>

#include <glfw/glfw3.h>

namespace glEngine::Core
{

App::App()
    : m_window(nullptr)
    , m_shader(nullptr)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
}

App::~App()
{
    glfwTerminate();
}

void App::Init(std::unique_ptr<Window> window, std::unique_ptr<Shader> shader)
{
    m_window = std::move(window);
    m_shader = std::move(shader);
}

void App::Run(const std::function<void(float deltaTime)>& tickFn)
{
    glEnable(GL_DEPTH_TEST);
    while (!glfwWindowShouldClose(m_window->GetGLFWWindow()))
    {
        const auto currentTime = static_cast<GLfloat>(glfwGetTime());
        m_deltaTime = currentTime - m_lastFrameTime;
        m_lastFrameTime = currentTime;

        m_window->ProcessInput();
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        tickFn(m_deltaTime);

        glfwSwapBuffers(m_window->GetGLFWWindow());
        glfwPollEvents();
    }
}

void App::Render(const std::vector<Mesh>& meshes) const
{
    m_shader->Use();
    for (const Mesh& mesh : meshes)
    {
        glBindVertexArray(mesh.GetVAO());
        glDrawElements
            (GL_TRIANGLES
            , mesh.GetIndexCount()
            , GL_UNSIGNED_INT
            , static_cast<void*>(0));
        glBindVertexArray(0);
    }
}

void App::Shutdown()
{
    m_window.reset();
    m_shader.reset();
}

};