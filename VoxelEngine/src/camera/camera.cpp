#include <algorithm>
#include <glm/ext.hpp>
#include "camera.hpp"

vx::Camera::Camera(const glm::vec3& position, const float fov, const float aspectRatio)
{
    _position = position;
    _fov = fov;
    setAspectRatio(aspectRatio);

    _rotationX = 0.0f;
    _rotationY = 0.0f;
    _rotationZ = 0.0f;
    resetRotationMatrix();

    updateVectors();
}

glm::vec3 vx::Camera::getPosition() const
{
    return _position;
}

void vx::Camera::setPosition(const glm::vec3& position)
{
    _position = position;
}

void vx::Camera::move(const glm::vec3& offset)
{
    setPosition(_position + offset);
}

void vx::Camera::rotate(const float x, const float y, const float z)
{
    _rotationX += x;
    _rotationY += y;
    _rotationZ += z;

    _rotationX = std::clamp(_rotationX, glm::radians(_minUpAngle), glm::radians(_maxUpAngle));

    resetRotationMatrix();
    _rotationMatrix = glm::rotate(_rotationMatrix, _rotationZ, glm::vec3(0, 0, 1));
    _rotationMatrix = glm::rotate(_rotationMatrix, _rotationY, glm::vec3(0, 1, 0));
    _rotationMatrix = glm::rotate(_rotationMatrix, _rotationX, glm::vec3(1, 0, 0));

    updateVectors();
}

void vx::Camera::resetRotationMatrix()
{
    _rotationMatrix = glm::mat4(1.0f);
}

void vx::Camera::setAspectRatio(const float aspectRatio)
{
    _aspectRatio = aspectRatio;
}

glm::vec3 vx::Camera::getFrontVec() const
{
    return _front;
}

glm::vec3 vx::Camera::getUpVec() const
{
    return  _up;
}

glm::vec3 vx::Camera::getRightVec() const
{
    return _right;
}

glm::mat4 vx::Camera::getProjectionMatrix() const
{
    return glm::perspective(_fov, _aspectRatio, 0.05f, 1000.0f);
}

glm::mat4 vx::Camera::getViewMatrix() const
{
    return glm::lookAt(_position, _position + _front, _up);
}

glm::mat4 vx::Camera::getProjectionViewMatrix() const
{
    return getProjectionMatrix() * getViewMatrix();
}

void vx::Camera::updateVectors()
{
    _front = glm::vec3(_rotationMatrix * glm::vec4(0, 0, -1, 1));
    _right = glm::vec3(_rotationMatrix * glm::vec4(1, 0, 0, 1));
    _up = glm::vec3(_rotationMatrix * glm::vec4(0, 1, 0, 1));
}
