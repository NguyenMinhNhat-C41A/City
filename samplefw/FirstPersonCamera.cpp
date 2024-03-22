#include "FirstPersonCamera.h"

FirstPersonCamera::FirstPersonCamera(wolf::App *pApp) : m_pApp(pApp)
{

    this->lastMousePos = this->m_pApp->getMousePos();
    this->camSpeed = this->camSpeeds.at(this->camSpeedIndex);
}

FirstPersonCamera::~FirstPersonCamera()
{
}

glm::mat4 FirstPersonCamera::getViewMatrix()
{
    return glm::lookAt(this->camPosition, this->camPosition + this->camViewFront, this->camUp);
}

glm::mat4 FirstPersonCamera::getProjMatrix(const int width, const int height)
{
    return glm::perspective(m_fov, (float)width / (float)height, m_near, m_far);
}

void FirstPersonCamera::update(const float dt)
{

    glm::vec2 mousePos = m_pApp->getMousePos();

    if (m_pApp->isKeyDown('w'))
    {
        this->camPosition += this->camSpeed * dt * glm::vec3(this->camMoveFront.x, 0.0f, this->camMoveFront.z);
    }
    if (m_pApp->isKeyDown('s'))
    {
        this->camPosition -= this->camSpeed * dt * glm::vec3(this->camMoveFront.x, 0.0f, this->camMoveFront.z);
    }

    if (m_pApp->isKeyDown('a'))
    {
        this->camPosition -= glm::normalize(glm::cross(this->camMoveFront, this->camUp)) * this->camSpeed * dt;
    }
    if (m_pApp->isKeyDown('d'))
    {
        this->camPosition += glm::normalize(glm::cross(this->camMoveFront, this->camUp)) * this->camSpeed * dt;
    }

    if (m_pApp->isKeyDown('f'))
    {
        if (!this->m_bIsFDown)
        {
            this->m_bIsFDown = true;
        }
    }
    else
    {
        if (this->m_bIsFDown)
        {
            this->m_bIsFDown = false;
            this->m_bIsWheelchairMode = !this->m_bIsWheelchairMode;
        }
    }

    if (m_pApp->isKeyDown('r'))
    {
        if (!this->m_bIsRDown)
        {
            this->m_bIsRDown = true;
        }
    }
    else
    {
        if (this->m_bIsRDown)
        {
            this->m_bIsRDown = false;

            this->camSpeedIndex = (this->camSpeedIndex + 1) % this->camSpeeds.size();
            this->camSpeed = this->camSpeeds.at(this->camSpeedIndex);
        }
    }

    if (m_pApp->isKeyDown(GLFW_KEY_SPACE))
    {
        this->camPosition = glm::vec3(this->camPosition.x, this->camPosition.y + this->camFlySpeed * dt, this->camPosition.z);
    }

    if (m_pApp->isKeyDown(GLFW_KEY_LEFT_SHIFT))
    {
        this->camPosition = glm::vec3(this->camPosition.x, this->camPosition.y - this->camFlySpeed * dt, this->camPosition.z);
    }

    if (m_pApp->isKeyDown(GLFW_KEY_UP))
    {
        this->pitch += this->camTankRotSpeed * dt;
    }

    if (m_pApp->isKeyDown(GLFW_KEY_DOWN))
    {
        this->pitch -= this->camTankRotSpeed * dt;
    }

    if (m_pApp->isKeyDown(GLFW_KEY_LEFT))
    {
        this->yaw -= this->camTankRotSpeed * dt;
    }

    if (m_pApp->isKeyDown(GLFW_KEY_RIGHT))
    {
        this->yaw += this->camTankRotSpeed * dt;
    }

    float xOffset = mousePos.x - this->lastMousePos.x;
    float yOffset = mousePos.y - this->lastMousePos.y;
    this->lastMousePos.x = mousePos.x;
    this->lastMousePos.y = mousePos.y;

    this->yaw += xOffset * this->mouseSensitivity;

    if (this->yaw < -180.0f)
    {
        this->yaw = 180.0f;
    }

    if (this->yaw > 180.0f)
    {
        this->yaw = -180.0f;
    }

    if (this->m_bIsWheelchairMode)
    {
        this->pitch = 0.0f;
    }
    else
    {
        this->pitch -= yOffset * this->mouseSensitivity;

        if (this->pitch > MAX_PITCH)
        {
            this->pitch = MAX_PITCH;
        }

        if (this->pitch < -MAX_PITCH)
        {
            this->pitch = -MAX_PITCH;
        }
    }
    glm::vec3 moveDirection = glm::vec3(
        cos(glm::radians(this->yaw)),
        0.0f,
        sin(glm::radians(this->yaw)));
    this->camMoveFront = glm::normalize(moveDirection);

    glm::vec3 lookDirection = glm::vec3(
        moveDirection.x * cos(glm::radians(this->pitch)),
        sin(glm::radians(this->pitch)),
        moveDirection.z * cos(glm::radians(this->pitch)));
    this->camViewFront = glm::normalize(lookDirection);
}