#include "diffuseLight.h"

DiffuseLight::DiffuseLight()
{
}

DiffuseLight::DiffuseLight(const glm::vec3 &newLightDir, const glm::vec3 &newLightCol)
{
    this->lightDirection = newLightDir;
    this->lightColour = newLightCol;
};

DiffuseLight::~DiffuseLight()
{
}

void DiffuseLight::setLightDirection(const glm::vec3 &newLightDir)
{
    this->lightDirection = newLightDir;
}

glm::vec3 DiffuseLight::getLightDirection()
{
    return this->lightDirection;
}

void DiffuseLight::setLightColour(const glm::vec3 &newLightCol)
{
    this->lightColour = newLightCol;
}

glm::vec3 DiffuseLight::getLightColour()
{
    return this->lightColour;
}