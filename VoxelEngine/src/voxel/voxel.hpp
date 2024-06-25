#pragma once
#include <cstdint>

namespace vx
{
    class Voxel
    {
    public:
        Voxel();
        Voxel(const uint16_t id);

        uint16_t getId() const;

    private:
        uint16_t _id;
    };
}
