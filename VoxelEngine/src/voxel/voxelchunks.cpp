#include <GLFW/glfw3.h>
#include "voxelchunks.hpp"
#include "enginestatistic.hpp"

vx::VoxelChunks::VoxelChunks(vx::IVoxelChunkGenerator* generator)
{
    _generator = generator;
}

vx::VoxelChunks::~VoxelChunks()
{
}

void vx::VoxelChunks::update(const glm::vec3& cameraPosition)
{
    _centerChunkPosition = getChunkPositionAtWorldPosition(cameraPosition);

    removeChunks();
    generateChunks();
}

glm::ivec2 vx::VoxelChunks::getChunkPositionAtWorldPosition(const glm::vec3& worldPosition) const
{
    const float chunkSize = VoxelChunk::SIZE * VoxelChunk::VOXEL_SIZE;

    glm::ivec2 chunkPosition(
        worldPosition.x / chunkSize,
        worldPosition.z / chunkSize
    );

    if (worldPosition.x < 0) chunkPosition.x--;
    if (worldPosition.z < 0) chunkPosition.y--;

    return chunkPosition;
}

vx::VoxelChunk* vx::VoxelChunks::getChunkAtWorldPosition(const glm::vec3& worldPosition) const
{
    const glm::ivec2 chunkPosition = getChunkPositionAtWorldPosition(worldPosition);
    if (_chunks.contains(chunkPosition)) return _chunks.at(chunkPosition).get();
    return nullptr;
}

vx::VoxelChunk* vx::VoxelChunks::getChunkAt(const glm::ivec2& chunkPosition) const
{
    if (_chunks.contains(chunkPosition)) return _chunks.at(chunkPosition).get();
    return nullptr;
}

std::unordered_map<glm::ivec2, vx::VoxelChunk*> vx::VoxelChunks::getChunks() const
{
    std::unordered_map<glm::ivec2, vx::VoxelChunk*> chunks;
    for (auto& it : _chunks)
    {
        chunks[it.first] = it.second.get();
    }
    return chunks;
}

std::vector<glm::ivec2> vx::VoxelChunks::getChunkPositionsToRender()
{
    return _chunkPositionsToRender;
}

std::vector<glm::ivec2> vx::VoxelChunks::getChunkPositionsToRemove()
{
    return _chunkPositionsToRemove;
}

bool vx::VoxelChunks::isChunkPositionInGenerationRadius(const glm::ivec2& chunkPosition) const
{
    return chunkPosition.x >= _centerChunkPosition.x - _generationRadius &&
        chunkPosition.x <= _centerChunkPosition.x + _generationRadius &&
        chunkPosition.y >= _centerChunkPosition.y - _generationRadius &&
        chunkPosition.y <= _centerChunkPosition.y + _generationRadius;
}

void vx::VoxelChunks::setGenerationRadius(const int32_t radius)
{
    _generationRadius = radius;
}

void vx::VoxelChunks::generateChunks()
{
    const double start = glfwGetTime();
    _chunkPositionsToRender.clear();

    for (int32_t x = _centerChunkPosition.x - _generationRadius; x < _centerChunkPosition.x + _generationRadius; x++)
    {
        for (int32_t z = _centerChunkPosition.y - _generationRadius; z < _centerChunkPosition.y + _generationRadius; z++)
        {
            const glm::ivec2 chunkPosition(x, z);
            if (_chunks.contains(chunkPosition)) continue;

            VoxelChunk* chunk = _generator->generate(chunkPosition);
            addChunk(chunkPosition, chunk);
            _chunkPositionsToRender.push_back(chunkPosition);
        }
    }

    const double end = glfwGetTime();

    if (!_chunkPositionsToRender.empty())
    {
        EngineStatistic::updateChunksGenerationTime(end - start);
    }
}

void vx::VoxelChunks::removeChunks()
{
    _chunkPositionsToRemove.clear();

    for (auto& it : _chunks)
    {
        const glm::ivec2& chunkPosition = it.first;
        if (!isChunkPositionInGenerationRadius(chunkPosition))
        {
            _chunkPositionsToRemove.push_back(chunkPosition);
        }
    }

    for (auto& chunkPositionToRemove : _chunkPositionsToRemove)
    {
        removeChunkAt(chunkPositionToRemove);
    }
}

void vx::VoxelChunks::addChunk(const glm::ivec2& chunkPosition, VoxelChunk* chunk)
{
    _chunks.insert({ chunkPosition, std::shared_ptr<VoxelChunk>(chunk) });
}

void vx::VoxelChunks::removeChunkAt(const glm::ivec2& chunkPosition)
{
    _chunks.erase(chunkPosition);
}
