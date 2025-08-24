//
// Created by 장지성 on 25. 8. 21..
//

#ifndef GLENGINE_MATERIAL_H
#define GLENGINE_MATERIAL_H

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "Shader.h"

namespace glEngine::Core
{
    class Shader;

struct Material
{
    glm::vec3 AmbientK {0.05f, 0.05f, 0.05f};;
    glm::vec3 DiffuseK {1.00f, 1.00f, 1.00f};;
    glm::vec3 SpecularK {0.50f, 0.50f, 0.50f};
    float Shininess {64.0f};
    bool IsUseTex {false};
    GLuint AlbedoTex {0};

    void Apply(const Shader &shader) const
    {
        shader.UniformVec3(Shader::GetNameUniformField("uMaterial", "ambientK"), AmbientK);
        shader.UniformVec3(Shader::GetNameUniformField("uMaterial", "diffuseK"), DiffuseK);
        shader.UniformVec3(Shader::GetNameUniformField("uMaterial", "specularK"), SpecularK);
        shader.UniformFloat(Shader::GetNameUniformField("uMaterial", "shininess"), Shininess);
        shader.UniformBool(Shader::GetNameUniformField("uMaterial", "isUseTex"), IsUseTex);

        if (IsUseTex && AlbedoTex != 0)
        {
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, AlbedoTex);
            shader.UniformInt("uAlbedo", 0);
        }
    }
};

};

#endif //GLENGINE_MATERIAL_H