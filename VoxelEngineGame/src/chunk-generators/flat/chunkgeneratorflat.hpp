#pragma once
#include "ivoxelchunkgenerator.hpp"

namespace vxg
{
    class ChunkGeneratorFlat : public vx::IVoxelChunkGenerator
    {
    public:
        virtual ~ChunkGeneratorFlat();

        virtual vx::VoxelChunk* generate(const glm::ivec2& position) override;
    };
}
