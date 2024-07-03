#include "chunkgeneratorellipse.hpp"

vxg::ChunkGeneratorEllipse::ChunkGeneratorEllipse(
    const uint16_t voxelId,
    const glm::ivec3& semiAxes,
    const glm::ivec3& center
)
{
    _voxelId = voxelId;
    _semiAxes = semiAxes;
    _center = center;
}

vxg::ChunkGeneratorEllipse::~ChunkGeneratorEllipse()
{
}

vx::VoxelChunk* vxg::ChunkGeneratorEllipse::generate(const glm::ivec2& position)
{
    vx::VoxelChunk* chunk = new vx::VoxelChunk(position);

    for (int32_t z = 0; z < vx::VoxelChunk::SIZE; z++)
    {
        for (int32_t x = 0; x < vx::VoxelChunk::SIZE; x++)
        {
            for (int32_t y = 0; y < vx::VoxelChunk::HEIGHT; y++)
            {
                const glm::ivec3 localPosition(x, y, z);
                const glm::ivec3 worldPosition = chunk->getVoxelWorldPosition(localPosition);
                bool isVoxelInsideEllipse = isPositionInsideEllipse(worldPosition);
                if (isVoxelInsideEllipse)
                {
                    *chunk->getVoxelAt(localPosition) = vx::Voxel(_voxelId);
                }
            }
        }
    }

    return chunk;
}

bool vxg::ChunkGeneratorEllipse::isPositionInsideEllipse(const glm::ivec3& position) const
{
    return static_cast<float>(std::pow(position.x - _center.x, 2)) / static_cast<float>(_semiAxes.x * _semiAxes.x) +
        static_cast<float>(std::pow(position.y - _center.y, 2)) / static_cast<float>(_semiAxes.y * _semiAxes.y) +
        static_cast<float>(std::pow(position.z - _center.z, 2)) / static_cast<float>(_semiAxes.z * _semiAxes.z) <= 1.0f;
}
