//
// Created by 장지성 on 25. 8. 12..
//

#include "Mesh.h"

namespace glEngine::Core
{

Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<GLuint>& indices)
    : m_vertices(vertices)
    , m_indices(indices)
{
    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);

    glGenBuffers(1, &m_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData
        (GL_ARRAY_BUFFER
        , static_cast<GLsizeiptr>(vertices.size() * sizeof(Vertex))
        , vertices.data()
        , GL_STATIC_DRAW);

    glGenBuffers(1, &m_ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
    glBufferData
        (GL_ELEMENT_ARRAY_BUFFER
        , static_cast<GLsizeiptr>(indices.size() * sizeof(GLuint))
        , indices.data()
        , GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer
        (0
        , 3
        , GL_FLOAT
        , GL_FALSE
        , sizeof(Vertex)
        , reinterpret_cast<void*>(offsetof(Vertex, Position)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer
            (1
            , 3
            , GL_FLOAT
            , GL_FALSE
            , sizeof(Vertex)
            , reinterpret_cast<void*>(offsetof(Vertex, Color)));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer
            (2
            , 2
            , GL_FLOAT
            , GL_FALSE
            , sizeof(Vertex)
            , reinterpret_cast<void*>(offsetof(Vertex, UV)));
    glEnableVertexAttribArray(3);
    glVertexAttribPointer
            (3
            , 3
            , GL_FLOAT
            , GL_FALSE
            , sizeof(Vertex)
            , reinterpret_cast<void*>(offsetof(Vertex, Normal)));

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

Mesh::~Mesh() {
    if (m_ebo) glDeleteBuffers(1, &m_ebo);
    if (m_vbo) glDeleteBuffers(1, &m_vbo);
    if (m_vao) glDeleteVertexArrays(1, &m_vao);
}

Mesh::Mesh(Mesh&& rhs) noexcept
    : m_vao(std::exchange(rhs.m_vao, 0))
      , m_vbo(std::exchange(rhs.m_vbo, 0))
      , m_ebo(std::exchange(rhs.m_ebo, 0))
      , m_vertices(std::move(rhs.m_vertices))
      , m_indices(std::move(rhs.m_indices))
{}

Mesh& Mesh::operator=(Mesh&& rhs) noexcept
{
    if (this == &rhs) return *this;
    if (m_vao) glDeleteVertexArrays(1, &m_vao);
    if (m_vbo) glDeleteBuffers(1, &m_vbo);
    if (m_ebo) glDeleteBuffers(1, &m_ebo);

    m_vao = rhs.m_vao;
    m_vbo = rhs.m_vbo;
    m_ebo = rhs.m_ebo;
    m_vertices = std::move(rhs.m_vertices);
    m_indices = std::move(rhs.m_indices);
    return *this;
}

};