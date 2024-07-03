#pragma once
#include <memory>
#include <vector>
#include <utility>
#include "camera.hpp"
#include "engine.hpp"
#include "shader.hpp"
#include "mesh.hpp"
#include "voxelchunks.hpp"
#include "voxelrenderer.hpp"
#include "linerenderer.hpp"
#include "textureatlas.hpp"

namespace vxg
{
    class GameEngine : public vx::Engine
    {
    public:
        GameEngine(const std::string& windowTitle);
        virtual ~GameEngine();

        virtual void onStart();
        virtual void onUpdate();
        virtual void onRender();

    private:
        std::shared_ptr<vx::Camera> _camera = nullptr;

        GLuint _VAO, _VBO;
        std::shared_ptr<vx::Shader> _shader = nullptr;
        std::shared_ptr<vx::TextureAtlas> _textureAtlas = nullptr;

        std::shared_ptr<vx::VoxelChunks> _chunks = nullptr;
        std::vector<std::pair<vx::VoxelChunk*, std::shared_ptr<vx::Mesh>>> _chunkMeshes;

        std::shared_ptr<vx::Shader> _lineShader = nullptr;

        int32_t _fpsTitleCounter = 0;

        std::shared_ptr<vx::VoxelRenderer> _voxelRenderer = nullptr;

        void generateVoxelChunks();
        void renderVoxelChunks();
    };
}
