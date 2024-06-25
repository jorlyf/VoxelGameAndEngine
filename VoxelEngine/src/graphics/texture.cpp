#include <GL/glew.h>
#include "texture.hpp"
#include "../loaders/pngloader.hpp"

vx::Texture::Texture(const uint32_t id, const uint32_t width, const uint32_t height)
{
	_id = id;
	_width = width;
	_height = height;
}

vx::Texture::~Texture()
{
	glDeleteTextures(1, &_id);
}

vx::Texture* vx::Texture::loadFromFile(const std::string& filePath)
{
	return load_texture(filePath);
}

void vx::Texture::bind()
{
	glBindTexture(GL_TEXTURE_2D, _id);
}