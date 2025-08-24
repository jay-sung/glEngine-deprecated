//
// Created by 장지성 on 25. 8. 12..
//

#ifndef GLENGINE_WINDOW_H
#define GLENGINE_WINDOW_H

#include <memory>
#include <glfw/glfw3.h>

struct GLFWwindow;

namespace glEngine::Core
{

class Window {
public:
    explicit Window(int width, int height, const char* title);
    ~Window() = default;

    void ProcessInput() const;

    [[nodiscard]] auto GetGLFWWindow() const { return m_window.get(); }
private:
    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);

    std::unique_ptr<GLFWwindow, void(*)(GLFWwindow*)> m_window;
};

};

#endif //GLENGINE_WINDOW_H