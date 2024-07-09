#include <iostream>
#include <glm/gtc/noise.hpp>
#include "voxelchunk.hpp"

uint32_t vx::VoxelChunk::SIZE = 8;
uint32_t vx::VoxelChunk::HEIGHT = 256;
float vx::VoxelChunk::VOXEL_SIZE = 1.0f;

vx::VoxelChunk::VoxelChunk(const glm::ivec2& position)
{
    _position = position;

    const uint32_t volume = getVolume();
    Voxel* rawVoxels = new Voxel[volume];
    _voxels = std::shared_ptr<Voxel[]>(rawVoxels);
}

vx::VoxelChunk::~VoxelChunk()
{
}

void vx::VoxelChunk::update()
{
    _isModified = false;
}

glm::ivec2 vx::VoxelChunk::getPosition() const
{
    return _position;
}

vx::Voxel* vx::VoxelChunk::getVoxelAt(const glm::ivec3& position) const
{
    const uint32_t index = getVoxelIndexAt(position);
    return &_voxels[index];
}

glm::ivec3 vx::VoxelChunk::getVoxelWorldPosition(const glm::ivec3& position)
{
    return glm::ivec3(
        position.x + _position.x * SIZE,
        position.y,
        position.z + _position.y * SIZE
    );
}

bool vx::VoxelChunk::isModified() const
{
    return _isModified;
}

uint32_t vx::VoxelChunk::getVolume()
{
    return SIZE * SIZE * HEIGHT;
}

uint32_t vx::VoxelChunk::getVoxelIndexAt(const glm::ivec3& position) const
{
    return (position.y * SIZE + position.z) * SIZE + position.x;
}
