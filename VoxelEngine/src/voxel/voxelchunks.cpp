#include "voxelchunks.hpp"

vx::VoxelChunks::VoxelChunks()
{

}

vx::VoxelChunks::~VoxelChunks()
{
}

void vx::VoxelChunks::addChunkAt(const glm::ivec2& chunkPosition)
{
    _chunks.insert({ chunkPosition, std::shared_ptr<VoxelChunk>(new VoxelChunk(chunkPosition)) });
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
