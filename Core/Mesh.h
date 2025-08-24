//
// Created by 장지성 on 25. 8. 12..
//

#ifndef GLENGINE_MESH_H
#define GLENGINE_MESH_H

#include <vector>
#include <glad/glad.h>
#include <glm/glm.hpp>

namespace glEngine::Core
{

struct Vertex
{
    glm::vec3 Position;
    glm::vec3 Color;
    glm::vec2 UV;
    glm::vec3 Normal;
};

class Mesh {
public:
    explicit Mesh(const std::vector<Vertex>& vertices, const std::vector<GLuint>& indices);
    ~Mesh();
    Mesh(const Mesh&) = default;
    Mesh(Mesh&& rhs) noexcept;

    Mesh& operator=(const Mesh&) = delete;
    Mesh& operator=(Mesh&& rhs) noexcept;

    [[nodiscard]] auto GetVAO() const { return m_vao; }
    [[nodiscard]] auto GetVBO() const { return m_vbo; }
    [[nodiscard]] auto GetEBO() const { return m_ebo; }
    [[nodiscard]] const auto& GetVertices() const  { return m_vertices; }
    [[nodiscard]] const auto& GetIndices() const { return m_indices; }
    [[nodiscard]] auto GetIndexCount() const { return static_cast<GLsizei>(m_indices.size()); }
private:
    GLuint m_vao{};
    GLuint m_vbo{};
    GLuint m_ebo{};
    std::vector<Vertex> m_vertices;
    std::vector<GLuint> m_indices;
};

};

#endif //GLENGINE_MESH_H