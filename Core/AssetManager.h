//
// Created by 장지성 on 25. 8. 19..
//

#ifndef GLENGINE_ASSETMANAGER_H
#define GLENGINE_ASSETMANAGER_H

#include <memory>
#include <unordered_map>
#include <filesystem>

#include "Texture2D.h"

namespace glEngine::Core
{

class AssetManager {
public:
    static AssetManager& GetInstance() {
        static AssetManager instance;
        return instance;
    }

    std::shared_ptr<Texture2D> LoadTexture(const std::filesystem::path& textureName, const Texture2DParam& param);

    void Collect();
private:
    AssetManager() = default;

    std::unordered_map<std::string, std::weak_ptr<Texture2D>> m_texCache {};
};

};

#endif //GLENGINE_ASSETMANAGER_H