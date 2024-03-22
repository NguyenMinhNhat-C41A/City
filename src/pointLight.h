#pragma once
#include "../wolf/wolf.h"
class PointLight
{
public:
    PointLight();
    PointLight(const glm::vec3 &newLightPos, const glm::vec3 &newLightCol, const glm::vec3 &newLightAtt, float newRange);
    PointLight(const glm::vec3 &newLightPos, const glm::vec3 &newLightCol, const glm::vec3 &newLightAtt, float newRange, const glm::vec3 &newLightAmb);
    ~PointLight();

    glm::vec3 getLightPosition();
    glm::vec3 getLightColour();
    glm::vec3 getLightAttenuation();
    float getLightRange();

    glm::vec3 getLightAmbient();

private:
    glm::vec3 lightPosition = glm::vec3(1.0f, 1.0f, 1.0f);
    glm::vec3 lightColour = glm::vec3(1.0f, 1.0f, 1.0f);
    glm::vec3 lightAttenuation = glm::vec3(0.0f, 0.0f, 1.0f);
    float lightRange = 0.2f;

    glm::vec3 lightAmbient = glm::vec3(0.1f);
};