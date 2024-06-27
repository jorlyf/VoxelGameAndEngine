#include <glm/gtc/noise.hpp>
#include "voxelchunk.hpp"
#include <iostream>

uint32_t vx::VoxelChunk::SIZE = 16;
uint32_t vx::VoxelChunk::HEIGHT = 16;
float vx::VoxelChunk::VOXEL_SIZE = 0.5f;

vx::VoxelChunk::VoxelChunk(const glm::ivec2& position)
{
    _position = position;

    const uint32_t volume = getVolume();
    Voxel* rawVoxels = new Voxel[volume];
    _voxels = std::shared_ptr<Voxel[]>(rawVoxels);

    // for (int32_t y = 0; y < VoxelChunk::HEIGHT; y++)
    // {
    //     for (int32_t z = 0; z < VoxelChunk::SIZE; z++)
    //     {
    //         for (int32_t x = 0; x < VoxelChunk::SIZE; x++)
    //         {
    //             const float realY = y * VOXEL_SIZE;
    //             const float realX = x * VOXEL_SIZE + position.x * static_cast<int32_t>(SIZE) * VOXEL_SIZE;
    //             const float realZ = z * VOXEL_SIZE + position.y * static_cast<int32_t>(SIZE) * VOXEL_SIZE;

    //             const uint32_t index = getVoxelIndexAt(x, y, z);
    //             uint16_t id = 0;
    //             const float h = glm::perlin(glm::vec2(realX, realZ)) / 0.1f;
    //             // const float h = std::sin(realX) * 3.0f;
    //             if (realY < h)
    //             {
    //                 id = 1;
    //             }
    //             _voxels[index] = id;
    //         }
    //     }
    // }
}

vx::VoxelChunk::~VoxelChunk()
{
}

glm::ivec2 vx::VoxelChunk::getPosition() const
{
    return _position;
}

vx::Voxel* vx::VoxelChunk::getVoxelAt(const uint32_t x, const uint32_t y, const uint32_t z) const
{
    const uint32_t index = getVoxelIndexAt(x, y, z);
    return &_voxels[index];
}

uint32_t vx::VoxelChunk::getVolume()
{
    return SIZE * SIZE * HEIGHT;
}

uint32_t vx::VoxelChunk::getVoxelIndexAt(const uint32_t x, const uint32_t y, const uint32_t z) const
{
    return (y * SIZE + z) * SIZE + x;
}
