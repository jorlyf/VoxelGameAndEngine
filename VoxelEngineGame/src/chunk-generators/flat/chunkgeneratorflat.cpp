#include "chunkgeneratorflat.hpp"

vxg::ChunkGeneratorFlat::~ChunkGeneratorFlat()
{
}

vx::VoxelChunk* vxg::ChunkGeneratorFlat::generate(const glm::ivec2& position)
{
    vx::VoxelChunk* chunk = new vx::VoxelChunk(position);

    for (int32_t z = 0; z < vx::VoxelChunk::SIZE; z++)
    {
        for (int32_t x = 0; x < vx::VoxelChunk::SIZE; x++)
        {
            *chunk->getVoxelAt(x, 0, z) = vx::Voxel(1);
        }
    }

    return chunk;
}
