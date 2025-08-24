//
// Created by 장지성 on 25. 8. 19..
//

#include "Texture2D.h"

#include <iostream>
#include <ostream>

namespace glEngine::Core
{

std::expected<std::unique_ptr<Texture2D>, std::string> Texture2D::LoadFromFile(const std::string& path, const Texture2DParam& param)
{
    stbi_set_flip_vertically_on_load(param.IsFlipY);
    int w;
    int h;
    int n;

    unsigned char* data = stbi_load(path.c_str(), &w, &h, &n, 0);
    if (!data)
    {
        std::fprintf(stderr, "[Texture2D] Failed to load image: %s\n", path.c_str());
        return std::unexpected("Failed to load image");
    }

    GLenum src = (n == 1) ? GL_RED : (n == 3) ? GL_RGB : GL_RGBA;
    GLuint tex = 0;

    GLint internal = GL_R8;
    if (src == GL_RGB) {
        internal = param.IsSRGB ? GL_SRGB8 : GL_RGB8;
    } else if (src == GL_RGBA) {
        internal = param.IsSRGB ? GL_SRGB8_ALPHA8 : GL_RGBA8;
    }

    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexImage2D(GL_TEXTURE_2D, 0, internal, w, h, 0, src, GL_UNSIGNED_BYTE, data);
    if (param.IsGenerateMips)
    {
        glGenerateMipmap(GL_TEXTURE_2D);
    }

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, param.MinFilter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, param.MagFilter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, param.WrapS);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, param.WrapT);

    if (param.IsGenerateMips)
        glGenerateMipmap(GL_TEXTURE_2D);

    if (param.Anisotropy > 0.0f)
    {
        GLfloat maxAnisotropy = 0.0f;
        glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY, &maxAnisotropy);
        if (maxAnisotropy > 0.0f)
        {
            glTexParameterf
                (GL_TEXTURE_2D
                , GL_TEXTURE_MAX_ANISOTROPY
                , std::min(param.Anisotropy, maxAnisotropy));
        }
    }

    glBindTexture(GL_TEXTURE_2D, 0);
    stbi_image_free(data);

    auto resultTex = std::make_unique<Texture2D>();
    resultTex->m_tex = tex;
    resultTex->m_width = w;
    resultTex->m_height = h;
    resultTex->m_channels = n;
    resultTex->m_isSRGB = param.IsSRGB;

    return resultTex;
}

Texture2D::~Texture2D()
{
    if (m_tex)
    {
        glDeleteTextures(1, &m_tex);
    }
}

Texture2D::Texture2D(Texture2D&& rhs) noexcept
{
    *this = std::move(rhs);
}

Texture2D& Texture2D::operator=(Texture2D&& rhs) noexcept
{
    if (this != &rhs) {
        if (m_tex) glDeleteTextures(1, &m_tex);
        m_tex = rhs.m_tex;
        m_width = std::exchange(rhs.m_width, 0);
        m_height = std::exchange(rhs.m_height, 0);
        m_channels = std::exchange(rhs.m_channels, 0);
        m_isSRGB = std::exchange(rhs.m_isSRGB, false);
    }
    return *this;
}

};