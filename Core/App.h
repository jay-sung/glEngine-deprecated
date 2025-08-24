//
// Created by 장지성 on 25. 8. 11..
//

#ifndef GLENGINE_APP_H
#define GLENGINE_APP_H

#include <memory>
#include <vector>
#include <functional>

#include "Mesh.h"
#include "Shader.h"
#include "Window.h"

namespace glEngine::Core
{

class App {
public:
    explicit App();
    ~App();

    void Init(std::unique_ptr<Window> window, std::unique_ptr<Shader> shader);
    void Run(const std::function<void(float deltaTime)>& tickFn);
    void Render(const std::vector<Mesh>& meshes) const;
    void Shutdown();

    [[nodiscard]] const auto& GetWindow() const { return *m_window; };
    [[nodiscard]] const auto& GetShader() const { return *m_shader; };
private:
    std::unique_ptr<Window> m_window;
    std::unique_ptr<Shader> m_shader;
    float m_deltaTime = 0.0f;
    float m_lastFrameTime = 0.0f;
};

};

#endif //GLENGINE_APP_H