#pragma once
#include "../wolf/wolf.h"
class DiffuseLight
{
public:
    DiffuseLight();
    DiffuseLight(const glm::vec3 &newLightDir, const glm::vec3 &newLightCol);
    ~DiffuseLight();

    void setLightDirection(const glm::vec3 &newLightDir);
    glm::vec3 getLightDirection();
    void setLightColour(const glm::vec3 &newLightCol);
    glm::vec3 getLightColour();

private:
    glm::vec3 lightDirection = glm::vec3(1.0f, 1.0f, 1.0f);
    glm::vec3 lightColour = glm::vec3(1.0f, 1.0f, 1.0f);
};