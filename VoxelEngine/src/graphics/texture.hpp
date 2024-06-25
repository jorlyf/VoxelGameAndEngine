#pragma once
#include <cstdint>
#include <string>

namespace vx
{
	class Texture {
	public:
		Texture(const uint32_t id, const uint32_t width, const uint32_t height);
		~Texture();

		static Texture* loadFromFile(const std::string& filePath);

		void bind();

	private:
		uint32_t _id;
		uint32_t _width;
		uint32_t _height;
	};
}
