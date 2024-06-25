cmake_minimum_required(VERSION 3.25)

project(voxel-engine-graphics)

include_directories(../../deps/include)

find_library(
    GL_LIB
    GL
    PATHS ../../deps/lib
    REQUIRED
)

find_library(
    GLFW_LIB
    glfw3
    PATHS ../../deps/lib
    REQUIRED
)

find_library(
    GLEW_LIB
    GLEW
    PATHS ../../deps/lib
    REQUIRED
)

find_library(
    GLM_LIB
    glm
    REQUIRED
)

add_library(${PROJECT_NAME} STATIC
    mesh.cpp
    shader.cpp
    texture.cpp
)

target_link_libraries(${PROJECT_NAME} PUBLIC
    ${GL_LIB}
    ${GLFW_LIB}
    ${GLEW_LIB}
    ${GLM_LIB}
    voxel-engine-loaders
)

target_include_directories(${PROJECT_NAME} PUBLIC
    ${PROJECT_SOURCE_DIR}
)
