#include "cityscape.h"

Cityscape::Cityscape() : GRID_LENGTH(QUARTER_LENGTH * 2 + 1),
                         GRID_SIZE(GRID_LENGTH * (BUILDING_PLOT_SIZE + ROAD_SIZE)),
                         CITY_SIZE(GRID_SIZE + ROAD_SIZE),
                         ISLAND_SIZE(CITY_SIZE + OUTER_EDGE_SIZE * 2),
                         CLIFF_HEIGHT(UPPER_CLIFF_HEIGHT + LOWER_CLIFF_HEIGHT),
                         CLIFF_SIZE(ISLAND_SIZE - PILLAR_SIZE * 2.0f),
                         RING_GAP_HEIGHT(static_cast<float>((LOWER_CLIFF_HEIGHT - RING_HEIGHT * NUM_RINGS) / (NUM_RINGS - 1.0f)))
{
    this->citySky = new Skybox();

    this->signposts = new Flats();
    this->signposts->beginConstructingVertices();
    this->roads = new Flats();
    this->roads->beginConstructingVertices();
    this->fences = new Flats();
    this->fences->beginConstructingVertices();
    this->curbs = new Flats();
    this->curbs->beginConstructingVertices();
    this->outerGeometry = new Flats();
    this->outerGeometry->beginConstructingVertices();

    this->generateCity();

    this->signposts->endConstructingVertices();
    this->signposts->endInit();
    this->roads->endConstructingVertices();
    this->roads->endInit();
    this->fences->endConstructingVertices();
    this->fences->endInit();
    this->curbs->endConstructingVertices();
    this->curbs->endInit();
    this->outerGeometry->endConstructingVertices();
    this->outerGeometry->endInit();
}

Cityscape::~Cityscape()
{
    std::cout << "Destroying Cityscape" << std::endl;

    for (auto building : this->buildings)
    {
        delete building;
    }
    this->buildings.clear();

    delete this->signposts;
    this->signposts = nullptr;

    delete this->roads;
    this->roads = nullptr;

    delete this->curbs;
    this->curbs = nullptr;

    delete this->fences;
    this->fences = nullptr;

    delete this->outerGeometry;
    this->outerGeometry = nullptr;

    delete this->citySky;
    this->citySky = nullptr;

    std::cout << "Destroyed Cityscape" << std::endl;
}

void Cityscape::update(const float dt)
{
}

void Cityscape::render(const glm::mat4 &mProj, const glm::mat4 &mView)
{

    this->citySky->render(mProj, mView);

    for (auto building : this->buildings)
    {
        building->render(mProj, mView);
    }

    this->signposts->render(mProj, mView);

    this->roads->render(mProj, mView);

    this->curbs->render(mProj, mView);

    this->fences->render(mProj, mView);

    this->outerGeometry->render(mProj, mView);
}

void Cityscape::regenerateCity()
{
    // CENTRE ALWAYS GENERATED FIRST
    for (int i = 1; i < this->buildings.size(); i++)
    {
        this->buildings.at(i)->regenerateBuilding();
    }
}

void Cityscape::generateCity()
{

    std::cout << "Creating Cityscape" << std::endl;
    this->roads->addTexture("TechFlat3Alt.png", 0);
    this->curbs->addTexture("TechBar2_NP.png", 0);
    this->fences->addTexture("IronFenceTop1.png", 0);

    // CENTRE ALWAYS GENERATED FIRST
    // Centre
    this->generateCentre();

    // First Quarter
    for (int i = 0; i < QUARTER_LENGTH * QUARTER_LENGTH; i++)
    {
        const int row = -(i / QUARTER_LENGTH) - 1;
        const int col = -(i % QUARTER_LENGTH) - 1;
        const float xPosition = col * (BUILDING_PLOT_SIZE + ROAD_SIZE);
        const float zPosition = row * (BUILDING_PLOT_SIZE + ROAD_SIZE);

        this->generateBlock(xPosition, zPosition);
    }

    // Second Quarter
    for (int i = 0; i < QUARTER_LENGTH * QUARTER_LENGTH; i++)
    {
        const int row = -(i / QUARTER_LENGTH) - 1;
        const int col = (i % QUARTER_LENGTH) + 1;

        const float xPosition = col * (BUILDING_PLOT_SIZE + ROAD_SIZE);
        const float zPosition = row * (BUILDING_PLOT_SIZE + ROAD_SIZE);

        this->generateBlock(xPosition, zPosition);
    }

    // Third Quarter
    for (int i = 0; i < QUARTER_LENGTH * QUARTER_LENGTH; i++)
    {
        const int row = (i / QUARTER_LENGTH) + 1;
        const int col = (i % QUARTER_LENGTH) + 1;

        const float xPosition = col * (BUILDING_PLOT_SIZE + ROAD_SIZE);
        const float zPosition = row * (BUILDING_PLOT_SIZE + ROAD_SIZE);

        this->generateBlock(xPosition, zPosition);
    }

    // Fourth Quarter
    for (int i = 0; i < QUARTER_LENGTH * QUARTER_LENGTH; i++)
    {
        const int row = (i / QUARTER_LENGTH) + 1;
        const int col = -(i % QUARTER_LENGTH) - 1;

        const float xPosition = col * (BUILDING_PLOT_SIZE + ROAD_SIZE);
        const float zPosition = row * (BUILDING_PLOT_SIZE + ROAD_SIZE);

        this->generateBlock(xPosition, zPosition);
    }

    // 1-2 Lane
    for (int i = 0; i < QUARTER_LENGTH; i++)
    {
        const int row = -(i % QUARTER_LENGTH) - 1;
        const int col = 0;

        const float xPosition = col * (BUILDING_PLOT_SIZE + ROAD_SIZE);
        const float zPosition = row * (BUILDING_PLOT_SIZE + ROAD_SIZE);

        this->generateBlock(xPosition, zPosition);
    }

    // 2-3 Lane
    for (int i = 0; i < QUARTER_LENGTH; i++)
    {
        const int row = 0;
        const int col = (i % QUARTER_LENGTH) + 1;

        const float xPosition = col * (BUILDING_PLOT_SIZE + ROAD_SIZE);
        const float zPosition = row * (BUILDING_PLOT_SIZE + ROAD_SIZE);

        this->generateBlock(xPosition, zPosition);
    }

    // 3/4 Lane
    for (int i = 0; i < QUARTER_LENGTH; i++)
    {
        const int row = (i % QUARTER_LENGTH) + 1;
        const int col = 0;

        const float xPosition = col * (BUILDING_PLOT_SIZE + ROAD_SIZE);
        const float zPosition = row * (BUILDING_PLOT_SIZE + ROAD_SIZE);

        this->generateBlock(xPosition, zPosition);
    }

    // 4-1 Lane
    for (int i = 0; i < QUARTER_LENGTH; i++)
    {
        const int row = 0;
        const int col = -(i % QUARTER_LENGTH) - 1;

        const float xPosition = col * (BUILDING_PLOT_SIZE + ROAD_SIZE);
        const float zPosition = row * (BUILDING_PLOT_SIZE + ROAD_SIZE);

        this->generateBlock(xPosition, zPosition);
    }

    // Generate Signposts
    this->generateSignposts();

    // Generate Edge Roads
    this->roads->addFlat(GRID_SIZE, static_cast<float>(ROAD_SIZE / 2.0f), glm::vec3(0.0f - static_cast<float>(GRID_SIZE / 2.0f) - static_cast<float>(ROAD_SIZE / 4.0f), 0.0f - CURB_HEIGHT, 0.0f), 90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
    this->roads->addFlat(GRID_SIZE, static_cast<float>(ROAD_SIZE / 2.0f), glm::vec3(0.0f + static_cast<float>(GRID_SIZE / 2.0f) + static_cast<float>(ROAD_SIZE / 4.0f), 0.0f - CURB_HEIGHT, 0.0f), 90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
    this->roads->addFlat(static_cast<float>(ROAD_SIZE / 2.0f), GRID_SIZE, glm::vec3(0.0f, 0.0f - CURB_HEIGHT, 0.0f + static_cast<float>(GRID_SIZE / 2.0f) + static_cast<float>(ROAD_SIZE / 4.0f)), 90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
    this->roads->addFlat(static_cast<float>(ROAD_SIZE / 2.0f), GRID_SIZE, glm::vec3(0.0f, 0.0f - CURB_HEIGHT, 0.0f - static_cast<float>(GRID_SIZE / 2.0f) - static_cast<float>(ROAD_SIZE / 4.0f)), 90.0f, glm::vec3(0.0f, 0.0f, 1.0f));

    this->roads->addFlat(static_cast<float>(ROAD_SIZE / 2.0f), static_cast<float>(ROAD_SIZE / 2.0f), glm::vec3(0.0f - static_cast<float>(GRID_SIZE / 2.0f) - static_cast<float>(ROAD_SIZE / 4.0f), 0.0f - CURB_HEIGHT, 0.0f - static_cast<float>(GRID_SIZE / 2.0f) - static_cast<float>(ROAD_SIZE / 4.0f)), 90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
    this->roads->addFlat(static_cast<float>(ROAD_SIZE / 2.0f), static_cast<float>(ROAD_SIZE / 2.0f), glm::vec3(0.0f - static_cast<float>(GRID_SIZE / 2.0f) - static_cast<float>(ROAD_SIZE / 4.0f), 0.0f - CURB_HEIGHT, 0.0f + static_cast<float>(GRID_SIZE / 2.0f) + static_cast<float>(ROAD_SIZE / 4.0f)), 90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
    this->roads->addFlat(static_cast<float>(ROAD_SIZE / 2.0f), static_cast<float>(ROAD_SIZE / 2.0f), glm::vec3(0.0f + static_cast<float>(GRID_SIZE / 2.0f) + static_cast<float>(ROAD_SIZE / 4.0f), 0.0f - CURB_HEIGHT, 0.0f - static_cast<float>(GRID_SIZE / 2.0f) - static_cast<float>(ROAD_SIZE / 4.0f)), 90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
    this->roads->addFlat(static_cast<float>(ROAD_SIZE / 2.0f), static_cast<float>(ROAD_SIZE / 2.0f), glm::vec3(0.0f + static_cast<float>(GRID_SIZE / 2.0f) + static_cast<float>(ROAD_SIZE / 4.0f), 0.0f - CURB_HEIGHT, 0.0f + static_cast<float>(GRID_SIZE / 2.0f) + static_cast<float>(ROAD_SIZE / 4.0f)), 90.0f, glm::vec3(0.0f, 0.0f, 1.0f));

    this->worldLength = GRID_LENGTH + ROAD_SIZE;

    // Generate Edge Curbs
    this->curbs->addFlatTextureFitHeight(CITY_SIZE, CURB_HEIGHT, glm::vec3(0.0f - static_cast<float>(CITY_SIZE / 2.0f), -static_cast<float>(CURB_HEIGHT / 2.0f), 0.0f), 00.0f, glm::vec3(0.0f, 0.0f, 1.0f));
    this->curbs->addFlatTextureFitHeight(CITY_SIZE, CURB_HEIGHT, glm::vec3(0.0f + static_cast<float>(CITY_SIZE / 2.0f), -static_cast<float>(CURB_HEIGHT / 2.0f), 0.0f), 00.0f, glm::vec3(0.0f, 0.0f, 1.0f));
    this->curbs->addFlatTextureFitHeight(CITY_SIZE, CURB_HEIGHT, glm::vec3(0.0f, -static_cast<float>(CURB_HEIGHT / 2.0f), 0.0f - static_cast<float>(CITY_SIZE / 2.0f)), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->curbs->addFlatTextureFitHeight(CITY_SIZE, CURB_HEIGHT, glm::vec3(0.0f, -static_cast<float>(CURB_HEIGHT / 2.0f), 0.0f + static_cast<float>(CITY_SIZE / 2.0f)), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));

    // Generate Outer Geometry
    this->generateOuterGeometry();
}

void Cityscape::generateCentre()
{
    const float xPosition = 0.0f;
    const float zPosition = 0.0f;
    // Generate Buildings
    this->buildings.push_back(new Building());

    // Generate Roads
    this->roads->addFlat(BUILDING_PLOT_SIZE, static_cast<float>(ROAD_SIZE / 2.0f), glm::vec3(xPosition - static_cast<float>(BUILDING_PLOT_SIZE / 2.0f) - static_cast<float>(ROAD_SIZE / 4.0f), 0.0f - CURB_HEIGHT, zPosition), 90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
    this->roads->addFlat(BUILDING_PLOT_SIZE, static_cast<float>(ROAD_SIZE / 2.0f), glm::vec3(xPosition + static_cast<float>(BUILDING_PLOT_SIZE / 2.0f) + static_cast<float>(ROAD_SIZE / 4.0f), 0.0f - CURB_HEIGHT, zPosition), 90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
    this->roads->addFlat(static_cast<float>(ROAD_SIZE / 2.0f), BUILDING_PLOT_SIZE, glm::vec3(xPosition, 0.0f - CURB_HEIGHT, zPosition - static_cast<float>(BUILDING_PLOT_SIZE / 2.0f) - static_cast<float>(ROAD_SIZE / 4.0f)), 90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
    this->roads->addFlat(static_cast<float>(ROAD_SIZE / 2.0f), BUILDING_PLOT_SIZE, glm::vec3(xPosition, 0.0f - CURB_HEIGHT, zPosition + static_cast<float>(BUILDING_PLOT_SIZE / 2.0f) + static_cast<float>(ROAD_SIZE / 4.0f)), 90.0f, glm::vec3(0.0f, 0.0f, 1.0f));

    // Generate Intersections
    this->roads->addFlat(static_cast<float>(ROAD_SIZE / 2.0f), static_cast<float>(ROAD_SIZE / 2.0f), glm::vec3(xPosition - static_cast<float>(BUILDING_PLOT_SIZE / 2.0f) - static_cast<float>(ROAD_SIZE / 4.0f), 0.0f - CURB_HEIGHT, zPosition - static_cast<float>((BUILDING_PLOT_SIZE) / 2.0f) - static_cast<float>(ROAD_SIZE / 4.0f)), 90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
    this->roads->addFlat(static_cast<float>(ROAD_SIZE / 2.0f), static_cast<float>(ROAD_SIZE / 2.0f), glm::vec3(xPosition - static_cast<float>(BUILDING_PLOT_SIZE / 2.0f) - static_cast<float>(ROAD_SIZE / 4.0f), 0.0f - CURB_HEIGHT, zPosition + static_cast<float>((BUILDING_PLOT_SIZE) / 2.0f) + static_cast<float>(ROAD_SIZE / 4.0f)), 90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
    this->roads->addFlat(static_cast<float>(ROAD_SIZE / 2.0f), static_cast<float>(ROAD_SIZE / 2.0f), glm::vec3(xPosition + static_cast<float>(BUILDING_PLOT_SIZE / 2.0f) + static_cast<float>(ROAD_SIZE / 4.0f), 0.0f - CURB_HEIGHT, zPosition - static_cast<float>(BUILDING_PLOT_SIZE / 2.0f) - static_cast<float>(ROAD_SIZE / 4.0f)), 90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
    this->roads->addFlat(static_cast<float>(ROAD_SIZE / 2.0f), static_cast<float>(ROAD_SIZE / 2.0f), glm::vec3(xPosition + static_cast<float>(BUILDING_PLOT_SIZE / 2.0f) + static_cast<float>(ROAD_SIZE / 4.0f), 0.0f - CURB_HEIGHT, zPosition + static_cast<float>(BUILDING_PLOT_SIZE / 2.0f) + static_cast<float>(ROAD_SIZE / 4.0f)), 90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
}

void Cityscape::generateBlock(const float xPosition, const float zPosition)
{
    // Generate Buildings
    this->buildings.push_back(new Building(glm::vec3(xPosition, 0.0f, zPosition)));

    // Generate Roads
    this->roads->addFlat(BUILDING_PLOT_SIZE, static_cast<float>(ROAD_SIZE / 2.0f), glm::vec3(xPosition - static_cast<float>(BUILDING_PLOT_SIZE / 2.0f) - static_cast<float>(ROAD_SIZE / 4.0f), 0.0f - CURB_HEIGHT, zPosition), 90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
    this->roads->addFlat(BUILDING_PLOT_SIZE, static_cast<float>(ROAD_SIZE / 2.0f), glm::vec3(xPosition + static_cast<float>(BUILDING_PLOT_SIZE / 2.0f) + static_cast<float>(ROAD_SIZE / 4.0f), 0.0f - CURB_HEIGHT, zPosition), 90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
    this->roads->addFlat(static_cast<float>(ROAD_SIZE / 2.0f), BUILDING_PLOT_SIZE, glm::vec3(xPosition, 0.0f - CURB_HEIGHT, zPosition - static_cast<float>(BUILDING_PLOT_SIZE / 2.0f) - static_cast<float>(ROAD_SIZE / 4.0f)), 90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
    this->roads->addFlat(static_cast<float>(ROAD_SIZE / 2.0f), BUILDING_PLOT_SIZE, glm::vec3(xPosition, 0.0f - CURB_HEIGHT, zPosition + static_cast<float>(BUILDING_PLOT_SIZE / 2.0f) + static_cast<float>(ROAD_SIZE / 4.0f)), 90.0f, glm::vec3(0.0f, 0.0f, 1.0f));

    // Generate Intersections
    this->roads->addFlat(static_cast<float>(ROAD_SIZE / 2.0f), static_cast<float>(ROAD_SIZE / 2.0f), glm::vec3(xPosition - static_cast<float>(BUILDING_PLOT_SIZE / 2.0f) - static_cast<float>(ROAD_SIZE / 4.0f), 0.0f - CURB_HEIGHT, zPosition - static_cast<float>((BUILDING_PLOT_SIZE) / 2.0f) - static_cast<float>(ROAD_SIZE / 4.0f)), 90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
    this->roads->addFlat(static_cast<float>(ROAD_SIZE / 2.0f), static_cast<float>(ROAD_SIZE / 2.0f), glm::vec3(xPosition - static_cast<float>(BUILDING_PLOT_SIZE / 2.0f) - static_cast<float>(ROAD_SIZE / 4.0f), 0.0f - CURB_HEIGHT, zPosition + static_cast<float>((BUILDING_PLOT_SIZE) / 2.0f) + static_cast<float>(ROAD_SIZE / 4.0f)), 90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
    this->roads->addFlat(static_cast<float>(ROAD_SIZE / 2.0f), static_cast<float>(ROAD_SIZE / 2.0f), glm::vec3(xPosition + static_cast<float>(BUILDING_PLOT_SIZE / 2.0f) + static_cast<float>(ROAD_SIZE / 4.0f), 0.0f - CURB_HEIGHT, zPosition - static_cast<float>(BUILDING_PLOT_SIZE / 2.0f) - static_cast<float>(ROAD_SIZE / 4.0f)), 90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
    this->roads->addFlat(static_cast<float>(ROAD_SIZE / 2.0f), static_cast<float>(ROAD_SIZE / 2.0f), glm::vec3(xPosition + static_cast<float>(BUILDING_PLOT_SIZE / 2.0f) + static_cast<float>(ROAD_SIZE / 4.0f), 0.0f - CURB_HEIGHT, zPosition + static_cast<float>(BUILDING_PLOT_SIZE / 2.0f) + static_cast<float>(ROAD_SIZE / 4.0f)), 90.0f, glm::vec3(0.0f, 0.0f, 1.0f));

    // Generate Curbs
    this->curbs->addFlatTextureFitHeight(BUILDING_PLOT_SIZE, CURB_HEIGHT, glm::vec3(xPosition - static_cast<float>(BUILDING_PLOT_SIZE / 2.0f), -static_cast<float>(CURB_HEIGHT / 2.0f), zPosition), 00.0f, glm::vec3(0.0f, 0.0f, 1.0f));
    this->curbs->addFlatTextureFitHeight(BUILDING_PLOT_SIZE, CURB_HEIGHT, glm::vec3(xPosition + static_cast<float>(BUILDING_PLOT_SIZE / 2.0f), -static_cast<float>(CURB_HEIGHT / 2.0f), zPosition), 00.0f, glm::vec3(0.0f, 0.0f, 1.0f));
    this->curbs->addFlatTextureFitHeight(BUILDING_PLOT_SIZE, CURB_HEIGHT, glm::vec3(xPosition, -static_cast<float>(CURB_HEIGHT / 2.0f), zPosition + static_cast<float>(BUILDING_PLOT_SIZE / 2.0f)), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->curbs->addFlatTextureFitHeight(BUILDING_PLOT_SIZE, CURB_HEIGHT, glm::vec3(xPosition, -static_cast<float>(CURB_HEIGHT / 2.0f), zPosition - static_cast<float>(BUILDING_PLOT_SIZE / 2.0f)), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));

    // Generate Fences
    this->fences->addFlat(BUILDING_PLOT_SIZE, 1.0f, glm::vec3(xPosition + static_cast<float>(BUILDING_PLOT_SIZE / 2.0f), 0.5f, zPosition), 00.0f, glm::vec3(0.0f, 0.0f, 1.0f));
    this->fences->addFlat(BUILDING_PLOT_SIZE, 1.0f, glm::vec3(xPosition - static_cast<float>(BUILDING_PLOT_SIZE / 2.0f), 0.5f, zPosition), 00.0f, glm::vec3(0.0f, 0.0f, 1.0f));
    this->fences->addFlat(BUILDING_PLOT_SIZE, 1.0f, glm::vec3(xPosition, 0.5f, zPosition + static_cast<float>(BUILDING_PLOT_SIZE / 2.0f)), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->fences->addFlat(BUILDING_PLOT_SIZE, 1.0f, glm::vec3(xPosition, 0.5f, zPosition - static_cast<float>(BUILDING_PLOT_SIZE / 2.0f)), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
}

void Cityscape::generateSignposts()
{
    int signpostTexIndex = 0;
    this->signposts->addTexture("LightV1.png", signpostTexIndex);

    // Faces
    // Centre
    this->generateSignpostFace(0.0f, 0.0f);
    signpostTexIndex += 6 * 16;

    // First Quarter
    for (int i = 0; i < QUARTER_LENGTH * QUARTER_LENGTH; i++)
    {
        const int row = -(i / QUARTER_LENGTH) - 1;
        const int col = -(i % QUARTER_LENGTH) - 1;
        const float xPosition = col * (BUILDING_PLOT_SIZE + ROAD_SIZE);
        const float zPosition = row * (BUILDING_PLOT_SIZE + ROAD_SIZE);

        this->generateSignpostFace(xPosition, zPosition);
        signpostTexIndex += 6 * 16;
    }

    // Second Quarter
    for (int i = 0; i < QUARTER_LENGTH * QUARTER_LENGTH; i++)
    {
        const int row = -(i / QUARTER_LENGTH) - 1;
        const int col = (i % QUARTER_LENGTH) + 1;

        const float xPosition = col * (BUILDING_PLOT_SIZE + ROAD_SIZE);
        const float zPosition = row * (BUILDING_PLOT_SIZE + ROAD_SIZE);

        this->generateSignpostFace(xPosition, zPosition);
        signpostTexIndex += 6 * 16;
    }

    // Third Quarter
    for (int i = 0; i < QUARTER_LENGTH * QUARTER_LENGTH; i++)
    {
        const int row = (i / QUARTER_LENGTH) + 1;
        const int col = (i % QUARTER_LENGTH) + 1;

        const float xPosition = col * (BUILDING_PLOT_SIZE + ROAD_SIZE);
        const float zPosition = row * (BUILDING_PLOT_SIZE + ROAD_SIZE);

        this->generateSignpostFace(xPosition, zPosition);
        signpostTexIndex += 6 * 16;
    }

    // Fourth Quarter
    for (int i = 0; i < QUARTER_LENGTH * QUARTER_LENGTH; i++)
    {
        const int row = (i / QUARTER_LENGTH) + 1;
        const int col = -(i % QUARTER_LENGTH) - 1;

        const float xPosition = col * (BUILDING_PLOT_SIZE + ROAD_SIZE);
        const float zPosition = row * (BUILDING_PLOT_SIZE + ROAD_SIZE);

        this->generateSignpostFace(xPosition, zPosition);
        signpostTexIndex += 6 * 16;
    }

    // 1-2 Lane
    for (int i = 0; i < QUARTER_LENGTH; i++)
    {
        const int row = -(i % QUARTER_LENGTH) - 1;
        const int col = 0;

        const float xPosition = col * (BUILDING_PLOT_SIZE + ROAD_SIZE);
        const float zPosition = row * (BUILDING_PLOT_SIZE + ROAD_SIZE);

        this->generateSignpostFace(xPosition, zPosition);
        signpostTexIndex += 6 * 16;
    }

    // 2-3 Lane
    for (int i = 0; i < QUARTER_LENGTH; i++)
    {
        const int row = 0;
        const int col = (i % QUARTER_LENGTH) + 1;

        const float xPosition = col * (BUILDING_PLOT_SIZE + ROAD_SIZE);
        const float zPosition = row * (BUILDING_PLOT_SIZE + ROAD_SIZE);

        this->generateSignpostFace(xPosition, zPosition);
        signpostTexIndex += 6 * 16;
    }

    // 3-4 Lane
    for (int i = 0; i < QUARTER_LENGTH; i++)
    {
        const int row = (i % QUARTER_LENGTH) + 1;
        const int col = 0;

        const float xPosition = col * (BUILDING_PLOT_SIZE + ROAD_SIZE);
        const float zPosition = row * (BUILDING_PLOT_SIZE + ROAD_SIZE);

        this->generateSignpostFace(xPosition, zPosition);
        signpostTexIndex += 6 * 16;
    }

    // 4-1 Lane
    for (int i = 0; i < QUARTER_LENGTH; i++)
    {
        const int row = 0;
        const int col = -(i % QUARTER_LENGTH) - 1;

        const float xPosition = col * (BUILDING_PLOT_SIZE + ROAD_SIZE);
        const float zPosition = row * (BUILDING_PLOT_SIZE + ROAD_SIZE);

        this->generateSignpostFace(xPosition, zPosition);
        signpostTexIndex += 6 * 16;
    }

    // Tops
    // Centre
    this->signposts->addTexture("LightTop1.png", signpostTexIndex);
    this->generateSignpostTop(0.0f, 0.0f);
    signpostTexIndex += 6 * 8;

    // First Quarter
    for (int i = 0; i < QUARTER_LENGTH * QUARTER_LENGTH; i++)
    {
        const int row = -(i / QUARTER_LENGTH) - 1;
        const int col = -(i % QUARTER_LENGTH) - 1;
        const float xPosition = col * (BUILDING_PLOT_SIZE + ROAD_SIZE);
        const float zPosition = row * (BUILDING_PLOT_SIZE + ROAD_SIZE);

        this->generateSignpostTop(xPosition, zPosition);
        signpostTexIndex += 6 * 8;
    }

    // Second Quarter
    for (int i = 0; i < QUARTER_LENGTH * QUARTER_LENGTH; i++)
    {
        const int row = -(i / QUARTER_LENGTH) - 1;
        const int col = (i % QUARTER_LENGTH) + 1;

        const float xPosition = col * (BUILDING_PLOT_SIZE + ROAD_SIZE);
        const float zPosition = row * (BUILDING_PLOT_SIZE + ROAD_SIZE);

        this->generateSignpostTop(xPosition, zPosition);
        signpostTexIndex += 6 * 8;
    }

    // Third Quarter
    for (int i = 0; i < QUARTER_LENGTH * QUARTER_LENGTH; i++)
    {
        const int row = (i / QUARTER_LENGTH) + 1;
        const int col = (i % QUARTER_LENGTH) + 1;

        const float xPosition = col * (BUILDING_PLOT_SIZE + ROAD_SIZE);
        const float zPosition = row * (BUILDING_PLOT_SIZE + ROAD_SIZE);

        this->generateSignpostTop(xPosition, zPosition);
        signpostTexIndex += 6 * 8;
    }

    // Fourth Quarter
    for (int i = 0; i < QUARTER_LENGTH * QUARTER_LENGTH; i++)
    {
        const int row = (i / QUARTER_LENGTH) + 1;
        const int col = -(i % QUARTER_LENGTH) - 1;

        const float xPosition = col * (BUILDING_PLOT_SIZE + ROAD_SIZE);
        const float zPosition = row * (BUILDING_PLOT_SIZE + ROAD_SIZE);

        this->generateSignpostTop(xPosition, zPosition);
        signpostTexIndex += 6 * 8;
    }

    // 1-2 Lane
    for (int i = 0; i < QUARTER_LENGTH; i++)
    {
        const int row = -(i % QUARTER_LENGTH) - 1;
        const int col = 0;

        const float xPosition = col * (BUILDING_PLOT_SIZE + ROAD_SIZE);
        const float zPosition = row * (BUILDING_PLOT_SIZE + ROAD_SIZE);

        this->generateSignpostTop(xPosition, zPosition);
        signpostTexIndex += 6 * 8;
    }

    // 2-3 Lane
    for (int i = 0; i < QUARTER_LENGTH; i++)
    {
        const int row = 0;
        const int col = (i % QUARTER_LENGTH) + 1;

        const float xPosition = col * (BUILDING_PLOT_SIZE + ROAD_SIZE);
        const float zPosition = row * (BUILDING_PLOT_SIZE + ROAD_SIZE);

        this->generateSignpostTop(xPosition, zPosition);
        signpostTexIndex += 6 * 8;
    }

    // 3/4 Lane
    for (int i = 0; i < QUARTER_LENGTH; i++)
    {
        const int row = (i % QUARTER_LENGTH) + 1;
        const int col = 0;

        const float xPosition = col * (BUILDING_PLOT_SIZE + ROAD_SIZE);
        const float zPosition = row * (BUILDING_PLOT_SIZE + ROAD_SIZE);

        this->generateSignpostTop(xPosition, zPosition);
        signpostTexIndex += 6 * 8;
    }

    // 4-1 Lane
    for (int i = 0; i < QUARTER_LENGTH; i++)
    {
        const int row = 0;
        const int col = -(i % QUARTER_LENGTH) - 1;

        const float xPosition = col * (BUILDING_PLOT_SIZE + ROAD_SIZE);
        const float zPosition = row * (BUILDING_PLOT_SIZE + ROAD_SIZE);

        this->generateSignpostTop(xPosition, zPosition);
        signpostTexIndex += 6 * 8;
    }
}

void Cityscape::generateSignpostFace(const float xPosition, const float zPosition)
{
    this->signposts->addFlatTextureFit(0.125f, 1.0f, glm::vec3(xPosition - 3.5f - 0.0625f, 0.75f, -3.5f + zPosition), 00.0f, glm::vec3(0.0f, 0.0f, 1.0f));
    this->signposts->addFlatTextureFit(0.125f, 1.0f, glm::vec3(xPosition - 3.5f + 0.0625f, 0.75f, -3.5f + zPosition), 00.0f, glm::vec3(0.0f, 0.0f, 1.0f));
    this->signposts->addFlatTextureFit(0.125f, 1.0f, glm::vec3(xPosition - 3.5f, 0.75f, -3.5f + 0.0625f + zPosition), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->signposts->addFlatTextureFit(0.125f, 1.0f, glm::vec3(xPosition - 3.5f, 0.75f, -3.5f - 0.0625f + zPosition), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));

    this->signposts->addFlatTextureFit(0.125f, 1.0f, glm::vec3(xPosition - 3.5f - 0.0625f, 0.75f, 3.5f + zPosition), 00.0f, glm::vec3(0.0f, 0.0f, 1.0f));
    this->signposts->addFlatTextureFit(0.125f, 1.0f, glm::vec3(xPosition - 3.5f + 0.0625f, 0.75f, 3.5f + zPosition), 00.0f, glm::vec3(0.0f, 0.0f, 1.0f));
    this->signposts->addFlatTextureFit(0.125f, 1.0f, glm::vec3(xPosition - 3.5f, 0.75f, 3.5f + 0.0625f + zPosition), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->signposts->addFlatTextureFit(0.125f, 1.0f, glm::vec3(xPosition - 3.5f, 0.75f, 3.5f - 0.0625f + zPosition), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));

    this->signposts->addFlatTextureFit(0.125f, 1.0f, glm::vec3(xPosition + 3.5f - 0.0625f, 0.75f, -3.5f + zPosition), 00.0f, glm::vec3(0.0f, 0.0f, 1.0f));
    this->signposts->addFlatTextureFit(0.125f, 1.0f, glm::vec3(xPosition + 3.5f + 0.0625f, 0.75f, -3.5f + zPosition), 00.0f, glm::vec3(0.0f, 0.0f, 1.0f));
    this->signposts->addFlatTextureFit(0.125f, 1.0f, glm::vec3(xPosition + 3.5f, 0.75f, -3.5f + 0.0625f + zPosition), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->signposts->addFlatTextureFit(0.125f, 1.0f, glm::vec3(xPosition + 3.5f, 0.75f, -3.5f - 0.0625f + zPosition), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));

    this->signposts->addFlatTextureFit(0.125f, 1.0f, glm::vec3(xPosition + 3.5f - 0.0625f, 0.75f, 3.5f + zPosition), 00.0f, glm::vec3(0.0f, 0.0f, 1.0f));
    this->signposts->addFlatTextureFit(0.125f, 1.0f, glm::vec3(xPosition + 3.5f + 0.0625f, 0.75f, 3.5f + zPosition), 00.0f, glm::vec3(0.0f, 0.0f, 1.0f));
    this->signposts->addFlatTextureFit(0.125f, 1.0f, glm::vec3(xPosition + 3.5f, 0.75f, 3.5f + 0.0625f + zPosition), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->signposts->addFlatTextureFit(0.125f, 1.0f, glm::vec3(xPosition + 3.5f, 0.75f, 3.5f - 0.0625f + zPosition), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
}

void Cityscape::generateSignpostTop(const float xPosition, const float zPosition)
{
    this->signposts->addFlatTextureFit(0.125f, 0.125f, glm::vec3(xPosition - 3.5f, 1.25f, -3.5f + zPosition), 90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
    this->signposts->addFlatTextureFit(0.125f, 0.125f, glm::vec3(xPosition - 3.5f, 0.25f, -3.5f + zPosition), 90.0f, glm::vec3(0.0f, 0.0f, 1.0f));

    this->signposts->addFlatTextureFit(0.125f, 0.125f, glm::vec3(xPosition - 3.5f, 1.25f, 3.5f + zPosition), 90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
    this->signposts->addFlatTextureFit(0.125f, 0.125f, glm::vec3(xPosition - 3.5f, 0.25f, 3.5f + zPosition), 90.0f, glm::vec3(0.0f, 0.0f, 1.0f));

    this->signposts->addFlatTextureFit(0.125f, 0.125f, glm::vec3(xPosition + 3.5f, 1.25f, -3.5f + zPosition), 90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
    this->signposts->addFlatTextureFit(0.125f, 0.125f, glm::vec3(xPosition + 3.5f, 0.25f, -3.5f + zPosition), 90.0f, glm::vec3(0.0f, 0.0f, 1.0f));

    this->signposts->addFlatTextureFit(0.125f, 0.125f, glm::vec3(xPosition + 3.5f, 1.25f, 3.5f + zPosition), 90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
    this->signposts->addFlatTextureFit(0.125f, 0.125f, glm::vec3(xPosition + 3.5f, 0.25f, 3.5f + zPosition), 90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
}

void Cityscape::generateOuterGeometry()
{

    // Generate Outer Edge
    this->worldLength = GRID_LENGTH + ROAD_SIZE + OUTER_EDGE_SIZE;
    int outerGeometryTexIndex = 0;
    this->outerGeometry->addTexture("TechFlat5.png", outerGeometryTexIndex);

    this->outerGeometry->addFlat(CITY_SIZE, OUTER_EDGE_SIZE, glm::vec3(0.0f - static_cast<float>((CITY_SIZE + OUTER_EDGE_SIZE) / 2.0f), 0.0f, 0.0f), 90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
    this->outerGeometry->addFlat(CITY_SIZE, OUTER_EDGE_SIZE, glm::vec3(0.0f + static_cast<float>((CITY_SIZE + OUTER_EDGE_SIZE) / 2.0f), 0.0f, 0.0f), 90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
    this->outerGeometry->addFlat(OUTER_EDGE_SIZE, CITY_SIZE, glm::vec3(0.0f, 0.0f, 0.0f + static_cast<float>((CITY_SIZE + OUTER_EDGE_SIZE) / 2.0f)), 90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
    this->outerGeometry->addFlat(OUTER_EDGE_SIZE, CITY_SIZE, glm::vec3(0.0f, 0.0f, 0.0f - static_cast<float>((CITY_SIZE + OUTER_EDGE_SIZE) / 2.0f)), 90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
    outerGeometryTexIndex += 6 * 4;

    this->outerGeometry->addFlat(OUTER_EDGE_SIZE, OUTER_EDGE_SIZE, glm::vec3(0.0f - static_cast<float>((CITY_SIZE + OUTER_EDGE_SIZE) / 2.0f), 0.0f, 0.0f - static_cast<float>((CITY_SIZE + OUTER_EDGE_SIZE) / 2.0f)), 90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
    this->outerGeometry->addFlat(OUTER_EDGE_SIZE, OUTER_EDGE_SIZE, glm::vec3(0.0f - static_cast<float>((CITY_SIZE + OUTER_EDGE_SIZE) / 2.0f), 0.0f, 0.0f + static_cast<float>((CITY_SIZE + OUTER_EDGE_SIZE) / 2.0f)), 90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
    this->outerGeometry->addFlat(OUTER_EDGE_SIZE, OUTER_EDGE_SIZE, glm::vec3(0.0f + static_cast<float>((CITY_SIZE + OUTER_EDGE_SIZE) / 2.0f), 0.0f, 0.0f - static_cast<float>((CITY_SIZE + OUTER_EDGE_SIZE) / 2.0f)), 90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
    this->outerGeometry->addFlat(OUTER_EDGE_SIZE, OUTER_EDGE_SIZE, glm::vec3(0.0f + static_cast<float>((CITY_SIZE + OUTER_EDGE_SIZE) / 2.0f), 0.0f, 0.0f + static_cast<float>((CITY_SIZE + OUTER_EDGE_SIZE) / 2.0f)), 90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
    outerGeometryTexIndex += 6 * 4;

    // Generate Upper Cliff
    this->outerGeometry->addFlat(ISLAND_SIZE, UPPER_CLIFF_HEIGHT, glm::vec3(0.0f - static_cast<float>(ISLAND_SIZE / 2.0f), -static_cast<float>(UPPER_CLIFF_HEIGHT / 2.0f), 0.0f), 00.0f, glm::vec3(0.0f, 0.0f, 1.0f));
    this->outerGeometry->addFlat(ISLAND_SIZE, UPPER_CLIFF_HEIGHT, glm::vec3(0.0f + static_cast<float>(ISLAND_SIZE / 2.0f), -static_cast<float>(UPPER_CLIFF_HEIGHT / 2.0f), 0.0f), 00.0f, glm::vec3(0.0f, 0.0f, 1.0f));
    this->outerGeometry->addFlat(ISLAND_SIZE, UPPER_CLIFF_HEIGHT, glm::vec3(0.0f, -static_cast<float>(UPPER_CLIFF_HEIGHT / 2.0f), 0.0f - static_cast<float>(ISLAND_SIZE / 2.0f)), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->outerGeometry->addFlat(ISLAND_SIZE, UPPER_CLIFF_HEIGHT, glm::vec3(0.0f, -static_cast<float>(UPPER_CLIFF_HEIGHT / 2.0f), 0.0f + static_cast<float>(ISLAND_SIZE / 2.0f)), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    outerGeometryTexIndex += 6 * 4;

    // Generate Lower Cliff
    this->outerGeometry->addFlat(CLIFF_SIZE, LOWER_CLIFF_HEIGHT, glm::vec3(0.0f - static_cast<float>(ISLAND_SIZE / 2.0f) + PILLAR_SIZE, -UPPER_CLIFF_HEIGHT - static_cast<float>(LOWER_CLIFF_HEIGHT / 2.0f), 0.0f), 00.0f, glm::vec3(0.0f, 0.0f, 1.0f));
    this->outerGeometry->addFlat(CLIFF_SIZE, LOWER_CLIFF_HEIGHT, glm::vec3(0.0f + static_cast<float>(ISLAND_SIZE / 2.0f) - PILLAR_SIZE, -UPPER_CLIFF_HEIGHT - static_cast<float>(LOWER_CLIFF_HEIGHT / 2.0f), 0.0f), 00.0f, glm::vec3(0.0f, 0.0f, 1.0f));
    this->outerGeometry->addFlat(CLIFF_SIZE, LOWER_CLIFF_HEIGHT, glm::vec3(0.0f, -UPPER_CLIFF_HEIGHT - static_cast<float>(LOWER_CLIFF_HEIGHT / 2.0f), 0.0f - static_cast<float>(ISLAND_SIZE / 2.0f) + PILLAR_SIZE), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->outerGeometry->addFlat(CLIFF_SIZE, LOWER_CLIFF_HEIGHT, glm::vec3(0.0f, -UPPER_CLIFF_HEIGHT - static_cast<float>(LOWER_CLIFF_HEIGHT / 2.0f), 0.0f + static_cast<float>(ISLAND_SIZE / 2.0f) - PILLAR_SIZE), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    outerGeometryTexIndex += 6 * 4;

    // Generate Overhang
    this->outerGeometry->addFlat(ISLAND_SIZE, PILLAR_SIZE, glm::vec3(0.0f - static_cast<float>((ISLAND_SIZE - PILLAR_SIZE) / 2.0f), -UPPER_CLIFF_HEIGHT, 0.0f), 90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
    this->outerGeometry->addFlat(ISLAND_SIZE, PILLAR_SIZE, glm::vec3(0.0f + static_cast<float>((ISLAND_SIZE - PILLAR_SIZE) / 2.0f), -UPPER_CLIFF_HEIGHT, 0.0f), 90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
    this->outerGeometry->addFlat(PILLAR_SIZE, CLIFF_SIZE, glm::vec3(0.0f, -UPPER_CLIFF_HEIGHT, 0.0f + static_cast<float>((ISLAND_SIZE - PILLAR_SIZE) / 2.0f)), 90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
    this->outerGeometry->addFlat(PILLAR_SIZE, CLIFF_SIZE, glm::vec3(0.0f, -UPPER_CLIFF_HEIGHT, 0.0f - static_cast<float>((ISLAND_SIZE - PILLAR_SIZE) / 2.0f)), 90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
    outerGeometryTexIndex += 6 * 4;

    // Generate Pillars
    // Rings
    this->outerGeometry->addTexture("TechFlat2.png", outerGeometryTexIndex);
    float currentHeight = -UPPER_CLIFF_HEIGHT - static_cast<float>(RING_HEIGHT / 2.0f);

    for (int i = 0; i < NUM_RINGS; i += 1)
    {
        this->outerGeometry->addFlat(PILLAR_SIZE, RING_HEIGHT, glm::vec3(0.0f - static_cast<float>(ISLAND_SIZE / 2.0f), currentHeight, 0.0f - static_cast<float>((ISLAND_SIZE - PILLAR_SIZE) / 2.0f)), 00.0f, glm::vec3(0.0f, 0.0f, 1.0f));
        this->outerGeometry->addFlat(PILLAR_SIZE, RING_HEIGHT, glm::vec3(0.0f - (static_cast<float>(ISLAND_SIZE / 2.0f) - PILLAR_SIZE), currentHeight, 0.0f - static_cast<float>((ISLAND_SIZE - PILLAR_SIZE) / 2.0f)), 00.0f, glm::vec3(0.0f, 0.0f, 1.0f));
        this->outerGeometry->addFlat(PILLAR_SIZE, RING_HEIGHT, glm::vec3(0.0f - static_cast<float>((ISLAND_SIZE - PILLAR_SIZE) / 2.0f), currentHeight, 0.0f - static_cast<float>(ISLAND_SIZE / 2.0f)), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
        this->outerGeometry->addFlat(PILLAR_SIZE, RING_HEIGHT, glm::vec3(0.0f - static_cast<float>((ISLAND_SIZE - PILLAR_SIZE) / 2.0f), currentHeight, 0.0f - (static_cast<float>(ISLAND_SIZE / 2.0f) - PILLAR_SIZE)), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
        outerGeometryTexIndex += 6 * 4;

        this->outerGeometry->addFlat(PILLAR_SIZE, RING_HEIGHT, glm::vec3(0.0f - static_cast<float>(ISLAND_SIZE / 2.0f), currentHeight, 0.0f + static_cast<float>((ISLAND_SIZE - PILLAR_SIZE) / 2.0f)), 00.0f, glm::vec3(0.0f, 0.0f, 1.0f));
        this->outerGeometry->addFlat(PILLAR_SIZE, RING_HEIGHT, glm::vec3(0.0f - (static_cast<float>(ISLAND_SIZE / 2.0f) - PILLAR_SIZE), currentHeight, 0.0f + static_cast<float>((ISLAND_SIZE - PILLAR_SIZE) / 2.0f)), 00.0f, glm::vec3(0.0f, 0.0f, 1.0f));
        this->outerGeometry->addFlat(PILLAR_SIZE, RING_HEIGHT, glm::vec3(0.0f - static_cast<float>((ISLAND_SIZE - PILLAR_SIZE) / 2.0f), currentHeight, 0.0f + static_cast<float>(ISLAND_SIZE / 2.0f)), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
        this->outerGeometry->addFlat(PILLAR_SIZE, RING_HEIGHT, glm::vec3(0.0f - static_cast<float>((ISLAND_SIZE - PILLAR_SIZE) / 2.0f), currentHeight, 0.0f + (static_cast<float>(ISLAND_SIZE / 2.0f) - PILLAR_SIZE)), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
        outerGeometryTexIndex += 6 * 4;

        this->outerGeometry->addFlat(PILLAR_SIZE, RING_HEIGHT, glm::vec3(0.0f + static_cast<float>(ISLAND_SIZE / 2.0f), currentHeight, 0.0f - static_cast<float>((ISLAND_SIZE - PILLAR_SIZE) / 2.0f)), 00.0f, glm::vec3(0.0f, 0.0f, 1.0f));
        this->outerGeometry->addFlat(PILLAR_SIZE, RING_HEIGHT, glm::vec3(0.0f + (static_cast<float>(ISLAND_SIZE / 2.0f) - PILLAR_SIZE), currentHeight, 0.0f - static_cast<float>((ISLAND_SIZE - PILLAR_SIZE) / 2.0f)), 00.0f, glm::vec3(0.0f, 0.0f, 1.0f));
        this->outerGeometry->addFlat(PILLAR_SIZE, RING_HEIGHT, glm::vec3(0.0f + static_cast<float>((ISLAND_SIZE - PILLAR_SIZE) / 2.0f), currentHeight, 0.0f - static_cast<float>(ISLAND_SIZE / 2.0f)), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
        this->outerGeometry->addFlat(PILLAR_SIZE, RING_HEIGHT, glm::vec3(0.0f + static_cast<float>((ISLAND_SIZE - PILLAR_SIZE) / 2.0f), currentHeight, 0.0f - (static_cast<float>(ISLAND_SIZE / 2.0f) - PILLAR_SIZE)), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
        outerGeometryTexIndex += 6 * 4;

        this->outerGeometry->addFlat(PILLAR_SIZE, RING_HEIGHT, glm::vec3(0.0f + static_cast<float>(ISLAND_SIZE / 2.0f), currentHeight, 0.0f + static_cast<float>((ISLAND_SIZE - PILLAR_SIZE) / 2.0f)), 00.0f, glm::vec3(0.0f, 0.0f, 1.0f));
        this->outerGeometry->addFlat(PILLAR_SIZE, RING_HEIGHT, glm::vec3(0.0f + (static_cast<float>(ISLAND_SIZE / 2.0f) - PILLAR_SIZE), currentHeight, 0.0f + static_cast<float>((ISLAND_SIZE - PILLAR_SIZE) / 2.0f)), 00.0f, glm::vec3(0.0f, 0.0f, 1.0f));
        this->outerGeometry->addFlat(PILLAR_SIZE, RING_HEIGHT, glm::vec3(0.0f + static_cast<float>((ISLAND_SIZE - PILLAR_SIZE) / 2.0f), currentHeight, 0.0f + static_cast<float>(ISLAND_SIZE / 2.0f)), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
        this->outerGeometry->addFlat(PILLAR_SIZE, RING_HEIGHT, glm::vec3(0.0f + static_cast<float>((ISLAND_SIZE - PILLAR_SIZE) / 2.0f), currentHeight, 0.0f + (static_cast<float>(ISLAND_SIZE / 2.0f) - PILLAR_SIZE)), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
        outerGeometryTexIndex += 6 * 4;

        currentHeight -= (RING_HEIGHT + RING_GAP_HEIGHT);
    }
    // Inner Pillars
    this->outerGeometry->addFlat(INNER_PILLAR_SIZE, LOWER_CLIFF_HEIGHT, glm::vec3(0.0f - static_cast<float>((ISLAND_SIZE - PILLAR_SIZE + INNER_PILLAR_SIZE) / 2.0f), 0.0f - UPPER_CLIFF_HEIGHT - static_cast<float>(LOWER_CLIFF_HEIGHT / 2.0f), 0.0f - static_cast<float>((ISLAND_SIZE - PILLAR_SIZE) / 2.0f)), 00.0f, glm::vec3(0.0f, 0.0f, 1.0f));
    this->outerGeometry->addFlat(INNER_PILLAR_SIZE, LOWER_CLIFF_HEIGHT, glm::vec3(0.0f - static_cast<float>((ISLAND_SIZE - PILLAR_SIZE - INNER_PILLAR_SIZE) / 2.0f), 0.0f - UPPER_CLIFF_HEIGHT - static_cast<float>(LOWER_CLIFF_HEIGHT / 2.0f), 0.0f - static_cast<float>((ISLAND_SIZE - PILLAR_SIZE) / 2.0f)), 00.0f, glm::vec3(0.0f, 0.0f, 1.0f));
    this->outerGeometry->addFlat(INNER_PILLAR_SIZE, LOWER_CLIFF_HEIGHT, glm::vec3(0.0f - static_cast<float>((ISLAND_SIZE - PILLAR_SIZE) / 2.0f), 0.0f - UPPER_CLIFF_HEIGHT - static_cast<float>(LOWER_CLIFF_HEIGHT / 2.0f), 0.0f - static_cast<float>((ISLAND_SIZE - PILLAR_SIZE - INNER_PILLAR_SIZE) / 2.0f)), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->outerGeometry->addFlat(INNER_PILLAR_SIZE, LOWER_CLIFF_HEIGHT, glm::vec3(0.0f - static_cast<float>((ISLAND_SIZE - PILLAR_SIZE) / 2.0f), 0.0f - UPPER_CLIFF_HEIGHT - static_cast<float>(LOWER_CLIFF_HEIGHT / 2.0f), 0.0f - static_cast<float>((ISLAND_SIZE - PILLAR_SIZE + INNER_PILLAR_SIZE) / 2.0f)), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    outerGeometryTexIndex += 6 * 4;

    this->outerGeometry->addFlat(INNER_PILLAR_SIZE, LOWER_CLIFF_HEIGHT, glm::vec3(0.0f - static_cast<float>((ISLAND_SIZE - PILLAR_SIZE + INNER_PILLAR_SIZE) / 2.0f), 0.0f - UPPER_CLIFF_HEIGHT - static_cast<float>(LOWER_CLIFF_HEIGHT / 2.0f), 0.0f + static_cast<float>((ISLAND_SIZE - PILLAR_SIZE) / 2.0f)), 00.0f, glm::vec3(0.0f, 0.0f, 1.0f));
    this->outerGeometry->addFlat(INNER_PILLAR_SIZE, LOWER_CLIFF_HEIGHT, glm::vec3(0.0f - static_cast<float>((ISLAND_SIZE - PILLAR_SIZE - INNER_PILLAR_SIZE) / 2.0f), 0.0f - UPPER_CLIFF_HEIGHT - static_cast<float>(LOWER_CLIFF_HEIGHT / 2.0f), 0.0f + static_cast<float>((ISLAND_SIZE - PILLAR_SIZE) / 2.0f)), 00.0f, glm::vec3(0.0f, 0.0f, 1.0f));
    this->outerGeometry->addFlat(INNER_PILLAR_SIZE, LOWER_CLIFF_HEIGHT, glm::vec3(0.0f - static_cast<float>((ISLAND_SIZE - PILLAR_SIZE) / 2.0f), 0.0f - UPPER_CLIFF_HEIGHT - static_cast<float>(LOWER_CLIFF_HEIGHT / 2.0f), 0.0f + static_cast<float>((ISLAND_SIZE - PILLAR_SIZE - INNER_PILLAR_SIZE) / 2.0f)), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->outerGeometry->addFlat(INNER_PILLAR_SIZE, LOWER_CLIFF_HEIGHT, glm::vec3(0.0f - static_cast<float>((ISLAND_SIZE - PILLAR_SIZE) / 2.0f), 0.0f - UPPER_CLIFF_HEIGHT - static_cast<float>(LOWER_CLIFF_HEIGHT / 2.0f), 0.0f + static_cast<float>((ISLAND_SIZE - PILLAR_SIZE + INNER_PILLAR_SIZE) / 2.0f)), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    outerGeometryTexIndex += 6 * 4;

    this->outerGeometry->addFlat(INNER_PILLAR_SIZE, LOWER_CLIFF_HEIGHT, glm::vec3(0.0f + static_cast<float>((ISLAND_SIZE - PILLAR_SIZE + INNER_PILLAR_SIZE) / 2.0f), 0.0f - UPPER_CLIFF_HEIGHT - static_cast<float>(LOWER_CLIFF_HEIGHT / 2.0f), 0.0f - static_cast<float>((ISLAND_SIZE - PILLAR_SIZE) / 2.0f)), 00.0f, glm::vec3(0.0f, 0.0f, 1.0f));
    this->outerGeometry->addFlat(INNER_PILLAR_SIZE, LOWER_CLIFF_HEIGHT, glm::vec3(0.0f + static_cast<float>((ISLAND_SIZE - PILLAR_SIZE - INNER_PILLAR_SIZE) / 2.0f), 0.0f - UPPER_CLIFF_HEIGHT - static_cast<float>(LOWER_CLIFF_HEIGHT / 2.0f), 0.0f - static_cast<float>((ISLAND_SIZE - PILLAR_SIZE) / 2.0f)), 00.0f, glm::vec3(0.0f, 0.0f, 1.0f));
    this->outerGeometry->addFlat(INNER_PILLAR_SIZE, LOWER_CLIFF_HEIGHT, glm::vec3(0.0f + static_cast<float>((ISLAND_SIZE - PILLAR_SIZE) / 2.0f), 0.0f - UPPER_CLIFF_HEIGHT - static_cast<float>(LOWER_CLIFF_HEIGHT / 2.0f), 0.0f - static_cast<float>((ISLAND_SIZE - PILLAR_SIZE - INNER_PILLAR_SIZE) / 2.0f)), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->outerGeometry->addFlat(INNER_PILLAR_SIZE, LOWER_CLIFF_HEIGHT, glm::vec3(0.0f + static_cast<float>((ISLAND_SIZE - PILLAR_SIZE) / 2.0f), 0.0f - UPPER_CLIFF_HEIGHT - static_cast<float>(LOWER_CLIFF_HEIGHT / 2.0f), 0.0f - static_cast<float>((ISLAND_SIZE - PILLAR_SIZE + INNER_PILLAR_SIZE) / 2.0f)), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    outerGeometryTexIndex += 6 * 4;

    this->outerGeometry->addFlat(INNER_PILLAR_SIZE, LOWER_CLIFF_HEIGHT, glm::vec3(0.0f + static_cast<float>((ISLAND_SIZE - PILLAR_SIZE + INNER_PILLAR_SIZE) / 2.0f), 0.0f - UPPER_CLIFF_HEIGHT - static_cast<float>(LOWER_CLIFF_HEIGHT / 2.0f), 0.0f + static_cast<float>((ISLAND_SIZE - PILLAR_SIZE) / 2.0f)), 00.0f, glm::vec3(0.0f, 0.0f, 1.0f));
    this->outerGeometry->addFlat(INNER_PILLAR_SIZE, LOWER_CLIFF_HEIGHT, glm::vec3(0.0f + static_cast<float>((ISLAND_SIZE - PILLAR_SIZE - INNER_PILLAR_SIZE) / 2.0f), 0.0f - UPPER_CLIFF_HEIGHT - static_cast<float>(LOWER_CLIFF_HEIGHT / 2.0f), 0.0f + static_cast<float>((ISLAND_SIZE - PILLAR_SIZE) / 2.0f)), 00.0f, glm::vec3(0.0f, 0.0f, 1.0f));
    this->outerGeometry->addFlat(INNER_PILLAR_SIZE, LOWER_CLIFF_HEIGHT, glm::vec3(0.0f + static_cast<float>((ISLAND_SIZE - PILLAR_SIZE) / 2.0f), 0.0f - UPPER_CLIFF_HEIGHT - static_cast<float>(LOWER_CLIFF_HEIGHT / 2.0f), 0.0f + static_cast<float>((ISLAND_SIZE - PILLAR_SIZE - INNER_PILLAR_SIZE) / 2.0f)), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->outerGeometry->addFlat(INNER_PILLAR_SIZE, LOWER_CLIFF_HEIGHT, glm::vec3(0.0f + static_cast<float>((ISLAND_SIZE - PILLAR_SIZE) / 2.0f), 0.0f - UPPER_CLIFF_HEIGHT - static_cast<float>(LOWER_CLIFF_HEIGHT / 2.0f), 0.0f + static_cast<float>((ISLAND_SIZE - PILLAR_SIZE + INNER_PILLAR_SIZE) / 2.0f)), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    outerGeometryTexIndex += 6 * 4;

    // Generate Pillar Bases
    this->outerGeometry->addTexture("TechFlat4.png", outerGeometryTexIndex);
    this->outerGeometry->addFlat(INNER_PILLAR_SIZE, INNER_PILLAR_SIZE, glm::vec3(0.0f - static_cast<float>((ISLAND_SIZE - PILLAR_SIZE) / 2.0f), 0.0f - (UPPER_CLIFF_HEIGHT + LOWER_CLIFF_HEIGHT), 0.0f - static_cast<float>((ISLAND_SIZE - PILLAR_SIZE) / 2.0f)), 90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
    this->outerGeometry->addFlat(INNER_PILLAR_SIZE, INNER_PILLAR_SIZE, glm::vec3(0.0f - static_cast<float>((ISLAND_SIZE - PILLAR_SIZE) / 2.0f), 0.0f - (UPPER_CLIFF_HEIGHT + LOWER_CLIFF_HEIGHT), 0.0f + static_cast<float>((ISLAND_SIZE - PILLAR_SIZE) / 2.0f)), 90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
    this->outerGeometry->addFlat(INNER_PILLAR_SIZE, INNER_PILLAR_SIZE, glm::vec3(0.0f + static_cast<float>((ISLAND_SIZE - PILLAR_SIZE) / 2.0f), 0.0f - (UPPER_CLIFF_HEIGHT + LOWER_CLIFF_HEIGHT), 0.0f - static_cast<float>((ISLAND_SIZE - PILLAR_SIZE) / 2.0f)), 90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
    this->outerGeometry->addFlat(INNER_PILLAR_SIZE, INNER_PILLAR_SIZE, glm::vec3(0.0f + static_cast<float>((ISLAND_SIZE - PILLAR_SIZE) / 2.0f), 0.0f - (UPPER_CLIFF_HEIGHT + LOWER_CLIFF_HEIGHT), 0.0f + static_cast<float>((ISLAND_SIZE - PILLAR_SIZE) / 2.0f)), 90.0f, glm::vec3(0.0f, 0.0f, 1.0f));

    outerGeometryTexIndex += 6 * 4;

    // Generate Walls
    float currentWallHeight = -CLIFF_HEIGHT + static_cast<float>(WALL_HEIGHT / 2.0f);
    float currentWallGlowHeight = -CLIFF_HEIGHT + WALL_HEIGHT + static_cast<float>(WALL_GLOW_HEIGHT / 2.0f);
    float offset = 2.0f;
    float pillarSize = (NUM_WALL_GLOWS) * 4.0f;

    // this->outerGeometry->addTexture("TechWall5.png", outerGeometryTexIndex);

    // for (int i = 0; i <= NUM_WALL_GLOWS; i++)
    // {
    // Walls
    // this->outerGeometry->addFlat(this->worldLength, WALL_HEIGHT, glm::vec3(0.0f - static_cast<float>(worldLength / 2.0f) + static_cast<float>(ROAD_SIZE / 4.0f), currentWallHeight, 0.0f), 00.0f, glm::vec3(0.0f, 0.0f, 1.0f));
    // this->outerGeometry->addFlat(this->worldLength, WALL_HEIGHT, glm::vec3(0.0f + static_cast<float>(worldLength / 2.0f) + static_cast<float>(ROAD_SIZE / 4.0f), currentWallHeight, 0.0f), 00.0f, glm::vec3(0.0f, 0.0f, 1.0f));
    // this->outerGeometry->addFlat(this->worldLength, WALL_HEIGHT, glm::vec3(static_cast<float>(ROAD_SIZE / 4.0f), currentWallHeight, 0.0f - static_cast<float>(worldLength / 2.0f)), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    // this->outerGeometry->addFlat(this->worldLength, WALL_HEIGHT, glm::vec3(static_cast<float>(ROAD_SIZE / 4.0f), currentWallHeight, 0.0f + static_cast<float>(worldLength / 2.0f)), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    // outerGeometryTexIndex += 6 * 4;

    // Corner Pillars
    //         this->outerGeometry->addFlat(pillarSize, WALL_HEIGHT, glm::vec3(0.0f - static_cast<float>(worldLength / 2.0f) + static_cast<float>(ROAD_SIZE / 4.0f) + pillarSize, currentWallHeight, 0.0f - static_cast<float>((worldLength - pillarSize) / 2.0f)), 00.0f, glm::vec3(0.0f, 0.0f, 1.0f));
    //         this->outerGeometry->addFlat(pillarSize, WALL_HEIGHT, glm::vec3(-static_cast<float>((worldLength - pillarSize) / 2.0f) + static_cast<float>(ROAD_SIZE / 4.0f), currentWallHeight, 0.0f - static_cast<float>(worldLength / 2.0f) + pillarSize), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    //         this->outerGeometry->addFlat(pillarSize, WALL_HEIGHT, glm::vec3(0.0f - static_cast<float>(worldLength / 2.0f) + static_cast<float>(ROAD_SIZE / 4.0f) + pillarSize, currentWallHeight, static_cast<float>((worldLength - pillarSize) / 2.0f)), 00.0f, glm::vec3(0.0f, 0.0f, 1.0f));
    //         this->outerGeometry->addFlat(pillarSize, WALL_HEIGHT, glm::vec3(-static_cast<float>((worldLength - pillarSize) / 2.0f) + static_cast<float>(ROAD_SIZE / 4.0f), currentWallHeight, static_cast<float>(worldLength / 2.0f) - pillarSize), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    //
    //         this->outerGeometry->addFlat(pillarSize, WALL_HEIGHT, glm::vec3(static_cast<float>(worldLength / 2.0f) - pillarSize + static_cast<float>(ROAD_SIZE / 4.0f), currentWallHeight, 0.0f - static_cast<float>((worldLength - pillarSize) / 2.0f)), 00.0f, glm::vec3(0.0f, 0.0f, 1.0f));
    //         this->outerGeometry->addFlat(pillarSize, WALL_HEIGHT, glm::vec3(static_cast<float>((worldLength - pillarSize) / 2.0f) + static_cast<float>(ROAD_SIZE / 4.0f), currentWallHeight, 0.0f - static_cast<float>(worldLength / 2.0f) + pillarSize), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    //         this->outerGeometry->addFlat(pillarSize, WALL_HEIGHT, glm::vec3(static_cast<float>(worldLength / 2.0f) - pillarSize + static_cast<float>(ROAD_SIZE / 4.0f), currentWallHeight, static_cast<float>((worldLength - pillarSize) / 2.0f)), 00.0f, glm::vec3(0.0f, 0.0f, 1.0f));
    //         this->outerGeometry->addFlat(pillarSize, WALL_HEIGHT, glm::vec3(static_cast<float>((worldLength - pillarSize) / 2.0f) + static_cast<float>(ROAD_SIZE / 4.0f), currentWallHeight, static_cast<float>(worldLength / 2.0f) - pillarSize), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    //         pillarSize -= offset;
    //         outerGeometryTexIndex += 6 * 8;
    //         currentWallHeight += WALL_HEIGHT + WALL_GLOW_HEIGHT;
    // }
    // currentWallHeight -= (static_cast<float>(WALL_HEIGHT / 2.0f) + WALL_GLOW_HEIGHT);
    // this->outerGeometry->addFlat(this->worldLength, this->worldLength, glm::vec3(static_cast<float>(ROAD_SIZE / 4.0f), currentWallHeight, 0.0f), 90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
    // outerGeometryTexIndex += 6;

    //     this->outerGeometry->addTexture("GlowYellow1.png", outerGeometryTexIndex);
    //     pillarSize = (NUM_WALL_GLOWS) * 4.0f;
    //     for (int i = 0; i < NUM_WALL_GLOWS; i++)
    //     {
    //         // Wall Glows
    //         this->outerGeometry->addFlat(this->worldLength, WALL_GLOW_HEIGHT, glm::vec3(0.0f - static_cast<float>(worldLength / 2.0f) + static_cast<float>(ROAD_SIZE / 4.0f), currentWallGlowHeight, 0.0f), 00.0f, glm::vec3(0.0f, 0.0f, 1.0f));
    //         this->outerGeometry->addFlat(this->worldLength, WALL_GLOW_HEIGHT, glm::vec3(0.0f + static_cast<float>(worldLength / 2.0f) + static_cast<float>(ROAD_SIZE / 4.0f), currentWallGlowHeight, 0.0f), 00.0f, glm::vec3(0.0f, 0.0f, 1.0f));
    //         this->outerGeometry->addFlat(this->worldLength, WALL_GLOW_HEIGHT, glm::vec3(static_cast<float>(ROAD_SIZE / 4.0f), currentWallGlowHeight, 0.0f - static_cast<float>(worldLength / 2.0f)), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    //         this->outerGeometry->addFlat(this->worldLength, WALL_GLOW_HEIGHT, glm::vec3(static_cast<float>(ROAD_SIZE / 4.0f), currentWallGlowHeight, 0.0f + static_cast<float>(worldLength / 2.0f)), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    //         outerGeometryTexIndex += 6 * 4;
    //
    //         // Corner Pillars
    //         this->outerGeometry->addFlat(pillarSize, WALL_GLOW_HEIGHT, glm::vec3(0.0f - static_cast<float>(worldLength / 2.0f) + pillarSize + static_cast<float>(ROAD_SIZE / 4.0f), currentWallGlowHeight, 0.0f - static_cast<float>((worldLength - pillarSize) / 2.0f)), 00.0f, glm::vec3(0.0f, 0.0f, 1.0f));
    //         this->outerGeometry->addFlat(pillarSize, WALL_GLOW_HEIGHT, glm::vec3(0.0f - static_cast<float>((worldLength - pillarSize) / 2.0f) + static_cast<float>(ROAD_SIZE / 4.0f), currentWallGlowHeight, 0.0f - static_cast<float>(worldLength / 2.0f) + pillarSize), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    //         this->outerGeometry->addFlat(pillarSize, WALL_GLOW_HEIGHT, glm::vec3(0.0f - static_cast<float>(worldLength / 2.0f) + pillarSize + static_cast<float>(ROAD_SIZE / 4.0f), currentWallGlowHeight, static_cast<float>((worldLength - pillarSize) / 2.0f)), 00.0f, glm::vec3(0.0f, 0.0f, 1.0f));
    //         this->outerGeometry->addFlat(pillarSize, WALL_GLOW_HEIGHT, glm::vec3(-static_cast<float>((worldLength - pillarSize) / 2.0f) + static_cast<float>(ROAD_SIZE / 4.0f), currentWallGlowHeight, static_cast<float>(worldLength / 2.0f) - pillarSize), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    //         this->outerGeometry->addFlat(pillarSize, WALL_GLOW_HEIGHT, glm::vec3(static_cast<float>(worldLength / 2.0f) - pillarSize + static_cast<float>(ROAD_SIZE / 4.0f), currentWallGlowHeight, 0.0f - static_cast<float>((worldLength - pillarSize) / 2.0f)), 00.0f, glm::vec3(0.0f, 0.0f, 1.0f));
    //         this->outerGeometry->addFlat(pillarSize, WALL_GLOW_HEIGHT, glm::vec3(static_cast<float>((worldLength - pillarSize) / 2.0f) + static_cast<float>(ROAD_SIZE / 4.0f), currentWallGlowHeight, 0.0f - static_cast<float>(worldLength / 2.0f) + pillarSize), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    //         this->outerGeometry->addFlat(pillarSize, WALL_GLOW_HEIGHT, glm::vec3(static_cast<float>(worldLength / 2.0f) - pillarSize + static_cast<float>(ROAD_SIZE / 4.0f), currentWallGlowHeight, static_cast<float>((worldLength - pillarSize) / 2.0f)), 00.0f, glm::vec3(0.0f, 0.0f, 1.0f));
    //         this->outerGeometry->addFlat(pillarSize, WALL_GLOW_HEIGHT, glm::vec3(static_cast<float>((worldLength - pillarSize) / 2.0f) + static_cast<float>(ROAD_SIZE / 4.0f), currentWallGlowHeight, static_cast<float>(worldLength / 2.0f) - pillarSize), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    //
    //         outerGeometryTexIndex += 6 * 8;
    //         pillarSize -= offset;
    //         currentWallGlowHeight += WALL_HEIGHT + WALL_GLOW_HEIGHT;
    //     }
}