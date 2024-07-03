cmake_minimum_required(VERSION 3.25)

project(game)

include_directories(../VoxelEngine/deps/include)

# find_library(
#     GL_LIB
#     GL
#     PATHS ../deps/lib
#     REQUIRED
# )

# find_library(
#     GLFW_LIB
#     glfw3
#     PATHS ../deps/lib
#     REQUIRED
# )

# find_library(
#     GLEW_LIB
#     GLEW
#     PATHS ../deps/lib
#     REQUIRED
# )

# find_library(
#     GLM_LIB
#     glm
#     REQUIRED
# )

add_subdirectory(../VoxelEngine voxel-engine)

add_executable(${PROJECT_NAME}
    src/main.cpp
    src/chunk-generators/ellipse/chunkgeneratorellipse.cpp
    src/chunk-generators/flat/chunkgeneratorflat.cpp
    src/engine/gameengine.cpp
)

target_link_libraries(${PROJECT_NAME} PUBLIC
    # ${GL_LIB}
    # ${GLFW_LIB}
    # ${GLEW_LIB}
    # ${GLM_LIB}
    voxel-engine
)

target_include_directories(${PROJECT_NAME} PUBLIC
    ${PROJECT_SOURCE_DIR}
    src
    src/chunk-generators/ellipse
    src/chunk-generators/flat
    src/engine
)
