//
// Created by 장지성 on 25. 8. 19..
//

#ifndef GLENGINE_TEXTURE2D_H
#define GLENGINE_TEXTURE2D_H

#include <memory>
#include <string>
#include <expected>
#include <glad/glad.h>
#include "stb_image.h"

namespace glEngine::Core
{

struct Texture2DParam
{
    bool IsSRGB = true;
    bool IsGenerateMips = true;
    GLint MinFilter = GL_LINEAR_MIPMAP_LINEAR;
    GLint MagFilter = GL_LINEAR;
    GLint WrapS = GL_REPEAT;
    GLint WrapT = GL_REPEAT;
    float Anisotropy = 0.0f;
    bool IsFlipY = true;
};

class Texture2D {
public:
    static std::expected<std::unique_ptr<Texture2D>, std::string>
        LoadFromFile(const std::string& path, const Texture2DParam& param);

    Texture2D() = default;
    ~Texture2D();
    Texture2D(const Texture2D&) = delete;
    Texture2D(Texture2D&& rhs) noexcept;

    Texture2D& operator=(const Texture2D&) = delete;
    Texture2D& operator=(Texture2D&& rhs) noexcept;

    [[nodiscard]] auto GetID() const { return m_tex; }
    [[nodiscard]] auto GetWidth() const { return m_width; }
    [[nodiscard]] auto GetHeight() const { return m_height; }
    [[nodiscard]] auto GetChannels() const { return m_channels; }
    [[nodiscard]] auto GetIsSRGB() const { return m_isSRGB; }
private:
    GLuint m_tex = 0;
    int m_width = 0;
    int m_height = 0;
    int m_channels = 0;
    bool m_isSRGB = false;
};

};

#endif //GLENGINE_TEXTURE2D_H