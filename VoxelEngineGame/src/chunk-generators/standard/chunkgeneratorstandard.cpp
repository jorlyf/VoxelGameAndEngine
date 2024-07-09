#include <glm/gtc/noise.hpp>
#include "chunkgeneratorstandard.hpp"

vxg::ChunkGeneratorStandard::~ChunkGeneratorStandard()
{
}

vx::VoxelChunk* vxg::ChunkGeneratorStandard::generate(const glm::ivec2& position)
{
    vx::VoxelChunk* chunk = new vx::VoxelChunk(position);

    for (int32_t x = 0; x < vx::VoxelChunk::SIZE; x++)
    {
        for (int32_t z = 0; z < vx::VoxelChunk::SIZE; z++)
        {
            for (int32_t y = 0; y < vx::VoxelChunk::HEIGHT; y++)
            {
                const glm::ivec3 localPosition(x, y, z);
                const glm::ivec3 worldPosition = chunk->getVoxelWorldPosition(localPosition);
                int32_t id = glm::perlin(glm::vec3(worldPosition.x * 0.0125f, worldPosition.y * 0.0125f, worldPosition.z * 0.0125f)) > 0.1f;
                if (id == 1) id = 2;
                if (y <= 2) id = 2;
                *chunk->getVoxelAt(localPosition) = vx::Voxel(id);
            }
        }
    }

    return chunk;
}
