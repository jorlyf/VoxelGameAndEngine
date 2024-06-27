#include "voxelchunks.hpp"

vx::VoxelChunks::VoxelChunks()
{

}

vx::VoxelChunks::~VoxelChunks()
{
}

void vx::VoxelChunks::addChunk(const glm::ivec2& chunkPosition, VoxelChunk* chunk)
{
    _chunks.insert({ chunkPosition, std::shared_ptr<VoxelChunk>(chunk) });
}

void vx::VoxelChunks::removeChunkAt(const glm::ivec2& chunkPosition)
{
}

vx::VoxelChunk* vx::VoxelChunks::getChunkAt(const glm::ivec2& chunkPosition) const
{
    if (_chunks.contains(chunkPosition)) return _chunks.at(chunkPosition).get();
    return nullptr;
}

std::unordered_map<glm::ivec2, std::shared_ptr<vx::VoxelChunk>> vx::VoxelChunks::getChunks() const
{
    return _chunks;
}
