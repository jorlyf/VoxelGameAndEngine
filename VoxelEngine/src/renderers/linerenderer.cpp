#include <cstring>
#include "linerenderer.hpp"

std::shared_ptr<float[]> vx::LineRenderer::_buffer = nullptr;
uint32_t vx::LineRenderer::_vertexCount = 0;
std::shared_ptr<vx::Mesh> vx::LineRenderer::_mesh = nullptr;

void vx::LineRenderer::addLine(
    const glm::vec3& start,
    const glm::vec3& end,
    const glm::vec4& rgba
)
{
    std::shared_ptr<float[]> newBuffer = std::shared_ptr<float[]>(new float[_vertexCount * 7 + 2 * 7]);
    std::memcpy(newBuffer.get(), _buffer.get(), _vertexCount * 7 * sizeof(float));
    _buffer = newBuffer;

    uint32_t index = _vertexCount * 7;
    _buffer[index + 0] = start.x;
    _buffer[index + 1] = start.y;
    _buffer[index + 2] = start.z;
    _buffer[index + 3] = rgba.r;
    _buffer[index + 4] = rgba.g;
    _buffer[index + 5] = rgba.b;
    _buffer[index + 6] = rgba.a;
    index += 7;

    _buffer[index + 0] = end.x;
    _buffer[index + 1] = end.y;
    _buffer[index + 2] = end.z;
    _buffer[index + 3] = rgba.r;
    _buffer[index + 4] = rgba.g;
    _buffer[index + 5] = rgba.b;
    _buffer[index + 6] = rgba.a;
    index += 7;

    _vertexCount += 2;

    const int32_t attributes[] = { 3, 4, 0 };
    _mesh = std::shared_ptr<Mesh>(new Mesh(_buffer.get(), _vertexCount, attributes, GL_LINES));
}

void vx::LineRenderer::addCube()
{

}

void vx::LineRenderer::draw()
{
    _mesh->draw();
}
