#include "Core/App.h"
#include "Core/Window.h"
#include "Core/Shader.h"
#include "Core/Mesh.h"
#include "Core/Camera.h"
#include "Core/Material.h"
#include "Core/AssetManager.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

#include "Light.h"

using namespace glEngine::Core;

int main() {
    try
    {
        App app;

        auto window = std::make_unique<Window>(800, 600, "Engine Example");
        auto shader = std::make_unique<Shader>("../Shader/vertex.glsl", "../Shader/frag.glsl");

        Camera camera {{0.0f, 0.0f, 3.0f}};

        Texture2DParam texPar;
        auto tex = AssetManager::GetInstance()
            .LoadTexture
                (std::filesystem::path{"../Asset/Texture/texture-example.jpeg"}
                , texPar);

        const std::vector<Vertex> vertices = {
            // Front (+Z)
            { {-0.5f,-0.5f, 0.5f}, {1,0,0}, {0,0}, {0,0, 1} },
            { { 0.5f,-0.5f, 0.5f}, {1,0,0}, {1,0}, {0,0, 1} },
            { { 0.5f, 0.5f, 0.5f}, {1,0,0}, {1,1}, {0,0, 1} },
            { {-0.5f, 0.5f, 0.5f}, {1,0,0}, {0,1}, {0,0, 1} },

            // Back (-Z)
            { {-0.5f,-0.5f,-0.5f}, {0,1,0}, {0,0}, {0,0,-1} },
            { {-0.5f, 0.5f,-0.5f}, {0,1,0}, {0,1}, {0,0,-1} },
            { { 0.5f, 0.5f,-0.5f}, {0,1,0}, {1,1}, {0,0,-1} },
            { { 0.5f,-0.5f,-0.5f}, {0,1,0}, {1,0}, {0,0,-1} },

            // Left (-X)
            { {-0.5f,-0.5f,-0.5f}, {0,0,1}, {0,0}, {-1,0,0} },
            { {-0.5f,-0.5f, 0.5f}, {0,0,1}, {1,0}, {-1,0,0} },
            { {-0.5f, 0.5f, 0.5f}, {0,0,1}, {1,1}, {-1,0,0} },
            { {-0.5f, 0.5f,-0.5f}, {0,0,1}, {0,1}, {-1,0,0} },

            // Right (+X)
            { { 0.5f,-0.5f, 0.5f}, {1,1,0}, {0,0}, { 1,0,0} },
            { { 0.5f,-0.5f,-0.5f}, {1,1,0}, {1,0}, { 1,0,0} },
            { { 0.5f, 0.5f,-0.5f}, {1,1,0}, {1,1}, { 1,0,0} },
            { { 0.5f, 0.5f, 0.5f}, {1,1,0}, {0,1}, { 1,0,0} },

            // Top (+Y)
            { {-0.5f, 0.5f, 0.5f}, {1,0,1}, {0,0}, {0, 1,0} },
            { { 0.5f, 0.5f, 0.5f}, {1,0,1}, {1,0}, {0, 1,0} },
            { { 0.5f, 0.5f,-0.5f}, {1,0,1}, {1,1}, {0, 1,0} },
            { {-0.5f, 0.5f,-0.5f}, {1,0,1}, {0,1}, {0, 1,0} },

            // Bottom (-Y)
            { {-0.5f,-0.5f,-0.5f}, {0,1,1}, {0,0}, {0,-1,0} },
            { { 0.5f,-0.5f,-0.5f}, {0,1,1}, {1,0}, {0,-1,0} },
            { { 0.5f,-0.5f, 0.5f}, {0,1,1}, {1,1}, {0,-1,0} },
            { {-0.5f,-0.5f, 0.5f}, {0,1,1}, {0,1}, {0,-1,0} },
        };

        const std::vector<GLuint> indices = {
            // Front
            0,  1,  2,  2,  3,  0,
           // Back
            4,  5,  6,  6,  7,  4,
           // Left
            8,  9, 10, 10, 11,  8,
           // Right
           12, 13, 14, 14, 15, 12,
           // Top
           16, 17, 18, 18, 19, 16,
           // Bottom
           20, 21, 22, 22, 23, 20
       };

        Material material{};
        material.AmbientK = glm::vec3(0.1f);
        material.DiffuseK = glm::vec3(0.7f);
        material.SpecularK = glm::vec3(0.5f);
        material.Shininess = 64.0f;
        material.IsUseTex    = true;
        material.AlbedoTex = tex ? tex->GetID() : 0;

        Light lights;
        lights
            .SetDirLight({ glm::normalize(glm::vec3(-0.3f, -1.0f, -0.2f)), {1,1,1}, 1.0f })
            .AddPoint( { 0.0f, 1.0f, 2.0f }, {1.0f, 0.95f, 0.85f}, 1.5f )      // 노란 전구 느낌
            .AddPoint( {-1.5f, 0.5f, 0.0f }, {0.6f, 0.8f, 1.0f }, 0.9f )
            .AddPoint( {1.5f, -0.5f, 0.0f }, {1.0f, 0.0f, 1.0f }, 0.9f )
            .AddPoint( {3.0f, 0.5f, -2.0f }, {0.0f, 0.8f, 1.0f }, 2.0f )
            .AddSpot ({0.0f, 0.0f, 0.0f}, {1,1,1}, 1.0f,
                  /*dir*/ glm::normalize(camera.GetFront()), /*inner*/ 12.5f, /*outer*/ 17.5f,
                  /*atten*/ 1.0f, 0.09f, 0.032f);

        const Mesh triangle(vertices, indices);
        std::vector<Mesh> meshes;
        meshes.emplace_back(triangle);

        app.Init(std::move(window), std::move(shader));
        app.Run([&](float deltaTime)
        {
            GLFWwindow* win = glfwGetCurrentContext();
            int w = 800, h = 600;
            if (win)
                glfwGetFramebufferSize(win, &w, &h);
            camera.Update(win, deltaTime, w, h);

            const auto& shader = app.GetShader();
            shader.UniformMat4("uModel", glm::mat4(1.0f));
            shader.UniformMat4("uView", camera.GetView());
            shader.UniformMat4("uProj", camera.GetProjection(static_cast<float>(w) / static_cast<float>(h)));
            shader.UniformVec3("uViewPos", camera.GetPos());
            shader.UniformFloat("uAlpha", 1.0f);

            lights.Upload(shader);

            material.Apply(shader);
            if (material.IsUseTex && material.AlbedoTex)
            {
                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, tex->GetID());
                shader.UniformInt("uAlbedo", 0);
            }

            app.Render(meshes);
        });
        app.Shutdown();
    }
    catch (const std::exception& e)
    {
        std::cout << e.what() << std::endl;
        return -1;
    }

    return 0;
}
