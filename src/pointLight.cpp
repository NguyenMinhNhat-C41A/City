#include "pointLight.h"

PointLight::PointLight()
{
}

PointLight::PointLight(const glm::vec3 &newLightPos, const glm::vec3 &newLightCol, const glm::vec3 &newLightAtt, float newRange)
{
    this->lightPosition = newLightPos;
    this->lightColour = newLightCol;
    this->lightAttenuation = newLightAtt;
    this->lightRange = newRange;
}

PointLight::PointLight(const glm::vec3 &newLightPos, const glm::vec3 &newLightCol, const glm::vec3 &newLightAtt, float newRange, const glm::vec3 &newLightAmb)
{
    this->lightPosition = newLightPos;
    this->lightColour = newLightCol;
    this->lightAttenuation = newLightAtt;
    this->lightRange = newRange;
    this->lightAmbient = newLightAmb;
}

PointLight::~PointLight()
{
}

glm::vec3 PointLight::getLightPosition()
{
    return this->lightPosition;
}
glm::vec3 PointLight::getLightColour()
{
    return this->lightColour;
}
glm::vec3 PointLight::getLightAttenuation()
{
    return this->lightAttenuation;
}
float PointLight::getLightRange()
{
    return this->lightRange;
}

glm::vec3 PointLight::getLightAmbient()
{
    return this->lightAmbient;
}