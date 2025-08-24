cmake_minimum_required(VERSION 4.0)
project(glEngine)

set(CMAKE_CXX_STANDARD 23)

add_executable(glEngine main.cpp
        Core/Shader.cpp
        Core/Shader.h
        Core/App.cpp
        Core/App.h
        Core/Window.cpp
        Core/Window.h
        Core/Mesh.cpp
        Core/Mesh.h
        Core/Camera.cpp
        Core/Camera.h
        Core/Texture2D.cpp
        Core/Texture2D.h
        External/stb_image.cpp
        Core/AssetManager.cpp
        Core/AssetManager.h
        Core/Material.cpp
        Core/Material.h
        Core/Light.cpp
        Core/Light.h)

target_include_directories(glEngine PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/Core
    ${CMAKE_CURRENT_SOURCE_DIR}/External
)

find_package(glfw3 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(assimp CONFIG REQUIRED)
find_package(Stb REQUIRED)

target_include_directories(glEngine PRIVATE External/stb_image.h)
target_link_libraries(glEngine PRIVATE assimp::assimp)
target_link_libraries(glEngine PRIVATE glm::glm)
target_link_libraries(glEngine PRIVATE glfw)
target_link_libraries(glEngine PRIVATE glad::glad)
target_link_libraries(glEngine PRIVATE imgui::imgui)