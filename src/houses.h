#pragma once
#include <algorithm>
#include <iostream>
#include <random>
#include <set>
#include <vector>
#include "../wolf/wolf.h"
#include "polys.h"
#include "rng.h"

class Houses
{
public:
    Houses();
    ~Houses();

    void update(float dt);
    void render(const glm::mat4 &mProj, const glm::mat4 &mView);
    void render(const glm::mat4 &mProj, const glm::mat4 &mView, const glm::vec3 &lightDiffDir, const glm::vec3 &lightDiffCol, const glm::vec3 &lightAmbCol);
    void render(const glm::mat4 &mProj, const glm::mat4 &mView, Lighting *lighting);

    void beginConstructingHouses();
    void constructHouse(glm::vec3 coords);
    void endConstructingHouses();
    void endInitialisation();

private:
    Polys *housesFlats = nullptr;
    int texIndex = 0;
};