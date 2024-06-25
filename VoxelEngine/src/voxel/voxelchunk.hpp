#pragma once
#include <cstdint>
#include <memory>
#include <glm/glm.hpp>
#include "voxel.hpp"

namespace vx
{
    class VoxelChunk
    {
    public:
        VoxelChunk(const glm::ivec2& position);
        ~VoxelChunk();

        glm::ivec2 getPosition() const;

        Voxel getVoxelAt(const uint32_t x, const uint32_t y, const uint32_t z) const;

        static uint32_t SIZE;
        static uint32_t HEIGHT;
        static float VOXEL_SIZE;

        static uint32_t getVolume();

    private:
        std::shared_ptr<Voxel[]> _voxels = nullptr;

        glm::ivec2 _position;

        uint32_t getVoxelIndexAt(const uint32_t x, const uint32_t y, const uint32_t z) const;
    };
}
