#pragma once
#include <GLFW/glfw3.h>
#include <cstdint>

namespace vx
{
    class Mesh
    {
    public:
        Mesh(
            const float* vertexBuffer,
            const uint32_t vertexCount,
            const int32_t* attributes,
            const uint32_t primitiveType = GL_TRIANGLES
        );
        ~Mesh();

        void reload(const float* vertexBuffer, const uint32_t vertexCount);
        void draw() const;

    private:
        uint32_t _vertexCount;
        uint32_t _vao;
        uint32_t _vbo;
        uint32_t _primitiveType;
        uint32_t _vertexSize;
    };
}
