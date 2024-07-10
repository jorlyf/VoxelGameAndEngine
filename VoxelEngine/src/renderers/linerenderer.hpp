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
        struct LineVertex
        {
            glm::vec3 position;
            glm::vec4 color;
        };

        static std::shared_ptr<LineVertex[]> _vertices;
        static uint32_t _vertexCount;

        static std::shared_ptr<Mesh> _mesh;
    };
}
