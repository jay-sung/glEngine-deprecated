//
// Created by 장지성 on 25. 8. 11..
//

#include "Shader.h"

#include <iostream>
#include <fstream>
#include <sstream>

#include <glm/gtc/type_ptr.hpp>

namespace glEngine::Core
{

std::string Shader::GetNameUniformFieldByIndex(const std::string& name, const std::string& field, int index)
{
    return name + "[" + std::to_string(index) + "]" + "." + field;
}

std::string Shader::GetNameUniformField(const std::string& name, const std::string& field)
{
    return name + "." + field;
}

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
    m_program = glCreateProgram();

    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vertexFile;
    std::ifstream fragmentFile;

    vertexFile.exceptions(std::ifstream::badbit | std::ifstream::failbit);
    fragmentFile.exceptions(std::ifstream::badbit | std::ifstream::failbit);
    try {
        vertexFile.open(vertexPath);
        fragmentFile.open(fragmentPath);

        std::stringstream vShaderStream, fShaderStream;
        vShaderStream << vertexFile.rdbuf();
        fShaderStream << fragmentFile.rdbuf();

        vertexFile.close();
        fragmentFile.close();

        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }
    catch (std::ifstream::failure& e) {
        std::cerr << e.what() << std::endl;
    }

    const char* vertexCodeC = vertexCode.c_str();
    const char* fragmentCodeC = fragmentCode.c_str();

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexCodeC, nullptr);
    glCompileShader(vertexShader);
    checkCompileErrors(vertexShader, "VERTEX");

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentCodeC, nullptr);
    glCompileShader(fragmentShader);
    checkCompileErrors(fragmentShader, "FRAGMENT");

    glAttachShader(m_program, vertexShader);
    glAttachShader(m_program, fragmentShader);
    glLinkProgram(m_program);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

Shader::~Shader()
{
    glDeleteProgram(m_program);
}

void Shader::Use() const
{
    glUseProgram(m_program);
}

void Shader::UniformBool(const std::string& name, bool value) const
{
    glUniform1i(GetLocation(name), static_cast<int>(value));
}

void Shader::UniformInt(const std::string &name, int value) const
{
    glUniform1i(GetLocation(name), value);
}

void Shader::UniformFloat(const std::string& name, float value) const
{
    glUniform1f(GetLocation(name), value);
}

void Shader::UniformVec3(const std::string& name, glm::vec3 value) const
{
    glUniform3f(GetLocation(name), value.x, value.y, value.z);
}

void Shader::UniformMat4(const std::string& name, const glm::mat4& mat) const
{
    glUniformMatrix4fv(GetLocation(name), 1, false, glm::value_ptr(mat));
}

GLint Shader::GetLocation(const std::string& name) const
{
    return glGetUniformLocation(m_program, name.c_str());
}

void Shader::checkCompileErrors(GLuint shader, const std::string& type)
{
    GLint success;
    GLchar infoLog[1024];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(shader, 1024, nullptr, infoLog);
        std::cerr << type << "::" << infoLog  << std::endl;
    }
}

};