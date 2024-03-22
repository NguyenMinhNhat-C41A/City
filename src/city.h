#pragma once
#include <vector>
#include "../wolf/wolf.h"

#include "houses.h"
#include "skybox.h"
#include "rng.h"
class City
{
public:
    City();
    ~City();
    void update(const float dt);
    void render(const glm::mat4 &mProj, const glm::mat4 &mView);
    void render(const glm::mat4 &mProj, const glm::mat4 &mView, const glm::vec3 &lightDiffDir, const glm::vec3 &lightDiffCol, const glm::vec3 &lightAmbCol);
    void render(const glm::mat4 &mProj, const glm::mat4 &mView, Lighting *lighting);

private:
    Houses *houses = nullptr;
    Skybox *citySky = nullptr;
};