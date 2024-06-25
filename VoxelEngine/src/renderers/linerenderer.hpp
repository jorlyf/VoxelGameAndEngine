#pragma once
#include <cstdint>
#include <memory>
#include <glm/glm.hpp>
#include "../graphics/mesh.hpp"

namespace vx
{
    class LineRenderer
    {
    public:
        static void addLine(
            const glm::vec3& start,
            const glm::vec3& end,
            const glm::vec4& rgba = glm::vec4(1, 0, 0, 1)
        );
        static void addCube();

        static void draw();

    private:
        static std::shared_ptr<float[]> _buffer;
        static uint32_t _vertexCount;
        static std::shared_ptr<Mesh> _mesh;
    };
}
