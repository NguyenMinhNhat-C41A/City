#pragma once
#include <vector>
#include "../wolf/wolf.h"
#include "building.h"
#include "flats.h"
#include "skybox.h"
#include "rng.h"
class Cityscape
{
public:
    Cityscape();
    virtual ~Cityscape();
    void update(const float dt);
    void render(const glm::mat4 &mProj, const glm::mat4 &mView);

    void regenerateCity();

private:
    const float BUILDING_PLOT_SIZE = 8.0f;
    const float ROAD_SIZE = 4.0f;
    const float CURB_HEIGHT = 0.125f;
    const float OUTER_EDGE_SIZE = 10.0f;

    const float GAP_SIZE = 250.0f;
    const float WALL_HEIGHT = 50.0f;
    const float WALL_GLOW_HEIGHT = 5.0f;
    const float NUM_WALL_GLOWS = 50;
    const int QUARTER_LENGTH = 29;

    const int GRID_LENGTH = QUARTER_LENGTH * 2 + 1;
    const float GRID_SIZE = GRID_LENGTH * (BUILDING_PLOT_SIZE + ROAD_SIZE);
    const float CITY_SIZE = GRID_SIZE + ROAD_SIZE;
    const float ISLAND_SIZE = CITY_SIZE + OUTER_EDGE_SIZE * 2;

    const float PILLAR_SIZE = 30.0f;
    const float INNER_PILLAR_SIZE = 20.0f;
    const float RING_HEIGHT = 4.0f;
    const int NUM_RINGS = 8;
    const float UPPER_CLIFF_HEIGHT = 40.0f;
    const float LOWER_CLIFF_HEIGHT = 80.0f;
    const float RING_GAP_HEIGHT = static_cast<float>((LOWER_CLIFF_HEIGHT - RING_HEIGHT * NUM_RINGS) / (NUM_RINGS - 1.0f));
    const float CLIFF_HEIGHT = UPPER_CLIFF_HEIGHT + LOWER_CLIFF_HEIGHT;
    const float CLIFF_SIZE = ISLAND_SIZE - PILLAR_SIZE * 2.0f;

    float worldLength = 0.0f;

    std::vector<Building *> buildings;

    Flats *signposts = nullptr;

    Flats *roads = nullptr;

    Flats *curbs = nullptr;

    Flats *fences = nullptr;

    Flats *outerGeometry = nullptr;

    Skybox *citySky = nullptr;

    void generateCity();
    void generateBlock(const float xPosition, const float zPosition);
    void generateCentre();
    void generateSignposts();
    void generateSignpostFace(const float xPosition, const float zPosition);
    void generateSignpostTop(const float xPosition, const float zPosition);

    void generateOuterGeometry();
};