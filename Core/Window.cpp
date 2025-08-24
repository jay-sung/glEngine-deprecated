//
// Created by 장지성 on 25. 8. 12..
//

#include <iostream>
#include <glad/glad.h>
#include <glfw/glfw3.h>

#include "Window.h"

namespace glEngine::Core
{

Window::Window(int width, int height, const char* title)
    : m_window(nullptr, glfwDestroyWindow)
{
    GLFWwindow* window = glfwCreateWindow(width, height, title, nullptr, nullptr);
    if (window == nullptr)
    {
        std::cout << "Failed to create window" << std::endl;
        throw std::runtime_error("Failed to create GLFW window");
    }
    m_window.reset(window);
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        throw std::runtime_error("Failed to initialize GLAD");
    }
}

void Window::ProcessInput() const
{
    if(glfwGetKey(m_window.get(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(m_window.get(), true);
}

void Window::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

};