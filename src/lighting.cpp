#include "lighting.h"

Lighting::Lighting() : POINT_LIGHT_COUNT(0)
{
}

Lighting::Lighting(int numPointLights) : POINT_LIGHT_COUNT(numPointLights)
{
}

Lighting::~Lighting()
{
    delete this->diffuseLight;
    this->diffuseLight = nullptr;

    for (auto pointLight : PointLights)
    {
        delete pointLight;
        pointLight = nullptr;
    }
    this->PointLights.clear();
}

void Lighting::addDiffuseLight(const glm::vec3 &newLightDir, const glm::vec3 &newLightCol)
{
    if (!this->diffuseLight)
    {
        this->diffuseLight = new DiffuseLight(newLightDir, newLightCol);
    }
}

void Lighting::addAmbientLight(const glm::vec3 &newLightCol)
{
    this->ambientLight = newLightCol;
}

void Lighting::addPointLight(const glm::vec3 &newLightPos, const glm::vec3 &newLightCol, const glm::vec3 &newLightAtt, float newRange)
{
    if (this->PointLights.size() < POINT_LIGHT_COUNT)
    {
        this->PointLights.push_back(new PointLight(newLightPos, newLightCol, newLightAtt, newRange));
    }
}

void Lighting::addPointLight(const glm::vec3 &newLightPos, const glm::vec3 &newLightCol, const glm::vec3 &newLightAtt, float newRange, const glm::vec3 &newLightAmb)
{
    if (this->PointLights.size() < POINT_LIGHT_COUNT)
    {
        this->PointLights.push_back(new PointLight(newLightPos, newLightCol, newLightAtt, newRange, newLightAmb));
    }
}

glm::vec3 Lighting::getDiffuseLightDirection()
{
    if (this->diffuseLight)
    {
        return this->diffuseLight->getLightDirection();
    }
    return glm::normalize(glm::vec3(0.0f, 0.0f, 0.0f));
}

glm::vec3 Lighting::getDiffuseLightColour()
{
    if (this->diffuseLight)
    {
        return this->diffuseLight->getLightColour();
    }
    return glm::vec3(0.0f, 0.0f, 0.0f);
}

glm::vec3 Lighting::getAmbientLightColour()
{
    return this->ambientLight;
}

std::vector<glm::vec3> Lighting::getPointLightPositions()
{
    std::vector<glm::vec3> poiliPoses;
    for (auto poili : this->PointLights)
    {
        poiliPoses.push_back(poili->getLightPosition());
    }
    return poiliPoses;
}

std::vector<glm::vec3> Lighting::getPointLightColours()
{

    std::vector<glm::vec3> poiliColos;
    for (auto poili : this->PointLights)
    {
        poiliColos.push_back(poili->getLightColour());
    }
    return poiliColos;
}

std::vector<glm::vec3> Lighting::getPointLightAttenuations()
{

    std::vector<glm::vec3> poiliAtts;
    for (auto poili : this->PointLights)
    {
        poiliAtts.push_back(poili->getLightAttenuation());
    }
    return poiliAtts;
}
std::vector<float> Lighting::getPointLightRanges()
{

    std::vector<float> poiliRngs;
    for (auto poili : this->PointLights)
    {
        poiliRngs.push_back(poili->getLightRange());
    }
    return poiliRngs;
}

std::vector<glm::vec3> Lighting::getPointLightAmbients()
{
    std::vector<glm::vec3> poiliAmbs;
    for (auto poili : this->PointLights)
    {
        poiliAmbs.push_back(poili->getLightAmbient());
    }
    return poiliAmbs;
}

int Lighting::getPointLightCount()
{
    return this->POINT_LIGHT_COUNT;
}