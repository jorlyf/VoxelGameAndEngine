#pragma once
#include <string>

namespace vx
{
    class PathManager
    {
    public:
        static void init(
            const std::string& resourcesPath
        );

        static std::string getRootPath();
        static std::string getResourcesPath();

    private:
        static std::string _resourcesPath;
    };
}
