#include <filesystem>
#include "pathmanager.hpp"

std::string vx::PathManager::_resourcesPath;

void vx::PathManager::init(const std::string& resourcesPath)
{
    _resourcesPath = resourcesPath;
}

std::string vx::PathManager::getRootPath()
{
    return std::filesystem::current_path();
}

std::string vx::PathManager::getResourcesPath()
{
    return _resourcesPath;
}
