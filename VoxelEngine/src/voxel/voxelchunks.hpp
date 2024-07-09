#pragma once
#include <cstdint>
#include <memory>
#include <unordered_map>
#include <vector>
#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/hash.hpp>
#include "voxelchunk.hpp"
#include "ivoxelchunkgenerator.hpp"

namespace vx
{
    class VoxelChunks
    {
    public:
        VoxelChunks(IVoxelChunkGenerator* generator);
        ~VoxelChunks();

        void update(const glm::vec3& cameraPosition);

        glm::ivec2 getChunkPositionAtWorldPosition(const glm::vec3& worldPosition) const;
        VoxelChunk* getChunkAtWorldPosition(const glm::vec3& worldPosition) const;
        VoxelChunk* getChunkAt(const glm::ivec2& chunkPosition) const;
        std::unordered_map<glm::ivec2, VoxelChunk*> getChunks() const;

        std::vector<glm::ivec2> getChunkPositionsToRender();
        std::vector<glm::ivec2> getChunkPositionsToRemove();

        bool isChunkPositionInGenerationRadius(const glm::ivec2& chunkPosition) const;
        void setGenerationRadius(const int32_t radius);

    private:
        std::unordered_map<glm::ivec2, std::shared_ptr<VoxelChunk>> _chunks;
        IVoxelChunkGenerator* _generator = nullptr;

        glm::ivec2 _centerChunkPosition;
        int32_t _generationRadius = 1;

        std::vector<glm::ivec2> _chunkPositionsToRender;
        std::vector<glm::ivec2> _chunkPositionsToRemove;

        void generateChunks();
        void removeChunks();

        void addChunk(const glm::ivec2& chunkPosition, VoxelChunk* chunk);
        void removeChunkAt(const glm::ivec2& chunkPosition);
    };
}
