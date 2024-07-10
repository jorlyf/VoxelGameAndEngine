#include "voxelrenderer.hpp"

vx::VoxelRenderer::VoxelRenderer(TextureAtlas* textureAtlas)
{
    _textureAtlas = textureAtlas;

    const uint32_t VERTEX_PER_VOXEL = 6 * 6;
    const uint32_t MAX_VOXEL_COUNT_PER_CHUNK = VoxelChunk::getVolume();

    _vertexCount = VERTEX_PER_VOXEL * MAX_VOXEL_COUNT_PER_CHUNK;
    const uint32_t VERTEX_ARRAY_LENGTH = _vertexCount;
    _vertices = std::shared_ptr<VoxelVertex[]>(new VoxelVertex[VERTEX_ARRAY_LENGTH]);
}

vx::Mesh* vx::VoxelRenderer::renderChunk(
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
                const glm::ivec3 localPosition(x, y, z);
                const Voxel& voxel = *voxelChunk.getVoxelAt(localPosition);
                const uint16_t voxelId = voxel.getId();

                const std::string blockType = voxelId == 1 ? "grass" : "cyan_wool";
                const TextureAtlas::TextureUV uv = _textureAtlas->getTextureUV(blockType);

                const uint16_t voidVoxelId = 0;
                if (voxelId == voidVoxelId) continue;

                if ((y + 1) >= VoxelChunk::HEIGHT || voxelChunk.getVoxelAt(glm::ivec3(x, y + 1, z))->getId() == voidVoxelId)
                {
                    renderTopFace(triangleIndex, voxel, localPosition, uv);
                    triangleIndex += 2;
                }
                if ((y - 1) < 0 || voxelChunk.getVoxelAt(glm::ivec3(x, y - 1, z))->getId() == voidVoxelId)
                {
                    renderBottomFace(triangleIndex, voxel, localPosition, uv);
                    triangleIndex += 2;
                }
                if ((x + 1) >= VoxelChunk::SIZE || voxelChunk.getVoxelAt(glm::ivec3(x + 1, y, z))->getId() == voidVoxelId)
                {
                    renderNorthFace(triangleIndex, voxel, localPosition, uv);
                    triangleIndex += 2;
                }
                if ((x - 1) < 0 || voxelChunk.getVoxelAt(glm::ivec3(x - 1, y, z))->getId() == voidVoxelId)
                {
                    renderSouthFace(triangleIndex, voxel, localPosition, uv);
                    triangleIndex += 2;
                }
                if ((z - 1) < 0 || voxelChunk.getVoxelAt(glm::ivec3(x, y, z - 1))->getId() == voidVoxelId)
                {
                    renderWestFace(triangleIndex, voxel, localPosition, uv);
                    triangleIndex += 2;
                }
                if ((z + 1) >= VoxelChunk::SIZE || voxelChunk.getVoxelAt(glm::ivec3(x, y, z + 1))->getId() == voidVoxelId)
                {
                    renderEastFace(triangleIndex, voxel, localPosition, uv);
                    triangleIndex += 2;
                }

                voxelIndex++;
            }
        }
    }

    _vertexCount = triangleIndex * 3;
    const int32_t attributes[] = { 3, 2, 0 };
    Mesh* mesh = new Mesh(reinterpret_cast<float*>(_vertices.get()), _vertexCount, attributes);
    return mesh;
}

void vx::VoxelRenderer::renderTopFace(
    const uint32_t triangleIndex,
    const Voxel& voxel,
    const glm::vec3 position,
    const TextureAtlas::TextureUV uv
)
{
    uint32_t i = 3 * triangleIndex;

    _vertices[i].vertex.x = position.x + 0.5f;
    _vertices[i].vertex.y = position.y + 0.5f;
    _vertices[i].vertex.z = position.z - 0.5f;
    _vertices[i].uv.x = uv.position.x;
    _vertices[i].uv.y = uv.position.y + uv.size.y;
    i++;

    _vertices[i].vertex.x = position.x - 0.5f;
    _vertices[i].vertex.y = position.y + 0.5f;
    _vertices[i].vertex.z = position.z - 0.5f;
    _vertices[i].uv.x = uv.position.x;
    _vertices[i].uv.y = uv.position.y;
    i++;

    _vertices[i].vertex.x = position.x - 0.5f;
    _vertices[i].vertex.y = position.y + 0.5f;
    _vertices[i].vertex.z = position.z + 0.5f;
    _vertices[i].uv.x = uv.position.x + uv.size.x;
    _vertices[i].uv.y = uv.position.y;
    i++;

    _vertices[i].vertex.x = position.x - 0.5f;
    _vertices[i].vertex.y = position.y + 0.5f;
    _vertices[i].vertex.z = position.z + 0.5f;
    _vertices[i].uv.x = uv.position.x + uv.size.x;
    _vertices[i].uv.y = uv.position.y;
    i++;

    _vertices[i].vertex.x = position.x + 0.5f;
    _vertices[i].vertex.y = position.y + 0.5f;
    _vertices[i].vertex.z = position.z + 0.5f;
    _vertices[i].uv.x = uv.position.x + uv.size.x;
    _vertices[i].uv.y = uv.position.y + uv.size.y;
    i++;

    _vertices[i].vertex.x = position.x + 0.5f;
    _vertices[i].vertex.y = position.y + 0.5f;
    _vertices[i].vertex.z = position.z - 0.5f;
    _vertices[i].uv.x = uv.position.x;
    _vertices[i].uv.y = uv.position.y + uv.size.y;
}

void vx::VoxelRenderer::renderBottomFace(
    const uint32_t triangleIndex,
    const Voxel& voxel,
    const glm::vec3 position,
    const TextureAtlas::TextureUV uv
)
{
    uint32_t i = 3 * triangleIndex;

    _vertices[i].vertex.x = position.x - 0.5f;
    _vertices[i].vertex.y = position.y - 0.5f;
    _vertices[i].vertex.z = position.z + 0.5f;
    _vertices[i].uv.x = uv.position.x + uv.size.x;
    _vertices[i].uv.y = uv.position.y;
    i++;

    _vertices[i].vertex.x = position.x - 0.5f;
    _vertices[i].vertex.y = position.y - 0.5f;
    _vertices[i].vertex.z = position.z - 0.5f;
    _vertices[i].uv.x = uv.position.x;
    _vertices[i].uv.y = uv.position.y;
    i++;

    _vertices[i].vertex.x = position.x + 0.5f;
    _vertices[i].vertex.y = position.y - 0.5f;
    _vertices[i].vertex.z = position.z - 0.5f;
    _vertices[i].uv.x = uv.position.x;
    _vertices[i].uv.y = uv.position.y + uv.size.y;
    i++;

    _vertices[i].vertex.x = position.x + 0.5f;
    _vertices[i].vertex.y = position.y - 0.5f;
    _vertices[i].vertex.z = position.z - 0.5f;
    _vertices[i].uv.x = uv.position.x;
    _vertices[i].uv.y = uv.position.y + uv.size.y;
    i++;

    _vertices[i].vertex.x = position.x + 0.5f;
    _vertices[i].vertex.y = position.y - 0.5f;
    _vertices[i].vertex.z = position.z + 0.5f;
    _vertices[i].uv.x = uv.position.x + uv.size.x;
    _vertices[i].uv.y = uv.position.y + uv.size.y;
    i++;

    _vertices[i].vertex.x = position.x - 0.5f;
    _vertices[i].vertex.y = position.y - 0.5f;
    _vertices[i].vertex.z = position.z + 0.5f;
    _vertices[i].uv.x = uv.position.x + uv.size.x;
    _vertices[i].uv.y = uv.position.y;
}

void vx::VoxelRenderer::renderNorthFace(
    const uint32_t triangleIndex,
    const Voxel& voxel,
    const glm::vec3 position,
    const TextureAtlas::TextureUV uv
)
{
    uint32_t i = 3 * triangleIndex;

    _vertices[i].vertex.x = position.x + 0.5f;
    _vertices[i].vertex.y = position.y + 0.5f;
    _vertices[i].vertex.z = position.z + 0.5f;
    _vertices[i].uv.x = uv.position.x;
    _vertices[i].uv.y = uv.position.y + uv.size.y;
    i++;

    _vertices[i].vertex.x = position.x + 0.5f;
    _vertices[i].vertex.y = position.y - 0.5f;
    _vertices[i].vertex.z = position.z + 0.5f;
    _vertices[i].uv.x = uv.position.x;
    _vertices[i].uv.y = uv.position.y;
    i++;

    _vertices[i].vertex.x = position.x + 0.5f;
    _vertices[i].vertex.y = position.y - 0.5f;
    _vertices[i].vertex.z = position.z - 0.5f;
    _vertices[i].uv.x = uv.position.x + uv.size.x;
    _vertices[i].uv.y = uv.position.y;
    i++;

    _vertices[i].vertex.x = position.x + 0.5f;
    _vertices[i].vertex.y = position.y - 0.5f;
    _vertices[i].vertex.z = position.z - 0.5f;
    _vertices[i].uv.x = uv.position.x + uv.size.x;
    _vertices[i].uv.y = uv.position.y;
    i++;

    _vertices[i].vertex.x = position.x + 0.5f;
    _vertices[i].vertex.y = position.y + 0.5f;
    _vertices[i].vertex.z = position.z - 0.5f;
    _vertices[i].uv.x = uv.position.x + uv.size.x;
    _vertices[i].uv.y = uv.position.y + uv.size.y;
    i++;

    _vertices[i].vertex.x = position.x + 0.5f;
    _vertices[i].vertex.y = position.y + 0.5f;
    _vertices[i].vertex.z = position.z + 0.5f;
    _vertices[i].uv.x = uv.position.x;
    _vertices[i].uv.y = uv.position.y + uv.size.y;
}

void vx::VoxelRenderer::renderSouthFace(
    const uint32_t triangleIndex,
    const Voxel& voxel,
    const glm::vec3 position,
    const TextureAtlas::TextureUV uv
)
{
    uint32_t i = 3 * triangleIndex;

    _vertices[i].vertex.x = position.x - 0.5f;
    _vertices[i].vertex.y = position.y + 0.5f;
    _vertices[i].vertex.z = position.z - 0.5f;
    _vertices[i].uv.x = uv.position.x;
    _vertices[i].uv.y = uv.position.y + uv.size.y;
    i++;

    _vertices[i].vertex.x = position.x - 0.5f;
    _vertices[i].vertex.y = position.y - 0.5f;
    _vertices[i].vertex.z = position.z - 0.5f;
    _vertices[i].uv.x = uv.position.x;
    _vertices[i].uv.y = uv.position.y;
    i++;

    _vertices[i].vertex.x = position.x - 0.5f;
    _vertices[i].vertex.y = position.y - 0.5f;
    _vertices[i].vertex.z = position.z + 0.5f;
    _vertices[i].uv.x = uv.position.x + uv.size.x;
    _vertices[i].uv.y = uv.position.y;
    i++;

    _vertices[i].vertex.x = position.x - 0.5f;
    _vertices[i].vertex.y = position.y - 0.5f;
    _vertices[i].vertex.z = position.z + 0.5f;
    _vertices[i].uv.x = uv.position.x + uv.size.x;
    _vertices[i].uv.y = uv.position.y;
    i++;

    _vertices[i].vertex.x = position.x - 0.5f;
    _vertices[i].vertex.y = position.y + 0.5f;
    _vertices[i].vertex.z = position.z + 0.5f;
    _vertices[i].uv.x = uv.position.x + uv.size.x;
    _vertices[i].uv.y = uv.position.y + uv.size.y;
    i++;

    _vertices[i].vertex.x = position.x - 0.5f;
    _vertices[i].vertex.y = position.y + 0.5f;
    _vertices[i].vertex.z = position.z - 0.5f;
    _vertices[i].uv.x = uv.position.x;
    _vertices[i].uv.y = uv.position.y + uv.size.y;
}

void vx::VoxelRenderer::renderWestFace(
    const uint32_t triangleIndex,
    const Voxel& voxel,
    const glm::vec3 position,
    const TextureAtlas::TextureUV uv
)
{
    uint32_t i = 3 * triangleIndex;

    _vertices[i].vertex.x = position.x + 0.5f;
    _vertices[i].vertex.y = position.y - 0.5f;
    _vertices[i].vertex.z = position.z - 0.5f;
    _vertices[i].uv.x = uv.position.x + uv.size.x;
    _vertices[i].uv.y = uv.position.y;
    i++;

    _vertices[i].vertex.x = position.x - 0.5f;
    _vertices[i].vertex.y = position.y - 0.5f;
    _vertices[i].vertex.z = position.z - 0.5f;
    _vertices[i].uv.x = uv.position.x;
    _vertices[i].uv.y = uv.position.y;
    i++;

    _vertices[i].vertex.x = position.x - 0.5f;
    _vertices[i].vertex.y = position.y + 0.5f;
    _vertices[i].vertex.z = position.z - 0.5f;
    _vertices[i].uv.x = uv.position.x;
    _vertices[i].uv.y = uv.position.y + uv.size.y;
    i++;

    _vertices[i].vertex.x = position.x - 0.5f;
    _vertices[i].vertex.y = position.y + 0.5f;
    _vertices[i].vertex.z = position.z - 0.5f;
    _vertices[i].uv.x = uv.position.x;
    _vertices[i].uv.y = uv.position.y + uv.size.y;
    i++;

    _vertices[i].vertex.x = position.x + 0.5f;
    _vertices[i].vertex.y = position.y + 0.5f;
    _vertices[i].vertex.z = position.z - 0.5f;
    _vertices[i].uv.x = uv.position.x + uv.size.x;
    _vertices[i].uv.y = uv.position.y + uv.size.y;
    i++;

    _vertices[i].vertex.x = position.x + 0.5f;
    _vertices[i].vertex.y = position.y - 0.5f;
    _vertices[i].vertex.z = position.z - 0.5f;
    _vertices[i].uv.x = uv.position.x + uv.size.x;
    _vertices[i].uv.y = uv.position.y;
}

void vx::VoxelRenderer::renderEastFace(
    const uint32_t triangleIndex,
    const Voxel& voxel,
    const glm::vec3 position,
    const TextureAtlas::TextureUV uv
)
{
    uint32_t i = 3 * triangleIndex;

    _vertices[i].vertex.x = position.x - 0.5f;
    _vertices[i].vertex.y = position.y + 0.5f;
    _vertices[i].vertex.z = position.z + 0.5f;
    _vertices[i].uv.x = uv.position.x;
    _vertices[i].uv.y = uv.position.y + uv.size.y;
    i++;

    _vertices[i].vertex.x = position.x - 0.5f;
    _vertices[i].vertex.y = position.y - 0.5f;
    _vertices[i].vertex.z = position.z + 0.5f;
    _vertices[i].uv.x = uv.position.x;
    _vertices[i].uv.y = uv.position.y;
    i++;

    _vertices[i].vertex.x = position.x + 0.5f;
    _vertices[i].vertex.y = position.y - 0.5f;
    _vertices[i].vertex.z = position.z + 0.5f;
    _vertices[i].uv.x = uv.position.x + uv.size.x;
    _vertices[i].uv.y = uv.position.y;
    i++;

    _vertices[i].vertex.x = position.x + 0.5f;
    _vertices[i].vertex.y = position.y - 0.5f;
    _vertices[i].vertex.z = position.z + 0.5f;
    _vertices[i].uv.x = uv.position.x + uv.size.x;
    _vertices[i].uv.y = uv.position.y;
    i++;

    _vertices[i].vertex.x = position.x + 0.5f;
    _vertices[i].vertex.y = position.y + 0.5f;
    _vertices[i].vertex.z = position.z + 0.5f;
    _vertices[i].uv.x = uv.position.x + uv.size.x;
    _vertices[i].uv.y = uv.position.y + uv.size.y;
    i++;

    _vertices[i].vertex.x = position.x - 0.5f;
    _vertices[i].vertex.y = position.y + 0.5f;
    _vertices[i].vertex.z = position.z + 0.5f;
    _vertices[i].uv.x = uv.position.x;
    _vertices[i].uv.y = uv.position.y + uv.size.y;
}
