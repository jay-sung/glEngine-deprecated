//
// Created by 장지성 on 25. 8. 21..
//

#ifndef GLENGINE_LIGHT_H
#define GLENGINE_LIGHT_H

#include <vector>
#include <glm/glm.hpp>

namespace glEngine::Core
{

class Shader;

struct DirLight
{
    glm::vec3 dir { -0.3f, -1.0f, -0.2f };;
    glm::vec3 color { 1.0f,  1.0f,  1.0f  };;
    float intensity { 1.0f };

    DirLight() = default;
    DirLight(const glm::vec3& d, const glm::vec3& c, float i)
        : dir(d), color(c), intensity(i)
    {}
};

struct PointLight
{
    glm::vec3 pos { 0.0f, 0.0f, 0.0f };
    glm::vec3 color { 1.0f, 1.0f, 1.0f };
    float intensity { 1.0f };
    float constant { 1.0f };
    float linear { 0.09f };
    float quadratic { 0.032f };

    PointLight() = default;
    PointLight(const glm::vec3& p, const glm::vec3& c, float i,
               float kc=1.0f, float kl=0.09f, float kq=0.032f)
        : pos(p), color(c), intensity(i), constant(kc), linear(kl), quadratic(kq)
    {}
};

struct SpotLight
{
    glm::vec3 pos   { 0.0f };
    glm::vec3 dir   { 0.0f, 0.0f, -1.0f };
    glm::vec3 color { 1.0f };
    float intensity { 1.0f };
    float cutOff     { glm::cos(glm::radians(12.5f)) };   // cos θ 형태
    float outerCutOff{ glm::cos(glm::radians(17.5f)) };
    float constant   { 1.0f };
    float linear     { 0.09f };
    float quadratic  { 0.032f };
};

class Light {
public:
    Light() = default;

    void Upload(const Shader& shader) const;

    Light& SetDirLight(const DirLight& dirLight)
    {
        m_dirLight = dirLight;
        return *this;
    }

    Light& SetDirLight
        ( const glm::vec3& dir
        , const glm::vec3& color = {1,1,1}
        , float intensity = 1.0f)
    {
        m_dirLight = DirLight(dir, color, intensity);
        return *this;
    }

    Light& ClearPoints()
    {
        m_pointLights.clear();
        return *this;
    }

    Light& AddPoint(const PointLight& pl)
    {
        m_pointLights.push_back(pl);
        return *this;
    }

    Light& AddPoint
        ( const glm::vec3& pos
        , const glm::vec3& color={1,1,1}
        , float intensity=1.0f
        , float c=1.0f, float l=0.09f, float q=0.032f)
    {
        m_pointLights.emplace_back(pos, color, intensity, c, l, q);
        return *this;
    }

    Light& AddSpot(const SpotLight& spotLight)
    {
        m_spotLight.emplace_back(spotLight);
        return *this;
    }

    Light& AddSpot
        ( const glm::vec3& pos
        , const glm::vec3& color={1,1,1}
        , float intensity=1.0f
        , const glm::vec3& dir={0,0,-1}
        , float innerDeg=12.5f, float outerDeg=17.5f
        , float c=1.0f, float l=0.09f, float q=0.032f)
    {
        m_spotLight.emplace_back(pos, dir, color, intensity, glm::cos(glm::radians(innerDeg)), glm::cos(glm::radians(outerDeg)), c, l, q);
        return *this;
    }

    [[nodiscard]] auto& GetDirLight() const { return m_dirLight; }
    [[nodiscard]] auto& GetPointLights() const { return m_pointLights; }

private:
    DirLight m_dirLight;
    std::vector<PointLight> m_pointLights;
    std::vector<SpotLight> m_spotLight;
};

};
#endif //GLENGINE_LIGHT_H