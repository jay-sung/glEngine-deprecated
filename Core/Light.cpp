//
// Created by 장지성 on 25. 8. 21..
//

#include "Light.h"

#include "Shader.h"

namespace glEngine::Core
{

void Light::Upload(const Shader& shader) const
{
    shader.UniformVec3(Shader::GetNameUniformField("uDirLight", "dir"), m_dirLight.dir);
    shader.UniformVec3(Shader::GetNameUniformField("uDirLight", "color"), m_dirLight.color);
    shader.UniformFloat(Shader::GetNameUniformField("uDirLight", "intensity"), m_dirLight.intensity);

    shader.UniformInt("uPointLightCount", static_cast<int>(m_pointLights.size()));
    for (int i = 0; i < m_pointLights.size(); i++)
    {
        shader.UniformVec3(Shader::GetNameUniformFieldByIndex("uPointLight", "pos", i), m_pointLights[i].pos);
        shader.UniformVec3(Shader::GetNameUniformFieldByIndex("uPointLight", "color", i), m_pointLights[i].color);
        shader.UniformFloat(Shader::GetNameUniformFieldByIndex("uPointLight", "intensity", i), m_pointLights[i].intensity);
        shader.UniformFloat(Shader::GetNameUniformFieldByIndex("uPointLight", "constant", i), m_pointLights[i].constant);
        shader.UniformFloat(Shader::GetNameUniformFieldByIndex("uPointLight", "linear", i), m_pointLights[i].linear);
        shader.UniformFloat(Shader::GetNameUniformFieldByIndex("uPointLight", "quadratic", i), m_pointLights[i].quadratic);
    }

    shader.UniformInt("uSpotLightCount", static_cast<int>(m_spotLight.size()));
    for (int i = 0; i <m_spotLight.size(); i++)
    {
        shader.UniformVec3(Shader::GetNameUniformFieldByIndex("uSpotLight", "pos", i), m_spotLight[i].pos);
        shader.UniformVec3(Shader::GetNameUniformFieldByIndex("uSpotLight", "dir", i), m_spotLight[i].dir);
        shader.UniformVec3(Shader::GetNameUniformFieldByIndex("uSpotLight", "color", i), m_spotLight[i].color);
        shader.UniformFloat(Shader::GetNameUniformFieldByIndex("uSpotLight", "intensity", i), m_spotLight[i].intensity);
        shader.UniformFloat(Shader::GetNameUniformFieldByIndex("uSpotLight", "cutOff", i), m_spotLight[i].cutOff);
        shader.UniformFloat(Shader::GetNameUniformFieldByIndex("uSpotLight", "outerCutOff", i), m_spotLight[i].outerCutOff);
        shader.UniformFloat(Shader::GetNameUniformFieldByIndex("uSpotLight", "constant", i), m_spotLight[i].constant);
        shader.UniformFloat(Shader::GetNameUniformFieldByIndex("uSpotLight", "linear", i), m_spotLight[i].linear);
        shader.UniformFloat(Shader::GetNameUniformFieldByIndex("uSpotLight", "quadratic", i), m_spotLight[i].quadratic);
    }
}


};