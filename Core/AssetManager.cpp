//
// Created by 장지성 on 25. 8. 19..
//

#include "AssetManager.h"

#include <iostream>
#include <sstream>

namespace glEngine::Core
{

static std::string makeToKey(const std::filesystem::path& path, const Texture2DParam& param)
{
    std::filesystem::path canon = std::filesystem::weakly_canonical(path);
    std::ostringstream oss;
    oss << canon.string()
        << "|srgb=" << (param.IsSRGB ? 1 : 0)
        << "|mip=" << (param.IsGenerateMips ? 1 : 0)
        << "|min=" << (param.MinFilter)
        << "|mag=" << (param.MagFilter)
        << "|ws=" << (param.WrapS)
        << "|wt=" << (param.WrapT)
        << "|aniso=" << (param.Anisotropy)
        << "|flip=" << (param.IsFlipY);
    return oss.str();
}

std::shared_ptr<Texture2D> AssetManager::LoadTexture(const std::filesystem::path& path, const Texture2DParam& param)
{
    const std::string key = makeToKey(path, param);
    if (const auto hitCache = m_texCache.find(key); hitCache != m_texCache.end())
    {
        if (auto sharedTex = hitCache->second.lock())
        {
            return sharedTex;
        }
    }

    auto tex = Texture2D::LoadFromFile(path.string(), param);
    if (!tex.has_value()) {
        std::cerr << "Failed to load texture: " << path.string() << std::endl;
        return {};
    }

    auto sharedTex = std::shared_ptr<Texture2D>(std::move(tex.value()));
    m_texCache[key] = sharedTex;
    return sharedTex;
}

void AssetManager::Collect() {
    for (auto cache = m_texCache.begin(); cache != m_texCache.end();)
    {
        if (cache->second.expired())
        {
            cache = m_texCache.erase(cache);
        }
        else
        {
            ++cache;
        }
    }
}

};
