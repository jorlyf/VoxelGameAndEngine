#pragma once
#include <stdint.h>
#include <memory>
#include <map>
#include <glm/glm.hpp>
#include "texture.hpp"

namespace vx
{
    class TextureAtlas
    {
    public:
        struct TextureUV
        {
            /// @brief position of left bottom point
            glm::vec2 position;
            /// @brief width and height
            glm::vec2 size;
        };

        TextureAtlas(const glm::ivec2& textureSize);

        void bind();

        TextureUV getTextureUV(const std::string& alias);

        void addTextureFromFile(const std::string& alias, const std::string& filePath);
        void generate();

        /// @brief 
        /// @param textures where key = alias, value = index of texture
        /// @param textureSize 
        /// @param filePath 
        static TextureAtlas* loadFromFile(
            const std::map<std::string, uint16_t>& textures,
            const glm::ivec2& textureSize,
            const std::string& filePath
        );

    private:
        std::shared_ptr<Texture> _texture = nullptr;
        std::map<std::string, TextureUV> _uvs;
        glm::ivec2 _textureSize;

        std::map<std::string, std::string> _textureFiles;

        void generateUVs(const std::map<std::string, uint16_t>& textures);
    };
}
