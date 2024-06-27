#pragma once
#include <cstdint>
#include <memory>
#include <unordered_map>
#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/hash.hpp"
#include "voxelchunk.hpp"

namespace vx
{
    class VoxelChunks
    {
    public:
        VoxelChunks();
        ~VoxelChunks();

        void addChunk(const glm::ivec2& chunkPosition, VoxelChunk* chunk);
        void removeChunkAt(const glm::ivec2& chunkPosition);

        VoxelChunk* getChunkAt(const glm::ivec2& chunkPosition) const;
        std::unordered_map<glm::ivec2, std::shared_ptr<VoxelChunk>> getChunks() const;

    private:
        std::unordered_map<glm::ivec2, std::shared_ptr<VoxelChunk>> _chunks;
    };
}
