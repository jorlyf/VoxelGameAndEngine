#include <GL/glew.h>
#include "mesh.hpp"

vx::Mesh::Mesh(
    const float* vertexBuffer,
    const uint32_t vertexCount,
    const int32_t* attributes,
    const uint32_t primitiveType
)
{
    _vertexCount = vertexCount;
    _primitiveType = primitiveType;

    _vertexSize = 0;
    for (int32_t i = 0; attributes[i]; i++)
    {
        _vertexSize += attributes[i];
    }

    glGenVertexArrays(1, &_vao);
    glGenBuffers(1, &_vbo);

    glBindVertexArray(_vao);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glBufferData(GL_ARRAY_BUFFER, _vertexCount * sizeof(float) * _vertexSize, vertexBuffer, GL_STATIC_DRAW);

    int32_t offset = 0;
    for (int32_t i = 0; attributes[i]; i++)
    {
        const int32_t size = attributes[i];
        glVertexAttribPointer(i, size, GL_FLOAT, GL_FALSE, _vertexSize * sizeof(float), (GLvoid*)(offset * sizeof(float)));
        glEnableVertexAttribArray(i);
        offset += size;
    }

    glBindVertexArray(0);
}

vx::Mesh::~Mesh()
{
    glDeleteVertexArrays(1, &_vao);
    glDeleteBuffers(1, &_vbo);
}

void vx::Mesh::reload(const float* vertexBuffer, const uint32_t vertexCount)
{
    _vertexCount = vertexCount;

    glBindVertexArray(_vao);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glBufferData(GL_ARRAY_BUFFER, _vertexCount * sizeof(float) * _vertexSize, vertexBuffer, GL_STATIC_DRAW);
}

void vx::Mesh::draw() const
{
    glBindVertexArray(_vao);
    glDrawArrays(_primitiveType, 0, _vertexCount);
    glBindVertexArray(0);
}
