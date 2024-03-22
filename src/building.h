#pragma once
#include <algorithm>
#include <iostream>
#include <random>
#include <set>
#include <vector>
#include "../wolf/wolf.h"
#include "flats.h"
#include "rng.h"

class Building
{
public:
    Building();
    Building(const glm::vec3 coords);
    virtual ~Building();
    void update(const float dt);
    void render(const glm::mat4 &mProj, const glm::mat4 &mView);

    void translateTo(const glm::vec3 coords);

    void regenerateBuilding();

private:
    Flats *buildingFlats;

    const glm::vec3 BUILDING_COORDS = glm::vec3(1.0f);

    void generateCentreBuilding();

    void generateTypeOneBuilding(const glm::vec3 coords);

    void generateTypeTwoBuilding(const glm::vec3 coords);

    void generateTypeThreeBuilding(const glm::vec3 coords);
};