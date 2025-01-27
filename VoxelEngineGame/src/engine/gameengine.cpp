#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "gameengine.hpp"
#include "windowevents.hpp"
#include "voxelchunks.hpp"
#include "deltatime.hpp"
#include "pathmanager.hpp"
#include "chunkgeneratorellipse.hpp"
#include "chunkgeneratorflat.hpp"
#include "chunkgeneratorstandard.hpp"

vxg::GameEngine::GameEngine(
    const std::string& windowTitle
)
    :Engine(windowTitle)
{
    vx::PathManager::init("resources");
}

vxg::GameEngine::~GameEngine()
{
}

void vxg::GameEngine::onStart()
{
    const glm::u32vec2 windowSize = _window->getSize();
    _camera = std::make_shared<vx::Camera>(
        glm::vec3(0.0f, 0.0f, 0.0f), 70.0f,
        (float)windowSize.x / windowSize.y
    );

    const std::string resourcesPath = vx::PathManager::getResourcesPath();

    _shader = std::shared_ptr<vx::Shader>(vx::Shader::loadFromFile(resourcesPath + "/main.glslv", resourcesPath + "/main.glslf"));
    _lineShader = std::shared_ptr<vx::Shader>(vx::Shader::loadFromFile(
        resourcesPath + "/shaders/line.glslv",
        resourcesPath + "/shaders/line.glslf"
    ));

    std::map<std::string, uint16_t> textureAtlasBinding;
    textureAtlasBinding["grass"] = 0;
    textureAtlasBinding["cyan_wool"] = 1;

    _textureAtlas = std::shared_ptr<vx::TextureAtlas>(vx::TextureAtlas::loadFromFile(
        textureAtlasBinding,
        glm::ivec2(64, 64),
        resourcesPath + "/atlas.png"
    ));

    vx::IVoxelChunkGenerator* generator = new ChunkGeneratorStandard();

    _voxelRenderer = std::shared_ptr<vx::VoxelRenderer>(new vx::VoxelRenderer(_textureAtlas.get()));
    _chunks = std::shared_ptr<vx::VoxelChunks>(new vx::VoxelChunks(generator));
    _chunks->setGenerationRadius(2);

    generateVoxelChunks();
    renderVoxelChunks();

    // X
    vx::LineRenderer::addLine(
        glm::vec3(-1000.f, 0.f, 0.f),
        glm::vec3(1000.f, 0.f, 0.f),
        glm::vec4(0, 1, 0, 1)
    );

    // Z
    vx::LineRenderer::addLine(
        glm::vec3(0.f, 0.f, -1000.f),
        glm::vec3(0.f, 0.f, 1000.f),
        glm::vec4(0, 0, 1, 1)
    );

    glClearColor(0.6f, 0.62f, 0.65f, 1);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void vxg::GameEngine::onUpdate()
{
    if (++_fpsTitleCounter > 360)
    {
        _fpsTitleCounter = 0;
        const int32_t fps = 1.0 / vx::DeltaTime::getDt();
        const std::string fpsTitle = std::to_string(fps);
        _window->setTitle(fpsTitle);
    }

    generateVoxelChunks();

    const float cameraMoveSpeed = 25.0f * vx::DeltaTime::getDt();
    if (vx::WindowEvents::getKeyboardKeyState(GLFW_KEY_W).isHolding)
    {
        _camera->move(_camera->getFrontVec() * cameraMoveSpeed);
    }
    if (vx::WindowEvents::getKeyboardKeyState(GLFW_KEY_S).isHolding)
    {
        _camera->move(-_camera->getFrontVec() * cameraMoveSpeed);
    }
    if (vx::WindowEvents::getKeyboardKeyState(GLFW_KEY_A).isHolding)
    {
        _camera->move(-_camera->getRightVec() * cameraMoveSpeed);
    }
    if (vx::WindowEvents::getKeyboardKeyState(GLFW_KEY_D).isHolding)
    {
        _camera->move(_camera->getRightVec() * cameraMoveSpeed);
    }
    const float cameraRotateSpeed = 0.002f;
    const glm::vec2 deltaMousePosition = vx::WindowEvents::getDeltaMousePosition();
    _camera->rotate(
        deltaMousePosition.y * cameraRotateSpeed,
        deltaMousePosition.x * cameraRotateSpeed,
        0
    );
}

void vxg::GameEngine::onRender()
{
    removeVoxelChunks();
    renderVoxelChunks();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    _shader->use();
    _shader->setUniformMatrix("projview", _camera->getProjectionViewMatrix());

    _textureAtlas->bind();
    for (auto& chunkMesh : _chunkMeshes)
    {
        const glm::ivec2 chunkPosition = chunkMesh.first;
        const vx::Mesh* mesh = chunkMesh.second.get();
        const glm::mat4 translateMatrix = glm::translate(
            glm::mat4(1.0f),
            glm::vec3(
                chunkPosition.x * static_cast<int32_t>(vx::VoxelChunk::SIZE),
                0,
                chunkPosition.y * static_cast<int32_t>(vx::VoxelChunk::SIZE)
            )
        );
        const glm::mat4 scaleMatrix = glm::scale(
            glm::mat4(1.0f),
            glm::vec3(
                vx::VoxelChunk::VOXEL_SIZE,
                vx::VoxelChunk::VOXEL_SIZE,
                vx::VoxelChunk::VOXEL_SIZE
            )
        );
        const glm::mat4 modelMatrix = scaleMatrix * translateMatrix;
        _shader->setUniformMatrix("model", modelMatrix);
        mesh->draw();
    }

    _lineShader->use();
    _lineShader->setUniformMatrix("projview", _camera->getProjectionViewMatrix());
    vx::LineRenderer::draw();
}

void vxg::GameEngine::generateVoxelChunks()
{
    const glm::vec3 cameraPosition = _camera->getPosition();
    _chunks->update(cameraPosition);
}

void vxg::GameEngine::removeVoxelChunks()
{
    const std::vector<glm::ivec2> chunkPositionsToRemove = _chunks->getChunkPositionsToRemove();
    for (auto& chunkPositionToRemove : chunkPositionsToRemove)
    {
        _chunkMeshes.erase(chunkPositionToRemove);
    }
}

void vxg::GameEngine::renderVoxelChunks()
{
    const std::vector<glm::ivec2> chunkPositionsToRender = _chunks->getChunkPositionsToRender();
    for (auto& chunkPositionToRender : chunkPositionsToRender)
    {
        const vx::VoxelChunk* chunkToRender = _chunks->getChunkAt(chunkPositionToRender);
        renderVoxelChunk(chunkToRender);
    }
}

void vxg::GameEngine::renderVoxelChunk(const vx::VoxelChunk* chunk)
{
    const glm::ivec2 chunkPosition = chunk->getPosition();
    const std::shared_ptr<vx::Mesh> mesh(_voxelRenderer->renderChunk(*chunk, *_chunks));
    _chunkMeshes[chunkPosition] = mesh;
}
