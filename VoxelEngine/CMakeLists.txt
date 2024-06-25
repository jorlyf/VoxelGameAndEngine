cmake_minimum_required(VERSION 3.25)

set (CMAKE_CXX_STANDARD 20)

project(voxel-engine)

include_directories(deps/include)

add_subdirectory(src/camera)
add_subdirectory(src/dt)
add_subdirectory(src/graphics)
add_subdirectory(src/loaders)
add_subdirectory(src/renderers)
add_subdirectory(src/utils)
add_subdirectory(src/voxel)
add_subdirectory(src/window)

add_library(${PROJECT_NAME}
    src/engine.cpp
)

target_link_libraries(${PROJECT_NAME} PUBLIC
    voxel-engine-camera
    voxel-engine-dt
    voxel-engine-graphics
    voxel-engine-loaders
    voxel-engine-renderers
    voxel-engine-utils
    voxel-engine-voxel
    voxel-engine-window
)

target_include_directories(${PROJECT_NAME} PUBLIC
    src
)