#include "voxel.hpp"

vx::Voxel::Voxel()
{
    _id = 0;
}

vx::Voxel::Voxel(const uint16_t id)
{
    _id = id;
}

uint16_t vx::Voxel::getId() const
{
    return _id;
}