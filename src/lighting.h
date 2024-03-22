#pragma once
#include <vector>
#include "../wolf/wolf.h"
#include "diffuseLight.h"
#include "pointLight.h"
class Lighting
{
public:
    Lighting();
    Lighting(int numPointLights);
    ~Lighting();

    void addDiffuseLight(const glm::vec3 &newLightDir, const glm::vec3 &newLightCol);
    void addAmbientLight(const glm::vec3 &newLightCol);
    void addPointLight(const glm::vec3 &newLightPos, const glm::vec3 &newLightCol, const glm::vec3 &newLightAtt, float newRange);
    void addPointLight(const glm::vec3 &newLightPos, const glm::vec3 &newLightCol, const glm::vec3 &newLightAtt, float newRange, const glm::vec3 &newLightAmb);

    glm::vec3 getDiffuseLightDirection();
    glm::vec3 getDiffuseLightColour();

    glm::vec3 getAmbientLightColour();

    std::vector<glm::vec3> getPointLightPositions();
    std::vector<glm::vec3> getPointLightColours();
    std::vector<glm::vec3> getPointLightAttenuations();
    std::vector<float> getPointLightRanges();
    std::vector<glm::vec3> getPointLightAmbients();
    int getPointLightCount();

private:
    const int POINT_LIGHT_COUNT = 0;

    int diffuseLightCount = 0;

    glm::vec3 ambientLight = glm::vec3(0.0f);
    DiffuseLight *diffuseLight = nullptr;
    std::vector<PointLight *> PointLights;
};