#pragma once

#include <vector>

#include <SDL/SDL_opengl.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Engine
{
    enum Camera_Movement {
        FORWARD,
        BACKWARD,
        LEFT,
        RIGHT
    };

    const float YAW = -90.0f;
    const float PITCH = 0.0f;
    const float SPEED = 2.5f;
    const float SENSITIVITY = 50.f;
    const float ZOOM = 45.0f;

    class Camera
    {
    public:
        Camera(
            glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
            float yaw = YAW, float pitch = PITCH
        );
        glm::mat4 getViewMatrix();
        void processKeyboard(Camera_Movement direction, float deltaTime);
        void processMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true);
        void processMouseScroll(float yoffset);
        float getZoom();

    private:
        glm::vec3 _position;
        glm::vec3 _front;
        glm::vec3 _up;
        glm::vec3 _right;
        glm::vec3 _worldUp;

        float _yaw;
        float _pitch;
        float _movementSpeed;
        float _mouseSensitivity;
        float _zoom;

        void _updateCameraVectors();
    };
}