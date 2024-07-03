#include "textureatlas.hpp"

vx::TextureAtlas::TextureAtlas(const glm::ivec2& textureSize)
{
    _textureSize = textureSize;
}

void vx::TextureAtlas::bind()
{
    _texture->bind();
}

vx::TextureAtlas::TextureUV vx::TextureAtlas::getTextureUV(const std::string& alias)
{
    return _uvs.at(alias);
}

void vx::TextureAtlas::addTextureFromFile(const std::string& alias, const std::string& filePath)
{
    _textureFiles.insert({ alias, filePath });
}

void vx::TextureAtlas::generate()
{
    for (auto& it : _textureFiles)
    {
        const std::string& alias = it.first;
        const std::string& textureFilePath = it.second;


    }
}

vx::TextureAtlas* vx::TextureAtlas::loadFromFile(
    const std::map<std::string, uint16_t>& textures,
    const glm::ivec2& textureSize,
    const std::string& filePath
)
{
    TextureAtlas* atlas = new TextureAtlas(textureSize);
    atlas->_texture = std::shared_ptr<Texture>(Texture::loadFromFile(filePath));
    atlas->generateUVs(textures);

    return atlas;
}

void vx::TextureAtlas::generateUVs(const std::map<std::string, uint16_t>& textures)
{
    for (auto& it : textures)
    {
        const std::string& alias = it.first;
        const uint16_t textureIndex = it.second;

        const glm::ivec2 texturePosition(textureIndex * _textureSize.x, 0);
        const int32_t textureCount = 4;
        TextureUV uv;
        uv.position = glm::vec2(static_cast<float>(texturePosition.x) / (_textureSize.x * textureCount), 0);
        uv.size = glm::vec2(1.0f / textureCount, 1.0f);

        _uvs.insert({ alias, uv });
    }
}
