#pragma once
#include <glm/glm.hpp>
#include "voxelchunk.hpp"

namespace vx
{
    class IVoxelChunkGenerator
    {
    public:
        virtual ~IVoxelChunkGenerator() { }

        virtual VoxelChunk* generate(const glm::ivec2& position) = 0;
    };
}
