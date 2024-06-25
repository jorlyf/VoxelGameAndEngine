#pragma once
#include <glm/glm.hpp>

namespace vx
{
    class Camera
    {
    public:
        Camera(const glm::vec3& position, const float fov, const float aspectRatio);

        glm::vec3 getPosition() const;
        void setPosition(const glm::vec3& position);

        void move(const glm::vec3& offset);

        void rotate(const float x, const float y, const float z);

        void setAspectRatio(const float aspectRatio);

        glm::vec3 getFrontVec() const;
        glm::vec3 getUpVec() const;
        glm::vec3 getRightVec() const;

        glm::mat4 getProjectionMatrix() const;
        glm::mat4 getViewMatrix() const;
        glm::mat4 getProjectionViewMatrix() const;

    private:
        glm::vec3 _position;

        glm::vec3 _front;
        glm::vec3 _up;
        glm::vec3 _right;

        float _rotationX;
        float _rotationY;
        float _rotationZ;

        float _minUpAngle = -89.0f;
        float _maxUpAngle = 89.0f;

        glm::mat4 _rotationMatrix;
        float _fov;
        float _aspectRatio;

        void updateVectors();
        void resetRotationMatrix();
    };
}
