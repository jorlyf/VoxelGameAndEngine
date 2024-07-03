#pragma once
#include "ivoxelchunkgenerator.hpp"

namespace vxg
{
    class ChunkGeneratorEllipse : public vx::IVoxelChunkGenerator
    {
    public:
        ChunkGeneratorEllipse(
            const uint16_t voxelId,
            const glm::ivec3& semiAxes,
            const glm::ivec3& center
        );
        virtual ~ChunkGeneratorEllipse();

        virtual vx::VoxelChunk* generate(const glm::ivec2& position) override;

    private:
        uint16_t _voxelId;
        glm::ivec3 _semiAxes;
        glm::ivec3 _center;

        bool isPositionInsideEllipse(const glm::ivec3& position) const;
    };
}
