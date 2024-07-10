#include <cstring>
#include "linerenderer.hpp"

std::shared_ptr<vx::LineRenderer::LineVertex[]> vx::LineRenderer::_vertices = nullptr;
uint32_t vx::LineRenderer::_vertexCount = 0;

std::shared_ptr<vx::Mesh> vx::LineRenderer::_mesh = nullptr;

void vx::LineRenderer::addLine(
    const glm::vec3& start,
    const glm::vec3& end,
    const glm::vec4& rgba
)
{
    std::shared_ptr<LineVertex[]> newVertices = std::shared_ptr<LineVertex[]>(new LineVertex[_vertexCount + 2]);
    std::memcpy(newVertices.get(), _vertices.get(), _vertexCount * sizeof(LineVertex));
    _vertices = newVertices;

    uint32_t index = _vertexCount;
    _vertices[index].position.x = start.x;
    _vertices[index].position.y = start.y;
    _vertices[index].position.z = start.z;
    _vertices[index].color.r = rgba.r;
    _vertices[index].color.g = rgba.g;
    _vertices[index].color.b = rgba.b;
    _vertices[index].color.a = rgba.a;
    index++;

    _vertices[index].position.x = end.x;
    _vertices[index].position.y = end.y;
    _vertices[index].position.z = end.z;
    _vertices[index].color.r = rgba.r;
    _vertices[index].color.g = rgba.g;
    _vertices[index].color.b = rgba.b;
    _vertices[index].color.a = rgba.a;

    _vertexCount += 2;

    const int32_t attributes[] = { 3, 4, 0 };
    _mesh = std::shared_ptr<Mesh>(new Mesh(reinterpret_cast<float*>(_vertices.get()), _vertexCount, attributes, GL_LINES));
}

void vx::LineRenderer::addCube()
{

}

void vx::LineRenderer::draw()
{
    _mesh->draw();
}
