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

        void update();

        glm::ivec2 getPosition() const;

        Voxel* getVoxelAt(const glm::ivec3& position) const;
        glm::ivec3 getVoxelWorldPosition(const glm::ivec3& position);

        bool isModified() const;

        static uint32_t SIZE;
        static uint32_t HEIGHT;
        static float VOXEL_SIZE;

        static uint32_t getVolume();

    private:
        std::shared_ptr<Voxel[]> _voxels = nullptr;

        glm::ivec2 _position;

        bool _isModified = false;

        uint32_t getVoxelIndexAt(const glm::ivec3& position) const;
    };
}
