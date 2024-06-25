#pragma once
#include <cstdint>
#include <memory>
#include "../graphics/mesh.hpp"
#include "../voxel/voxelchunks.hpp"

namespace vx
{
    class VoxelRenderer
    {
    public:
        VoxelRenderer();

        std::shared_ptr<Mesh> renderChunk(
            const VoxelChunk& voxelChunk,
            const VoxelChunks& voxelChunks
        );

    private:
        std::shared_ptr<float[]> _buffer = nullptr;
        uint32_t _vertexCount = 0;

        void renderTopFace(
            const uint32_t triangleIndex,
            const Voxel& voxel,
            const float x,
            const float y,
            const float z
        );

        void renderBottomFace(
            const uint32_t triangleIndex,
            const Voxel& voxel,
            const float x,
            const float y,
            const float z
        );

        void renderNorthFace(
            const uint32_t triangleIndex,
            const Voxel& voxel,
            const float x,
            const float y,
            const float z
        );

        void renderSouthFace(
            const uint32_t triangleIndex,
            const Voxel& voxel,
            const float x,
            const float y,
            const float z
        );

        void renderWestFace(
            const uint32_t triangleIndex,
            const Voxel& voxel,
            const float x,
            const float y,
            const float z
        );

        void renderEastFace(
            const uint32_t triangleIndex,
            const Voxel& voxel,
            const float x,
            const float y,
            const float z
        );
    };
}
