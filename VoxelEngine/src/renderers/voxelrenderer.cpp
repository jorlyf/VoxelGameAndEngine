#include "voxelrenderer.hpp"

vx::VoxelRenderer::VoxelRenderer()
{
    const uint32_t VERTEX_PER_VOXEL = 6 * 6;
    const uint32_t VERTEX_SIZE = 5;
    const uint32_t MAX_VOXEL_COUNT_PER_CHUNK = VoxelChunk::getVolume();

    _vertexCount = VERTEX_PER_VOXEL * MAX_VOXEL_COUNT_PER_CHUNK;
    const uint32_t VERTEX_ARRAY_LENGTH = _vertexCount * VERTEX_SIZE;
    _buffer = std::shared_ptr<float[]>(new float[VERTEX_ARRAY_LENGTH]);
}

std::shared_ptr<vx::Mesh> vx::VoxelRenderer::renderChunk(
    const VoxelChunk& voxelChunk,
    const VoxelChunks& voxelChunks
)
{
    uint32_t voxelIndex = 0;
    uint32_t triangleIndex = 0;
    for (int32_t y = 0; y < VoxelChunk::HEIGHT; y++)
    {
        for (int32_t z = 0; z < VoxelChunk::SIZE; z++)
        {
            for (int32_t x = 0; x < VoxelChunk::SIZE; x++)
            {
                const Voxel voxel = voxelChunk.getVoxelAt(x, y, z);
                const uint16_t voxelId = voxel.getId();

                const uint16_t voidVoxelId = 0;
                if (voxelId == voidVoxelId) continue;

                if ((y + 1) >= VoxelChunk::HEIGHT || voxelChunk.getVoxelAt(x, y + 1, z).getId() == voidVoxelId)
                {
                    renderTopFace(triangleIndex, voxel, x, y, z);
                    triangleIndex += 2;
                }
                if ((y - 1) < 0 || voxelChunk.getVoxelAt(x, y - 1, z).getId() == voidVoxelId)
                {
                    renderBottomFace(triangleIndex, voxel, x, y, z);
                    triangleIndex += 2;
                }
                if ((x + 1) >= VoxelChunk::SIZE || voxelChunk.getVoxelAt(x + 1, y, z).getId() == voidVoxelId)
                {
                    renderNorthFace(triangleIndex, voxel, x, y, z);
                    triangleIndex += 2;
                }
                if ((x - 1) < 0 || voxelChunk.getVoxelAt(x - 1, y, z).getId() == voidVoxelId)
                {
                    renderSouthFace(triangleIndex, voxel, x, y, z);
                    triangleIndex += 2;
                }
                if ((z - 1) < 0 || voxelChunk.getVoxelAt(x, y, z - 1).getId() == voidVoxelId)
                {
                    renderWestFace(triangleIndex, voxel, x, y, z);
                    triangleIndex += 2;
                }
                if ((z + 1) >= VoxelChunk::SIZE || voxelChunk.getVoxelAt(x, y, z + 1).getId() == voidVoxelId)
                {
                    renderEastFace(triangleIndex, voxel, x, y, z);
                    triangleIndex += 2;
                }

                voxelIndex++;
            }
        }
    }

    _vertexCount = triangleIndex * 3;
    const int32_t attributes[] = { 3, 2, 0 };
    Mesh* mesh = new Mesh(_buffer.get(), _vertexCount, attributes);
    return std::shared_ptr<Mesh>(mesh);
}

void vx::VoxelRenderer::renderTopFace(
    const uint32_t triangleIndex,
    const Voxel& voxel,
    const float x,
    const float y,
    const float z
)
{
    const uint32_t VERTEX_SIZE = 5;
    uint32_t i = 3 * triangleIndex * VERTEX_SIZE;

    _buffer[i++] = x + 0.5f;
    _buffer[i++] = y + 0.5f;
    _buffer[i++] = z - 0.5f;
    _buffer[i++] = 0;
    _buffer[i++] = 1;

    _buffer[i++] = x - 0.5f;
    _buffer[i++] = y + 0.5f;
    _buffer[i++] = z - 0.5f;
    _buffer[i++] = 0;
    _buffer[i++] = 0;

    _buffer[i++] = x - 0.5f;
    _buffer[i++] = y + 0.5f;
    _buffer[i++] = z + 0.5f;
    _buffer[i++] = 1;
    _buffer[i++] = 0;

    _buffer[i++] = x - 0.5f;
    _buffer[i++] = y + 0.5f;
    _buffer[i++] = z + 0.5f;
    _buffer[i++] = 1;
    _buffer[i++] = 0;

    _buffer[i++] = x + 0.5f;
    _buffer[i++] = y + 0.5f;
    _buffer[i++] = z + 0.5f;
    _buffer[i++] = 1;
    _buffer[i++] = 1;

    _buffer[i++] = x + 0.5f;
    _buffer[i++] = y + 0.5f;
    _buffer[i++] = z - 0.5f;
    _buffer[i++] = 0;
    _buffer[i++] = 1;
}

void vx::VoxelRenderer::renderBottomFace(
    const uint32_t triangleIndex,
    const Voxel& voxel,
    const float x,
    const float y,
    const float z
)
{
    const uint32_t VERTEX_SIZE = 5;
    uint32_t i = 3 * triangleIndex * VERTEX_SIZE;

    _buffer[i++] = x - 0.5f;
    _buffer[i++] = y - 0.5f;
    _buffer[i++] = z + 0.5f;
    _buffer[i++] = 1;
    _buffer[i++] = 0;

    _buffer[i++] = x - 0.5f;
    _buffer[i++] = y - 0.5f;
    _buffer[i++] = z - 0.5f;
    _buffer[i++] = 0;
    _buffer[i++] = 0;

    _buffer[i++] = x + 0.5f;
    _buffer[i++] = y - 0.5f;
    _buffer[i++] = z - 0.5f;
    _buffer[i++] = 0;
    _buffer[i++] = 1;

    _buffer[i++] = x + 0.5f;
    _buffer[i++] = y - 0.5f;
    _buffer[i++] = z - 0.5f;
    _buffer[i++] = 0;
    _buffer[i++] = 1;

    _buffer[i++] = x + 0.5f;
    _buffer[i++] = y - 0.5f;
    _buffer[i++] = z + 0.5f;
    _buffer[i++] = 1;
    _buffer[i++] = 1;

    _buffer[i++] = x - 0.5f;
    _buffer[i++] = y - 0.5f;
    _buffer[i++] = z + 0.5f;
    _buffer[i++] = 1;
    _buffer[i++] = 0;
}

void vx::VoxelRenderer::renderNorthFace(
    const uint32_t triangleIndex,
    const Voxel& voxel,
    const float x,
    const float y,
    const float z
)
{
    const uint32_t VERTEX_SIZE = 5;
    uint32_t i = 3 * triangleIndex * VERTEX_SIZE;

    _buffer[i++] = x + 0.5f;
    _buffer[i++] = y + 0.5f;
    _buffer[i++] = z + 0.5f;
    _buffer[i++] = 0;
    _buffer[i++] = 1;

    _buffer[i++] = x + 0.5f;
    _buffer[i++] = y - 0.5f;
    _buffer[i++] = z + 0.5f;
    _buffer[i++] = 0;
    _buffer[i++] = 0;

    _buffer[i++] = x + 0.5f;
    _buffer[i++] = y - 0.5f;
    _buffer[i++] = z - 0.5f;
    _buffer[i++] = 1;
    _buffer[i++] = 0;

    _buffer[i++] = x + 0.5f;
    _buffer[i++] = y - 0.5f;
    _buffer[i++] = z - 0.5f;
    _buffer[i++] = 1;
    _buffer[i++] = 0;

    _buffer[i++] = x + 0.5f;
    _buffer[i++] = y + 0.5f;
    _buffer[i++] = z - 0.5f;
    _buffer[i++] = 1;
    _buffer[i++] = 1;

    _buffer[i++] = x + 0.5f;
    _buffer[i++] = y + 0.5f;
    _buffer[i++] = z + 0.5f;
    _buffer[i++] = 0;
    _buffer[i++] = 1;
}

void vx::VoxelRenderer::renderSouthFace(
    const uint32_t triangleIndex,
    const Voxel& voxel,
    const float x,
    const float y,
    const float z
)
{
    const uint32_t VERTEX_SIZE = 5;
    uint32_t i = 3 * triangleIndex * VERTEX_SIZE;

    _buffer[i++] = x - 0.5f;
    _buffer[i++] = y + 0.5f;
    _buffer[i++] = z - 0.5f;
    _buffer[i++] = 0;
    _buffer[i++] = 1;

    _buffer[i++] = x - 0.5f;
    _buffer[i++] = y - 0.5f;
    _buffer[i++] = z - 0.5f;
    _buffer[i++] = 0;
    _buffer[i++] = 0;

    _buffer[i++] = x - 0.5f;
    _buffer[i++] = y - 0.5f;
    _buffer[i++] = z + 0.5f;
    _buffer[i++] = 1;
    _buffer[i++] = 0;

    _buffer[i++] = x - 0.5f;
    _buffer[i++] = y - 0.5f;
    _buffer[i++] = z + 0.5f;
    _buffer[i++] = 1;
    _buffer[i++] = 0;

    _buffer[i++] = x - 0.5f;
    _buffer[i++] = y + 0.5f;
    _buffer[i++] = z + 0.5f;
    _buffer[i++] = 1;
    _buffer[i++] = 1;

    _buffer[i++] = x - 0.5f;
    _buffer[i++] = y + 0.5f;
    _buffer[i++] = z - 0.5f;
    _buffer[i++] = 0;
    _buffer[i++] = 1;
}

void vx::VoxelRenderer::renderWestFace(
    const uint32_t triangleIndex,
    const Voxel& voxel,
    const float x,
    const float y,
    const float z
)
{
    const uint32_t VERTEX_SIZE = 5;
    uint32_t i = 3 * triangleIndex * VERTEX_SIZE;

    _buffer[i++] = x + 0.5f;
    _buffer[i++] = y - 0.5f;
    _buffer[i++] = z - 0.5f;
    _buffer[i++] = 1;
    _buffer[i++] = 0;

    _buffer[i++] = x - 0.5f;
    _buffer[i++] = y - 0.5f;
    _buffer[i++] = z - 0.5f;
    _buffer[i++] = 0;
    _buffer[i++] = 0;

    _buffer[i++] = x - 0.5f;
    _buffer[i++] = y + 0.5f;
    _buffer[i++] = z - 0.5f;
    _buffer[i++] = 0;
    _buffer[i++] = 1;

    _buffer[i++] = x - 0.5f;
    _buffer[i++] = y + 0.5f;
    _buffer[i++] = z - 0.5f;
    _buffer[i++] = 0;
    _buffer[i++] = 1;

    _buffer[i++] = x + 0.5f;
    _buffer[i++] = y + 0.5f;
    _buffer[i++] = z - 0.5f;
    _buffer[i++] = 1;
    _buffer[i++] = 1;

    _buffer[i++] = x + 0.5f;
    _buffer[i++] = y - 0.5f;
    _buffer[i++] = z - 0.5f;
    _buffer[i++] = 1;
    _buffer[i++] = 0;
}

void vx::VoxelRenderer::renderEastFace(
    const uint32_t triangleIndex,
    const Voxel& voxel,
    const float x,
    const float y,
    const float z
)
{
    const uint32_t VERTEX_SIZE = 5;
    uint32_t i = 3 * triangleIndex * VERTEX_SIZE;

    _buffer[i++] = x - 0.5f;
    _buffer[i++] = y + 0.5f;
    _buffer[i++] = z + 0.5f;
    _buffer[i++] = 0;
    _buffer[i++] = 1;

    _buffer[i++] = x - 0.5f;
    _buffer[i++] = y - 0.5f;
    _buffer[i++] = z + 0.5f;
    _buffer[i++] = 0;
    _buffer[i++] = 0;

    _buffer[i++] = x + 0.5f;
    _buffer[i++] = y - 0.5f;
    _buffer[i++] = z + 0.5f;
    _buffer[i++] = 1;
    _buffer[i++] = 0;

    _buffer[i++] = x + 0.5f;
    _buffer[i++] = y - 0.5f;
    _buffer[i++] = z + 0.5f;
    _buffer[i++] = 1;
    _buffer[i++] = 0;

    _buffer[i++] = x + 0.5f;
    _buffer[i++] = y + 0.5f;
    _buffer[i++] = z + 0.5f;
    _buffer[i++] = 1;
    _buffer[i++] = 1;

    _buffer[i++] = x - 0.5f;
    _buffer[i++] = y + 0.5f;
    _buffer[i++] = z + 0.5f;
    _buffer[i++] = 0;
    _buffer[i++] = 1;
}
