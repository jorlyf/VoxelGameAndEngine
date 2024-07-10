#pragma once
#include <cstdint>
#include <memory>
#include "mesh.hpp"
#include "textureatlas.hpp"
#include "voxelchunks.hpp"

namespace vx
{
    class VoxelRenderer
    {
    public:
        VoxelRenderer(TextureAtlas* textureAtlas);

        Mesh* renderChunk(
            const VoxelChunk& voxelChunk,
            const VoxelChunks& voxelChunks
        );

    private:
        struct VoxelVertex
        {
            glm::vec3 vertex;
            glm::vec2 uv;
        };

        std::shared_ptr<VoxelVertex[]> _vertices = nullptr;
        uint32_t _vertexCount = 0;

        TextureAtlas* _textureAtlas = nullptr;

        void renderTopFace(
            const uint32_t triangleIndex,
            const Voxel& voxel,
            const glm::vec3 position,
            const TextureAtlas::TextureUV uv
        );

        void renderBottomFace(
            const uint32_t triangleIndex,
            const Voxel& voxel,
            const glm::vec3 position,
            const TextureAtlas::TextureUV uv
        );

        void renderNorthFace(
            const uint32_t triangleIndex,
            const Voxel& voxel,
            const glm::vec3 position,
            const TextureAtlas::TextureUV uv
        );

        void renderSouthFace(
            const uint32_t triangleIndex,
            const Voxel& voxel,
            const glm::vec3 position,
            const TextureAtlas::TextureUV uv
        );

        void renderWestFace(
            const uint32_t triangleIndex,
            const Voxel& voxel,
            const glm::vec3 position,
            const TextureAtlas::TextureUV uv
        );

        void renderEastFace(
            const uint32_t triangleIndex,
            const Voxel& voxel,
            const glm::vec3 position,
            const TextureAtlas::TextureUV uv
        );
    };
}
