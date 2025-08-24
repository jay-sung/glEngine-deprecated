//
// Created by 장지성 on 25. 8. 11
//

#ifndef GLENGINE_SHADER_H
#define GLENGINE_SHADER_H

#include <string>
#include <glad/glad.h>
#include <glm/glm.hpp>

namespace glEngine::Core
{

class Shader {
public:
    static std::string GetNameUniformFieldByIndex(const std::string& name, const std::string& field, int index);
    static std::string GetNameUniformField(const std::string& name, const std::string& field);

    explicit Shader(const char* vertexPath, const char* fragmentPath);
    ~Shader();

    void Use() const;

    void UniformBool(const std::string& name, bool value) const;
    void UniformInt(const std::string& name, int value) const;
    void UniformFloat(const std::string& name, float value) const;
    void UniformVec3(const std::string& name, glm::vec3 value) const;
    void UniformMat4(const std::string& name, const glm::mat4& mat) const;

    [[nodiscard]] GLint GetLocation(const std::string& name) const;
private:
    static void checkCompileErrors(GLuint shader, const std::string& type);

    GLuint m_program;
};

};

#endif //GLENGINE_SHADER_H