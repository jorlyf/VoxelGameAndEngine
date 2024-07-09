#pragma once
#include "ivoxelchunkgenerator.hpp"

namespace vxg
{
    class ChunkGeneratorStandard : public vx::IVoxelChunkGenerator
    {
    public:
        virtual ~ChunkGeneratorStandard();

        virtual vx::VoxelChunk* generate(const glm::ivec2& position) override;
    };
}
