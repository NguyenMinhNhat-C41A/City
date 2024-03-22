#include "building.h"

Building::Building() : BUILDING_COORDS(glm::vec3(0.0f))
{
    this->buildingFlats = new Flats();
    this->buildingFlats->beginConstructingVertices();
    this->generateCentreBuilding();
    this->buildingFlats->endConstructingVertices();
    this->buildingFlats->endInit();
}

Building::Building(const glm::vec3 coords) : BUILDING_COORDS(coords)
{
    const int buildingType = RandomNumberGenerator::getRandomNumber(1, 3);
    this->buildingFlats = new Flats();
    this->buildingFlats->beginConstructingVertices();
    switch (buildingType)
    {
    case 1:
        this->generateTypeOneBuilding(BUILDING_COORDS);
        break;
    case 2:
        this->generateTypeTwoBuilding(BUILDING_COORDS);
        break;
    case 3:
        this->generateTypeThreeBuilding(BUILDING_COORDS);
        break;
    default:
        this->generateTypeOneBuilding(BUILDING_COORDS);
        break;
    }

    this->buildingFlats->endConstructingVertices();
    this->buildingFlats->endInit();
}

Building::~Building()
{
}

void Building::update(const float dt)
{
}

void Building::render(const glm::mat4 &mProj, const glm::mat4 &mView)
{
    this->buildingFlats->render(mProj, mView);
}

void Building::regenerateBuilding()
{
    delete this->buildingFlats;
    this->buildingFlats = nullptr;

    const int buildingType = RandomNumberGenerator::getRandomNumber(1, 3);

    this->buildingFlats = new Flats();
    this->buildingFlats->beginConstructingVertices();
    switch (buildingType)
    {
    case 1:
        this->generateTypeOneBuilding(BUILDING_COORDS);
        break;
    case 2:
        this->generateTypeTwoBuilding(BUILDING_COORDS);
        break;
    case 3:
        this->generateTypeThreeBuilding(BUILDING_COORDS);
        break;
    default:
        this->generateTypeOneBuilding(BUILDING_COORDS);
        break;
    }

    this->buildingFlats->endConstructingVertices();
    this->buildingFlats->endInit();
}

void Building::generateCentreBuilding()
{
    // Data
    int flatTexIndex = 0;
    const float curbHeight = 0.125f;
    const float smallestSquareSize = 0.0f;
    const float largestSquareSize = 8.0f;
    const float squareSizeOffset = 1.0f;
    const float squareHeight = 0.125f;
    const float squaresGap = 1.0f;
    const int numSquares = static_cast<int>((largestSquareSize - smallestSquareSize) / squareSizeOffset);

    float currentSquareSize = largestSquareSize;
    float currentHeight = 0.0f;

    this->buildingFlats->addTexture("GlowLineYellow1.png", flatTexIndex);
    currentHeight -= (curbHeight + static_cast<float>(squareHeight / 2.0f));
    for (int i = 0; i <= numSquares; i++)
    {

        this->buildingFlats->addFlatTextureFitHeight(currentSquareSize, squareHeight, glm::vec3(0.0f - static_cast<float>(currentSquareSize / 2.0f), currentHeight, 0.0f), 00.0f, glm::vec3(0.0f, 1.0f, 0.0f));
        this->buildingFlats->addFlatTextureFitHeight(currentSquareSize, squareHeight, glm::vec3(0.0f + static_cast<float>(currentSquareSize / 2.0f), currentHeight, 0.0f), 00.0f, glm::vec3(0.0f, 1.0f, 0.0f));
        this->buildingFlats->addFlatTextureFitHeight(currentSquareSize, squareHeight, glm::vec3(0.0f, currentHeight, 0.0f - static_cast<float>(currentSquareSize / 2.0f)), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
        this->buildingFlats->addFlatTextureFitHeight(currentSquareSize, squareHeight, glm::vec3(0.0f, currentHeight, 0.0f + static_cast<float>(currentSquareSize / 2.0f)), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
        flatTexIndex += 6 * 4;
        currentSquareSize -= squareSizeOffset;
        currentHeight -= squareHeight;
    }
}

void Building::generateTypeOneBuilding(const glm::vec3 coords)
{
    int flatTexIndex = 0;
    float currentHeight = 0.0f;

    const float baseFloors = static_cast<float>(RandomNumberGenerator::getRandomNumber(7, 10));
    const float bufferFloors = static_cast<float>(RandomNumberGenerator::getRandomNumber(2, 3));
    const float fenceFloors = 1.0f;
    std::vector<float> blockFloors;
    for (int i = 0; i < 4; i++)
    {
        float floor = static_cast<float>(RandomNumberGenerator::getRandomNumber(32, 36));
        float offset = static_cast<float>(RandomNumberGenerator::getRandomNumber(0, 1) == 1 ? 1 : -1);
        blockFloors.push_back(floor);
        blockFloors.push_back(floor + RandomNumberGenerator::getRandomNumber(4, 7) * offset);
    }

    std::vector<float> fenceHeights;

    // Begin Generate Building Plot
    this->buildingFlats->addTexture("TechFlat4.png", flatTexIndex);
    this->buildingFlats->addFlat(8, 8, glm::vec3(coords.x, coords.y, coords.z), 90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
    flatTexIndex += 6;
    // End Generate Building Plot

    // Begin Generate Base Floors
    currentHeight += static_cast<float>(baseFloors / 2.0f);

    this->buildingFlats->addTexture("TechWallGrille1.png", flatTexIndex);
    this->buildingFlats->addFlat(2.0f, baseFloors, glm::vec3(coords.x - 2.0f, coords.y + currentHeight, coords.z + 0.0f), 00.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->buildingFlats->addFlat(2.0f, baseFloors, glm::vec3(coords.x + 2.0f, coords.y + currentHeight, coords.z + 0.0f), 00.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->buildingFlats->addFlat(2.0f, baseFloors, glm::vec3(coords.x + 0.0f, coords.y + currentHeight, coords.z + 2.0f), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->buildingFlats->addFlat(2.0f, baseFloors, glm::vec3(coords.x + 0.0f, coords.y + currentHeight, coords.z - 2.0f), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    flatTexIndex += 6 * 4;

    this->buildingFlats->addTexture("TechWall1Alt.png", flatTexIndex);
    this->buildingFlats->addFlat(1.0f, baseFloors, glm::vec3(coords.x - 1.5f, coords.y + currentHeight, coords.z - 1.0f), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->buildingFlats->addFlat(1.0f, baseFloors, glm::vec3(coords.x - 1.5f, coords.y + currentHeight, coords.z + 1.0f), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->buildingFlats->addFlat(1.0f, baseFloors, glm::vec3(coords.x + 1.5f, coords.y + currentHeight, coords.z - 1.0f), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->buildingFlats->addFlat(1.0f, baseFloors, glm::vec3(coords.x + 1.5f, coords.y + currentHeight, coords.z + 1.0f), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));

    this->buildingFlats->addFlat(1.0f, baseFloors, glm::vec3(coords.x - 1.0f, coords.y + currentHeight, coords.z + 1.5f), 00.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->buildingFlats->addFlat(1.0f, baseFloors, glm::vec3(coords.x + 1.0f, coords.y + currentHeight, coords.z + 1.5f), 00.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->buildingFlats->addFlat(1.0f, baseFloors, glm::vec3(coords.x - 1.0f, coords.y + currentHeight, coords.z - 1.5f), 00.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->buildingFlats->addFlat(1.0f, baseFloors, glm::vec3(coords.x + 1.0f, coords.y + currentHeight, coords.z - 1.5f), 00.0f, glm::vec3(0.0f, 1.0f, 0.0f));

    flatTexIndex += 6 * 8;
    // End Generate Base Floors

    // Begin Generate Buffer Floor
    currentHeight += static_cast<float>(baseFloors / 2.0f) + static_cast<float>(bufferFloors / 2.0f);
    this->buildingFlats->addTexture("IronFence1_NP.png", flatTexIndex);

    this->buildingFlats->addFlat(2.0f, bufferFloors, glm::vec3(coords.x - 2.0f, coords.y + currentHeight, coords.z + 0.0f), 00.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->buildingFlats->addFlat(2.0f, bufferFloors, glm::vec3(coords.x + 2.0f, coords.y + currentHeight, coords.z + 0.0f), 00.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->buildingFlats->addFlat(2.0f, bufferFloors, glm::vec3(coords.x + 0.0f, coords.y + currentHeight, coords.z + 2.0f), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->buildingFlats->addFlat(2.0f, bufferFloors, glm::vec3(coords.x + 0.0f, coords.y + currentHeight, coords.z - 2.0f), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    flatTexIndex += 6 * 4;

    this->buildingFlats->addFlat(1.0f, bufferFloors, glm::vec3(coords.x - 1.5f, coords.y + currentHeight, coords.z - 1.0f), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->buildingFlats->addFlat(1.0f, bufferFloors, glm::vec3(coords.x - 1.5f, coords.y + currentHeight, coords.z + 1.0f), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->buildingFlats->addFlat(1.0f, bufferFloors, glm::vec3(coords.x + 1.5f, coords.y + currentHeight, coords.z - 1.0f), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->buildingFlats->addFlat(1.0f, bufferFloors, glm::vec3(coords.x + 1.5f, coords.y + currentHeight, coords.z + 1.0f), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    flatTexIndex += 6 * 4;

    this->buildingFlats->addFlat(1.0f, bufferFloors, glm::vec3(coords.x - 1.0f, coords.y + currentHeight, coords.z + 1.5f), 00.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->buildingFlats->addFlat(1.0f, bufferFloors, glm::vec3(coords.x + 1.0f, coords.y + currentHeight, coords.z + 1.5f), 00.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->buildingFlats->addFlat(1.0f, bufferFloors, glm::vec3(coords.x - 1.0f, coords.y + currentHeight, coords.z - 1.5f), 00.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->buildingFlats->addFlat(1.0f, bufferFloors, glm::vec3(coords.x + 1.0f, coords.y + currentHeight, coords.z - 1.5f), 00.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    flatTexIndex += 6 * 4;
    // End Generate Buffer Floor

    // Begin Generate Surrounding Blocks
    currentHeight += static_cast<float>(bufferFloors / 2.0f);

    this->buildingFlats->addTexture("TechGrille1_NP.png", flatTexIndex);

    this->buildingFlats->addFlat(1.0f, blockFloors.at(0), glm::vec3(coords.x - 2.0f, coords.y + currentHeight + static_cast<float>(blockFloors.at(0) / 2.0f), coords.z - 0.5f), 00.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->buildingFlats->addFlat(1.0f, blockFloors.at(0), glm::vec3(coords.x - 1.5f, coords.y + currentHeight + static_cast<float>(blockFloors.at(0) / 2.0f), coords.z - 1.0f), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->buildingFlats->addFlat(1.0f, blockFloors.at(1), glm::vec3(coords.x - 2.0f, coords.y + currentHeight + static_cast<float>(blockFloors.at(1) / 2.0f), coords.z + 0.5f), 00.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->buildingFlats->addFlat(1.0f, blockFloors.at(1), glm::vec3(coords.x - 1.5f, coords.y + currentHeight + static_cast<float>(blockFloors.at(1) / 2.0f), coords.z + 1.0f), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    flatTexIndex += 6 * 4;

    this->buildingFlats->addFlat(1.0f, blockFloors.at(2), glm::vec3(coords.x + 2.0f, coords.y + currentHeight + static_cast<float>(blockFloors.at(2) / 2.0f), coords.z - 0.5f), 00.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->buildingFlats->addFlat(1.0f, blockFloors.at(2), glm::vec3(coords.x + 1.5f, coords.y + currentHeight + static_cast<float>(blockFloors.at(2) / 2.0f), coords.z - 1.0f), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->buildingFlats->addFlat(1.0f, blockFloors.at(3), glm::vec3(coords.x + 2.0f, coords.y + currentHeight + static_cast<float>(blockFloors.at(3) / 2.0f), coords.z + 0.5f), 00.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->buildingFlats->addFlat(1.0f, blockFloors.at(3), glm::vec3(coords.x + 1.5f, coords.y + currentHeight + static_cast<float>(blockFloors.at(3) / 2.0f), coords.z + 1.0f), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    flatTexIndex += 6 * 4;

    this->buildingFlats->addFlat(1.0f, blockFloors.at(4), glm::vec3(coords.x - 0.5f, coords.y + currentHeight + static_cast<float>(blockFloors.at(4) / 2.0f), coords.z + 2.0f), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->buildingFlats->addFlat(1.0f, blockFloors.at(4), glm::vec3(coords.x - 1.0f, coords.y + currentHeight + static_cast<float>(blockFloors.at(4) / 2.0f), coords.z + 1.5f), 00.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->buildingFlats->addFlat(1.0f, blockFloors.at(5), glm::vec3(coords.x + 0.5f, coords.y + currentHeight + static_cast<float>(blockFloors.at(5) / 2.0f), coords.z + 2.0f), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->buildingFlats->addFlat(1.0f, blockFloors.at(5), glm::vec3(coords.x + 1.0f, coords.y + currentHeight + static_cast<float>(blockFloors.at(5) / 2.0f), coords.z + 1.5f), 00.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    flatTexIndex += 6 * 4;

    this->buildingFlats->addFlat(1.0f, blockFloors.at(6), glm::vec3(coords.x - 0.5f, coords.y + currentHeight + static_cast<float>(blockFloors.at(6) / 2.0f), coords.z - 2.0f), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->buildingFlats->addFlat(1.0f, blockFloors.at(6), glm::vec3(coords.x - 1.0f, coords.y + currentHeight + static_cast<float>(blockFloors.at(6) / 2.0f), coords.z - 1.5f), 00.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->buildingFlats->addFlat(1.0f, blockFloors.at(7), glm::vec3(coords.x + 0.5f, coords.y + currentHeight + static_cast<float>(blockFloors.at(7) / 2.0f), coords.z - 2.0f), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->buildingFlats->addFlat(1.0f, blockFloors.at(7), glm::vec3(coords.x + 1.0f, coords.y + currentHeight + static_cast<float>(blockFloors.at(7) / 2.0f), coords.z - 1.5f), 00.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    flatTexIndex += 6 * 4;
    std::vector<float> blocksTopHeights;
    for (int i = 0; i < blockFloors.size(); i++)
    {
        blocksTopHeights.push_back(currentHeight + blockFloors.at(i));
    }

    float higherBlockFloor = 0;
    float lowerBlockFloor = 0;
    float blockHeightDifference = 0;

    higherBlockFloor = std::max(blockFloors.at(0), blockFloors.at(1));
    lowerBlockFloor = std::min(blockFloors.at(0), blockFloors.at(1));
    blockHeightDifference = higherBlockFloor - lowerBlockFloor;
    this->buildingFlats->addFlat(1.0f, blockHeightDifference, glm::vec3(coords.x - 1.5f, coords.y + currentHeight + lowerBlockFloor + static_cast<float>(blockHeightDifference / 2.0f), coords.z + 0.0f), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));

    higherBlockFloor = std::max(blockFloors.at(2), blockFloors.at(3));
    lowerBlockFloor = std::min(blockFloors.at(2), blockFloors.at(3));
    blockHeightDifference = higherBlockFloor - lowerBlockFloor;
    this->buildingFlats->addFlat(1.0f, blockHeightDifference, glm::vec3(coords.x + 1.5f, coords.y + currentHeight + lowerBlockFloor + static_cast<float>(blockHeightDifference / 2.0f), coords.z + 0.0f), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));

    higherBlockFloor = std::max(blockFloors.at(4), blockFloors.at(5));
    lowerBlockFloor = std::min(blockFloors.at(4), blockFloors.at(5));
    blockHeightDifference = higherBlockFloor - lowerBlockFloor;
    this->buildingFlats->addFlat(1.0f, blockHeightDifference, glm::vec3(coords.x + 0.0f, coords.y + currentHeight + lowerBlockFloor + static_cast<float>(blockHeightDifference / 2.0f), coords.z + 1.5f), 00.0f, glm::vec3(0.0f, 1.0f, 0.0f));

    higherBlockFloor = std::max(blockFloors.at(6), blockFloors.at(7));
    lowerBlockFloor = std::min(blockFloors.at(6), blockFloors.at(7));
    blockHeightDifference = higherBlockFloor - lowerBlockFloor;
    this->buildingFlats->addFlat(1.0f, blockHeightDifference, glm::vec3(coords.x + 0.0f, coords.y + currentHeight + lowerBlockFloor + static_cast<float>(blockHeightDifference / 2.0f), coords.z - 1.5f), 00.0f, glm::vec3(0.0f, 1.0f, 0.0f));

    flatTexIndex += 6 * 4;
    // End Generate Surrounding Blocks

    // Begin Generate Central Tower
    float higestBlockFLoor = 0;

    for (int i = 0; i < blocksTopHeights.size(); i++)
    {
        if (higestBlockFLoor < blocksTopHeights.at(i))
        {
            higestBlockFLoor = blocksTopHeights.at(i);
        }
    }

    float higherCentralTowerFloor = 0;
    float lowerCentralTowerFloor = 0;
    float centralTowerwerHeightDifference = 0;
    float faceOneFloors = 0;
    float faceTwoFloors = 0;

    std::vector<float> centralTowersTopHeights;
    centralTowersTopHeights.push_back(higestBlockFLoor + RandomNumberGenerator::getRandomNumber(3, 6));
    centralTowersTopHeights.push_back(centralTowersTopHeights.at(centralTowersTopHeights.size() - 1) + RandomNumberGenerator::getRandomNumber(3, 6));
    centralTowersTopHeights.push_back(centralTowersTopHeights.at(centralTowersTopHeights.size() - 1) + RandomNumberGenerator::getRandomNumber(3, 6));
    centralTowersTopHeights.push_back(centralTowersTopHeights.at(centralTowersTopHeights.size() - 1) + RandomNumberGenerator::getRandomNumber(3, 6));

    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(centralTowersTopHeights.begin(), centralTowersTopHeights.end(), g);

    std::vector<float> centralTowerFloors;
    centralTowerFloors.push_back(centralTowersTopHeights.at(0) - blocksTopHeights.at(0));
    centralTowerFloors.push_back(centralTowersTopHeights.at(0) - blocksTopHeights.at(6));
    centralTowerFloors.push_back(centralTowersTopHeights.at(1) - blocksTopHeights.at(1));
    centralTowerFloors.push_back(centralTowersTopHeights.at(1) - blocksTopHeights.at(4));
    centralTowerFloors.push_back(centralTowersTopHeights.at(2) - blocksTopHeights.at(2));
    centralTowerFloors.push_back(centralTowersTopHeights.at(2) - blocksTopHeights.at(7));
    centralTowerFloors.push_back(centralTowersTopHeights.at(3) - blocksTopHeights.at(3));
    centralTowerFloors.push_back(centralTowersTopHeights.at(3) - blocksTopHeights.at(5));

    this->buildingFlats->addFlat(1.0f, centralTowerFloors.at(0), glm::vec3(coords.x - 1.0f, coords.y + blocksTopHeights.at(0) + static_cast<float>(centralTowerFloors.at(0) / 2.0f), coords.z - 0.5f), 00.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->buildingFlats->addFlat(1.0f, centralTowerFloors.at(1), glm::vec3(coords.x - 0.5f, coords.y + blocksTopHeights.at(6) + static_cast<float>(centralTowerFloors.at(1) / 2.0f), coords.z - 1.0f), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->buildingFlats->addFlat(1.0f, centralTowerFloors.at(2), glm::vec3(coords.x - 1.0f, coords.y + blocksTopHeights.at(1) + static_cast<float>(centralTowerFloors.at(2) / 2.0f), coords.z + 0.5f), 00.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->buildingFlats->addFlat(1.0f, centralTowerFloors.at(3), glm::vec3(coords.x - 0.5f, coords.y + blocksTopHeights.at(4) + static_cast<float>(centralTowerFloors.at(3) / 2.0f), coords.z + 1.0f), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    flatTexIndex += 6 * 4;

    this->buildingFlats->addFlat(1.0f, centralTowerFloors.at(4), glm::vec3(coords.x + 1.0f, coords.y + blocksTopHeights.at(2) + static_cast<float>(centralTowerFloors.at(4) / 2.0f), coords.z - 0.5f), 00.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->buildingFlats->addFlat(1.0f, centralTowerFloors.at(5), glm::vec3(coords.x + 0.5f, coords.y + blocksTopHeights.at(7) + static_cast<float>(centralTowerFloors.at(5) / 2.0f), coords.z - 1.0f), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->buildingFlats->addFlat(1.0f, centralTowerFloors.at(6), glm::vec3(coords.x + 1.0f, coords.y + blocksTopHeights.at(3) + static_cast<float>(centralTowerFloors.at(6) / 2.0f), coords.z + 0.5f), 00.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->buildingFlats->addFlat(1.0f, centralTowerFloors.at(7), glm::vec3(coords.x + 0.5f, coords.y + blocksTopHeights.at(5) + static_cast<float>(centralTowerFloors.at(7) / 2.0f), coords.z + 1.0f), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    flatTexIndex += 6 * 4;

    higherCentralTowerFloor = std::max(centralTowersTopHeights.at(0), centralTowersTopHeights.at(1));
    lowerCentralTowerFloor = std::min(centralTowersTopHeights.at(0), centralTowersTopHeights.at(1));
    centralTowerwerHeightDifference = higherCentralTowerFloor - lowerCentralTowerFloor;
    this->buildingFlats->addFlat(1.0f, centralTowerwerHeightDifference, glm::vec3(coords.x - 0.5f, coords.y + lowerCentralTowerFloor + static_cast<float>(centralTowerwerHeightDifference / 2.0f), coords.z + 0.0f), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));

    higherCentralTowerFloor = std::max(centralTowersTopHeights.at(1), centralTowersTopHeights.at(3));
    lowerCentralTowerFloor = std::min(centralTowersTopHeights.at(1), centralTowersTopHeights.at(3));
    centralTowerwerHeightDifference = higherCentralTowerFloor - lowerCentralTowerFloor;
    this->buildingFlats->addFlat(1.0f, centralTowerwerHeightDifference, glm::vec3(coords.x + 0.0f, coords.y + lowerCentralTowerFloor + static_cast<float>(centralTowerwerHeightDifference / 2.0f), coords.z + 0.5f), 00.0f, glm::vec3(0.0f, 1.0f, 0.0f));

    higherCentralTowerFloor = std::max(centralTowersTopHeights.at(3), centralTowersTopHeights.at(2));
    lowerCentralTowerFloor = std::min(centralTowersTopHeights.at(3), centralTowersTopHeights.at(2));
    centralTowerwerHeightDifference = higherCentralTowerFloor - lowerCentralTowerFloor;
    this->buildingFlats->addFlat(1.0f, centralTowerwerHeightDifference, glm::vec3(coords.x + 0.5f, coords.y + lowerCentralTowerFloor + static_cast<float>(centralTowerwerHeightDifference / 2.0f), coords.z + 0.0f), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));

    higherCentralTowerFloor = std::max(centralTowersTopHeights.at(2), centralTowersTopHeights.at(0));
    lowerCentralTowerFloor = std::min(centralTowersTopHeights.at(2), centralTowersTopHeights.at(0));
    centralTowerwerHeightDifference = higherCentralTowerFloor - lowerCentralTowerFloor;
    this->buildingFlats->addFlat(1.0f, centralTowerwerHeightDifference, glm::vec3(coords.x + 0.0f, coords.y + lowerCentralTowerFloor + static_cast<float>(centralTowerwerHeightDifference / 2.0f), coords.z - 0.5f), 00.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    flatTexIndex += 6 * 4;
    // End Generate Central Tower

    // Begin Generate Fences
    this->buildingFlats->addTexture("IronFenceTop4.png", flatTexIndex);
    this->buildingFlats->addFlat(1.0f, fenceFloors, glm::vec3(coords.x - 2.0f, coords.y + blocksTopHeights.at(0) + static_cast<float>(fenceFloors / 2.0f), coords.z - 0.5f), 00.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->buildingFlats->addFlat(1.0f, fenceFloors, glm::vec3(coords.x - 1.5f, coords.y + blocksTopHeights.at(0) + static_cast<float>(fenceFloors / 2.0f), coords.z - 1.0f), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->buildingFlats->addFlat(1.0f, fenceFloors, glm::vec3(coords.x - 2.0f, coords.y + blocksTopHeights.at(1) + static_cast<float>(fenceFloors / 2.0f), coords.z + 0.5f), 00.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->buildingFlats->addFlat(1.0f, fenceFloors, glm::vec3(coords.x - 1.5f, coords.y + blocksTopHeights.at(1) + static_cast<float>(fenceFloors / 2.0f), coords.z + 1.0f), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    flatTexIndex += 6 * 4;

    this->buildingFlats->addFlat(1.0f, fenceFloors, glm::vec3(coords.x + 2.0f, coords.y + blocksTopHeights.at(2) + static_cast<float>(fenceFloors / 2.0f), coords.z - 0.5f), 00.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->buildingFlats->addFlat(1.0f, fenceFloors, glm::vec3(coords.x + 1.5f, coords.y + blocksTopHeights.at(2) + static_cast<float>(fenceFloors / 2.0f), coords.z - 1.0f), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->buildingFlats->addFlat(1.0f, fenceFloors, glm::vec3(coords.x + 2.0f, coords.y + blocksTopHeights.at(3) + static_cast<float>(fenceFloors / 2.0f), coords.z + 0.5f), 00.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->buildingFlats->addFlat(1.0f, fenceFloors, glm::vec3(coords.x + 1.5f, coords.y + blocksTopHeights.at(3) + static_cast<float>(fenceFloors / 2.0f), coords.z + 1.0f), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    flatTexIndex += 6 * 4;

    this->buildingFlats->addFlat(1.0f, fenceFloors, glm::vec3(coords.x - 0.5f, coords.y + blocksTopHeights.at(4) + static_cast<float>(fenceFloors / 2.0f), coords.z + 2.0f), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->buildingFlats->addFlat(1.0f, fenceFloors, glm::vec3(coords.x - 1.0f, coords.y + blocksTopHeights.at(4) + static_cast<float>(fenceFloors / 2.0f), coords.z + 1.5f), 00.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->buildingFlats->addFlat(1.0f, fenceFloors, glm::vec3(coords.x + 0.5f, coords.y + blocksTopHeights.at(5) + static_cast<float>(fenceFloors / 2.0f), coords.z + 2.0f), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->buildingFlats->addFlat(1.0f, fenceFloors, glm::vec3(coords.x + 1.0f, coords.y + blocksTopHeights.at(5) + static_cast<float>(fenceFloors / 2.0f), coords.z + 1.5f), 00.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    flatTexIndex += 6 * 4;

    this->buildingFlats->addFlat(1.0f, fenceFloors, glm::vec3(coords.x - 0.5f, coords.y + blocksTopHeights.at(6) + static_cast<float>(fenceFloors / 2.0f), coords.z - 2.0f), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->buildingFlats->addFlat(1.0f, fenceFloors, glm::vec3(coords.x - 1.0f, coords.y + blocksTopHeights.at(6) + static_cast<float>(fenceFloors / 2.0f), coords.z - 1.5f), 00.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->buildingFlats->addFlat(1.0f, fenceFloors, glm::vec3(coords.x + 0.5f, coords.y + blocksTopHeights.at(7) + static_cast<float>(fenceFloors / 2.0f), coords.z - 2.0f), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->buildingFlats->addFlat(1.0f, fenceFloors, glm::vec3(coords.x + 1.0f, coords.y + blocksTopHeights.at(7) + static_cast<float>(fenceFloors / 2.0f), coords.z - 1.5f), 00.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    flatTexIndex += 6 * 4;

    this->buildingFlats->addFlat(1.0f, fenceFloors, glm::vec3(coords.x - 1.5f, coords.y + std::max(blocksTopHeights.at(0), blocksTopHeights.at(1)) + static_cast<float>(fenceFloors / 2.0f), coords.z + 0.0f), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->buildingFlats->addFlat(1.0f, fenceFloors, glm::vec3(coords.x + 1.5f, coords.y + std::max(blocksTopHeights.at(2), blocksTopHeights.at(3)) + static_cast<float>(fenceFloors / 2.0f), coords.z + 0.0f), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->buildingFlats->addFlat(1.0f, fenceFloors, glm::vec3(coords.x + 0.0f, coords.y + std::max(blocksTopHeights.at(4), blocksTopHeights.at(5)) + static_cast<float>(fenceFloors / 2.0f), coords.z + 1.5f), 00.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->buildingFlats->addFlat(1.0f, fenceFloors, glm::vec3(coords.x + 0.0f, coords.y + std::max(blocksTopHeights.at(6), blocksTopHeights.at(7)) + static_cast<float>(fenceFloors / 2.0f), coords.z - 1.5f), 00.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    flatTexIndex += 6 * 4;

    this->buildingFlats->addFlat(1.0f, fenceFloors, glm::vec3(coords.x - 1.0f, coords.y + centralTowersTopHeights.at(0) + static_cast<float>(fenceFloors / 2.0f), coords.z - 0.5f), 00.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->buildingFlats->addFlat(1.0f, fenceFloors, glm::vec3(coords.x - 0.5f, coords.y + centralTowersTopHeights.at(0) + static_cast<float>(fenceFloors / 2.0f), coords.z - 1.0f), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->buildingFlats->addFlat(1.0f, fenceFloors, glm::vec3(coords.x - 1.0f, coords.y + centralTowersTopHeights.at(1) + static_cast<float>(fenceFloors / 2.0f), coords.z + 0.5f), 00.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->buildingFlats->addFlat(1.0f, fenceFloors, glm::vec3(coords.x - 0.5f, coords.y + centralTowersTopHeights.at(1) + static_cast<float>(fenceFloors / 2.0f), coords.z + 1.0f), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->buildingFlats->addFlat(1.0f, fenceFloors, glm::vec3(coords.x + 1.0f, coords.y + centralTowersTopHeights.at(2) + static_cast<float>(fenceFloors / 2.0f), coords.z - 0.5f), 00.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->buildingFlats->addFlat(1.0f, fenceFloors, glm::vec3(coords.x + 0.5f, coords.y + centralTowersTopHeights.at(2) + static_cast<float>(fenceFloors / 2.0f), coords.z - 1.0f), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->buildingFlats->addFlat(1.0f, fenceFloors, glm::vec3(coords.x + 1.0f, coords.y + centralTowersTopHeights.at(3) + static_cast<float>(fenceFloors / 2.0f), coords.z + 0.5f), 00.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->buildingFlats->addFlat(1.0f, fenceFloors, glm::vec3(coords.x + 0.5f, coords.y + centralTowersTopHeights.at(3) + static_cast<float>(fenceFloors / 2.0f), coords.z + 1.0f), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    flatTexIndex += 6 * 8;

    this->buildingFlats->addFlat(1.0f, fenceFloors, glm::vec3(coords.x - 0.5f, coords.y + std::max(centralTowersTopHeights.at(0), centralTowersTopHeights.at(1)) + static_cast<float>(fenceFloors / 2.0f), coords.z + 0.0f), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->buildingFlats->addFlat(1.0f, fenceFloors, glm::vec3(coords.x + 0.5f, coords.y + std::max(centralTowersTopHeights.at(2), centralTowersTopHeights.at(3)) + static_cast<float>(fenceFloors / 2.0f), coords.z + 0.0f), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->buildingFlats->addFlat(1.0f, fenceFloors, glm::vec3(coords.x + 0.0f, coords.y + std::max(centralTowersTopHeights.at(1), centralTowersTopHeights.at(3)) + static_cast<float>(fenceFloors / 2.0f), coords.z + 0.5f), 00.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->buildingFlats->addFlat(1.0f, fenceFloors, glm::vec3(coords.x + 0.0f, coords.y + std::max(centralTowersTopHeights.at(0), centralTowersTopHeights.at(2)) + static_cast<float>(fenceFloors / 2.0f), coords.z - 0.5f), 00.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    flatTexIndex += 6 * 4;

    // End Generate Fences

    // Begin Generate Roofs
    this->buildingFlats->addTexture("TechGrillePattern1_NP.png", flatTexIndex);
    this->buildingFlats->addFlat(1.0f, 1.0f, glm::vec3(coords.x - 1.5f, coords.y + blocksTopHeights.at(0), coords.z - 0.5f), 90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
    this->buildingFlats->addFlat(1.0f, 1.0f, glm::vec3(coords.x - 1.5f, coords.y + blocksTopHeights.at(1), coords.z + 0.5f), 90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
    this->buildingFlats->addFlat(1.0f, 1.0f, glm::vec3(coords.x + 1.5f, coords.y + blocksTopHeights.at(2), coords.z - 0.5f), 90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
    this->buildingFlats->addFlat(1.0f, 1.0f, glm::vec3(coords.x + 1.5f, coords.y + blocksTopHeights.at(3), coords.z + 0.5f), 90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
    this->buildingFlats->addFlat(1.0f, 1.0f, glm::vec3(coords.x - 0.5f, coords.y + blocksTopHeights.at(4), coords.z + 1.5f), 90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
    this->buildingFlats->addFlat(1.0f, 1.0f, glm::vec3(coords.x + 0.5f, coords.y + blocksTopHeights.at(5), coords.z + 1.5f), 90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
    this->buildingFlats->addFlat(1.0f, 1.0f, glm::vec3(coords.x - 0.5f, coords.y + blocksTopHeights.at(6), coords.z - 1.5f), 90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
    this->buildingFlats->addFlat(1.0f, 1.0f, glm::vec3(coords.x + 0.5f, coords.y + blocksTopHeights.at(7), coords.z - 1.5f), 90.0f, glm::vec3(0.0f, 0.0f, 1.0f));

    this->buildingFlats->addFlat(1.0f, 1.0f, glm::vec3(coords.x - 0.5f, coords.y + centralTowersTopHeights.at(0), coords.z - 0.5f), 90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
    this->buildingFlats->addFlat(1.0f, 1.0f, glm::vec3(coords.x - 0.5f, coords.y + centralTowersTopHeights.at(1), coords.z + 0.5f), 90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
    this->buildingFlats->addFlat(1.0f, 1.0f, glm::vec3(coords.x + 0.5f, coords.y + centralTowersTopHeights.at(2), coords.z - 0.5f), 90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
    this->buildingFlats->addFlat(1.0f, 1.0f, glm::vec3(coords.x + 0.5f, coords.y + centralTowersTopHeights.at(3), coords.z + 0.5f), 90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
}

void Building::generateTypeTwoBuilding(const glm::vec3 coords)
{
    int flatTexIndex = 0;
    float currentHeight = 0.0f;
    float inverseCurrentHeight = 0.0f;
    float currentRoofHeight = 0.0f;

    // Begin Generate Building Plot
    this->buildingFlats->addTexture("TechFlat4.png", flatTexIndex);
    this->buildingFlats->addFlat(8, 8, glm::vec3(coords.x, coords.y, coords.z), 90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
    flatTexIndex += 6;
    // End Generate Building Plot

    // Data
    const float baseFloors = static_cast<float>(RandomNumberGenerator::getRandomNumber(4, 7));
    const float bufferFloors = static_cast<float>(RandomNumberGenerator::getRandomNumber(2, 3));
    const float upperFloors = static_cast<float>(RandomNumberGenerator::getRandomNumber(7, 9));
    const float gapSize = static_cast<float>(RandomNumberGenerator::getRandomNumber(4, 6));
    const float ringFloors = static_cast<float>(RandomNumberGenerator::getRandomNumber(7, 9));
    const float buildingHeight = (baseFloors + bufferFloors + upperFloors + gapSize) * 2.0f + ringFloors;
    const float fenceFloors = 1.0f;

    // Begin Generate Base Floors
    this->buildingFlats->addTexture("TechWallGrille1.png", flatTexIndex);
    currentHeight += static_cast<float>(baseFloors / 2.0f);
    inverseCurrentHeight += buildingHeight - static_cast<float>(baseFloors / 2.0f);

    // Outer Layer
    this->buildingFlats->addFlat(4.0f, baseFloors, glm::vec3(coords.x - 3.0f, coords.y + currentHeight, coords.z + 0.0f), 00.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->buildingFlats->addFlat(4.0f, baseFloors, glm::vec3(coords.x + 3.0f, coords.y + currentHeight, coords.z + 0.0f), 00.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->buildingFlats->addFlat(4.0f, baseFloors, glm::vec3(coords.x + 0.0f, coords.y + currentHeight, coords.z + 3.0f), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->buildingFlats->addFlat(4.0f, baseFloors, glm::vec3(coords.x + 0.0f, coords.y + currentHeight, coords.z - 3.0f), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    flatTexIndex += 6 * 4;

    this->buildingFlats->addFlat(4.0f, baseFloors, glm::vec3(coords.x - 3.0f, coords.y + inverseCurrentHeight, coords.z + 0.0f), 00.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->buildingFlats->addFlat(4.0f, baseFloors, glm::vec3(coords.x + 3.0f, coords.y + inverseCurrentHeight, coords.z + 0.0f), 00.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->buildingFlats->addFlat(4.0f, baseFloors, glm::vec3(coords.x + 0.0f, coords.y + inverseCurrentHeight, coords.z + 3.0f), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->buildingFlats->addFlat(4.0f, baseFloors, glm::vec3(coords.x + 0.0f, coords.y + inverseCurrentHeight, coords.z - 3.0f), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    flatTexIndex += 6 * 4;

    // Core
    this->buildingFlats->addFlat(2.0f, baseFloors, glm::vec3(coords.x - 1.0f, coords.y + currentHeight, coords.z + 0.0f), 00.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->buildingFlats->addFlat(2.0f, baseFloors, glm::vec3(coords.x + 1.0f, coords.y + currentHeight, coords.z + 0.0f), 00.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->buildingFlats->addFlat(2.0f, baseFloors, glm::vec3(coords.x + 0.0f, coords.y + currentHeight, coords.z - 1.0f), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->buildingFlats->addFlat(2.0f, baseFloors, glm::vec3(coords.x + 0.0f, coords.y + currentHeight, coords.z + 1.0f), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    flatTexIndex += 6 * 4;

    this->buildingFlats->addFlat(2.0f, baseFloors, glm::vec3(coords.x - 1.0f, coords.y + inverseCurrentHeight, coords.z + 0.0f), 00.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->buildingFlats->addFlat(2.0f, baseFloors, glm::vec3(coords.x + 1.0f, coords.y + inverseCurrentHeight, coords.z + 0.0f), 00.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->buildingFlats->addFlat(2.0f, baseFloors, glm::vec3(coords.x + 0.0f, coords.y + inverseCurrentHeight, coords.z - 1.0f), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->buildingFlats->addFlat(2.0f, baseFloors, glm::vec3(coords.x + 0.0f, coords.y + inverseCurrentHeight, coords.z + 1.0f), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    flatTexIndex += 6 * 4;

    this->buildingFlats->addTexture("TechWall1Alt.png", flatTexIndex);

    // Middle Layer
    this->buildingFlats->addFlat(4.0f, baseFloors, glm::vec3(coords.x + 0.0f, coords.y + currentHeight, coords.z - 2.0f), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->buildingFlats->addFlat(4.0f, baseFloors, glm::vec3(coords.x + 0.0f, coords.y + currentHeight, coords.z + 2.0f), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->buildingFlats->addFlat(4.0f, baseFloors, glm::vec3(coords.x - 2.0f, coords.y + currentHeight, coords.z + 0.0f), 00.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->buildingFlats->addFlat(4.0f, baseFloors, glm::vec3(coords.x + 2.0f, coords.y + currentHeight, coords.z + 0.0f), 00.0f, glm::vec3(0.0f, 1.0f, 0.0f));

    this->buildingFlats->addFlat(4.0f, baseFloors, glm::vec3(coords.x + 0.0f, coords.y + inverseCurrentHeight, coords.z - 2.0f), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->buildingFlats->addFlat(4.0f, baseFloors, glm::vec3(coords.x + 0.0f, coords.y + inverseCurrentHeight, coords.z + 2.0f), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->buildingFlats->addFlat(4.0f, baseFloors, glm::vec3(coords.x - 2.0f, coords.y + inverseCurrentHeight, coords.z + 0.0f), 00.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->buildingFlats->addFlat(4.0f, baseFloors, glm::vec3(coords.x + 2.0f, coords.y + inverseCurrentHeight, coords.z + 0.0f), 00.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    flatTexIndex += 6 * 8;
    // End Generate Base Floors

    // Begin Generate Buffer Floor
    this->buildingFlats->addTexture("IronFence2_NP.png", flatTexIndex);
    currentHeight += static_cast<float>(baseFloors / 2.0f) + static_cast<float>(bufferFloors / 2.0f);
    inverseCurrentHeight -= static_cast<float>(baseFloors / 2.0f) + static_cast<float>(bufferFloors / 2.0f);

    // Outer Layer
    this->buildingFlats->addFlat(4.0f, bufferFloors, glm::vec3(coords.x - 3.0f, coords.y + currentHeight, coords.z + 0.0f), 00.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->buildingFlats->addFlat(4.0f, bufferFloors, glm::vec3(coords.x + 3.0f, coords.y + currentHeight, coords.z + 0.0f), 00.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->buildingFlats->addFlat(4.0f, bufferFloors, glm::vec3(coords.x + 0.0f, coords.y + currentHeight, coords.z + 3.0f), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->buildingFlats->addFlat(4.0f, bufferFloors, glm::vec3(coords.x + 0.0f, coords.y + currentHeight, coords.z - 3.0f), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));

    this->buildingFlats->addFlat(4.0f, bufferFloors, glm::vec3(coords.x - 3.0f, coords.y + inverseCurrentHeight, coords.z + 0.0f), 00.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->buildingFlats->addFlat(4.0f, bufferFloors, glm::vec3(coords.x + 3.0f, coords.y + inverseCurrentHeight, coords.z + 0.0f), 00.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->buildingFlats->addFlat(4.0f, bufferFloors, glm::vec3(coords.x + 0.0f, coords.y + inverseCurrentHeight, coords.z + 3.0f), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->buildingFlats->addFlat(4.0f, bufferFloors, glm::vec3(coords.x + 0.0f, coords.y + inverseCurrentHeight, coords.z - 3.0f), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    flatTexIndex += 6 * 8;

    // Core
    this->buildingFlats->addFlat(2.0f, bufferFloors, glm::vec3(coords.x - 1.0f, coords.y + currentHeight, coords.z + 0.0f), 00.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->buildingFlats->addFlat(2.0f, bufferFloors, glm::vec3(coords.x + 1.0f, coords.y + currentHeight, coords.z + 0.0f), 00.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->buildingFlats->addFlat(2.0f, bufferFloors, glm::vec3(coords.x + 0.0f, coords.y + currentHeight, coords.z - 1.0f), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->buildingFlats->addFlat(2.0f, bufferFloors, glm::vec3(coords.x + 0.0f, coords.y + currentHeight, coords.z + 1.0f), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));

    this->buildingFlats->addFlat(2.0f, bufferFloors, glm::vec3(coords.x - 1.0f, coords.y + inverseCurrentHeight, coords.z + 0.0f), 00.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->buildingFlats->addFlat(2.0f, bufferFloors, glm::vec3(coords.x + 1.0f, coords.y + inverseCurrentHeight, coords.z + 0.0f), 00.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->buildingFlats->addFlat(2.0f, bufferFloors, glm::vec3(coords.x + 0.0f, coords.y + inverseCurrentHeight, coords.z - 1.0f), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->buildingFlats->addFlat(2.0f, bufferFloors, glm::vec3(coords.x + 0.0f, coords.y + inverseCurrentHeight, coords.z + 1.0f), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    flatTexIndex += 6 * 8;

    // Middle Layer
    this->buildingFlats->addFlat(4.0f, bufferFloors, glm::vec3(coords.x + 0.0f, coords.y + currentHeight, coords.z - 2.0f), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->buildingFlats->addFlat(4.0f, bufferFloors, glm::vec3(coords.x + 0.0f, coords.y + currentHeight, coords.z + 2.0f), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->buildingFlats->addFlat(4.0f, bufferFloors, glm::vec3(coords.x - 2.0f, coords.y + currentHeight, coords.z + 0.0f), 00.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->buildingFlats->addFlat(4.0f, bufferFloors, glm::vec3(coords.x + 2.0f, coords.y + currentHeight, coords.z + 0.0f), 00.0f, glm::vec3(0.0f, 1.0f, 0.0f));

    this->buildingFlats->addFlat(4.0f, bufferFloors, glm::vec3(coords.x + 0.0f, coords.y + inverseCurrentHeight, coords.z - 2.0f), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->buildingFlats->addFlat(4.0f, bufferFloors, glm::vec3(coords.x + 0.0f, coords.y + inverseCurrentHeight, coords.z + 2.0f), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->buildingFlats->addFlat(4.0f, bufferFloors, glm::vec3(coords.x - 2.0f, coords.y + inverseCurrentHeight, coords.z + 0.0f), 00.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->buildingFlats->addFlat(4.0f, bufferFloors, glm::vec3(coords.x + 2.0f, coords.y + inverseCurrentHeight, coords.z + 0.0f), 00.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    flatTexIndex += 6 * 8;
    // End Generate Buffer Floor

    // Begin Generate Upper Floors
    this->buildingFlats->addTexture("TechGrille1_NP.png", flatTexIndex);
    currentHeight += static_cast<float>(bufferFloors / 2.0f) + static_cast<float>(upperFloors / 2.0f);
    inverseCurrentHeight -= static_cast<float>(bufferFloors / 2.0f) + static_cast<float>(upperFloors / 2.0f);

    // Outer Layer
    this->buildingFlats->addFlat(4.0f, upperFloors, glm::vec3(coords.x - 3.0f, coords.y + currentHeight, coords.z + 0.0f), 00.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->buildingFlats->addFlat(4.0f, upperFloors, glm::vec3(coords.x + 3.0f, coords.y + currentHeight, coords.z + 0.0f), 00.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->buildingFlats->addFlat(4.0f, upperFloors, glm::vec3(coords.x + 0.0f, coords.y + currentHeight, coords.z + 3.0f), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->buildingFlats->addFlat(4.0f, upperFloors, glm::vec3(coords.x + 0.0f, coords.y + currentHeight, coords.z - 3.0f), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));

    this->buildingFlats->addFlat(4.0f, upperFloors, glm::vec3(coords.x - 3.0f, coords.y + inverseCurrentHeight, coords.z + 0.0f), 00.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->buildingFlats->addFlat(4.0f, upperFloors, glm::vec3(coords.x + 3.0f, coords.y + inverseCurrentHeight, coords.z + 0.0f), 00.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->buildingFlats->addFlat(4.0f, upperFloors, glm::vec3(coords.x + 0.0f, coords.y + inverseCurrentHeight, coords.z + 3.0f), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->buildingFlats->addFlat(4.0f, upperFloors, glm::vec3(coords.x + 0.0f, coords.y + inverseCurrentHeight, coords.z - 3.0f), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    flatTexIndex += 6 * 8;

    // Core
    this->buildingFlats->addFlat(2.0f, upperFloors, glm::vec3(coords.x - 1.0f, coords.y + currentHeight, coords.z + 0.0f), 00.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->buildingFlats->addFlat(2.0f, upperFloors, glm::vec3(coords.x + 1.0f, coords.y + currentHeight, coords.z + 0.0f), 00.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->buildingFlats->addFlat(2.0f, upperFloors, glm::vec3(coords.x + 0.0f, coords.y + currentHeight, coords.z - 1.0f), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->buildingFlats->addFlat(2.0f, upperFloors, glm::vec3(coords.x + 0.0f, coords.y + currentHeight, coords.z + 1.0f), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));

    this->buildingFlats->addFlat(2.0f, upperFloors, glm::vec3(coords.x - 1.0f, coords.y + inverseCurrentHeight, coords.z + 0.0f), 00.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->buildingFlats->addFlat(2.0f, upperFloors, glm::vec3(coords.x + 1.0f, coords.y + inverseCurrentHeight, coords.z + 0.0f), 00.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->buildingFlats->addFlat(2.0f, upperFloors, glm::vec3(coords.x + 0.0f, coords.y + inverseCurrentHeight, coords.z - 1.0f), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->buildingFlats->addFlat(2.0f, upperFloors, glm::vec3(coords.x + 0.0f, coords.y + inverseCurrentHeight, coords.z + 1.0f), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    flatTexIndex += 6 * 8;

    // Middle Layer
    this->buildingFlats->addFlat(4.0f, upperFloors, glm::vec3(coords.x + 0.0f, coords.y + currentHeight, coords.z - 2.0f), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->buildingFlats->addFlat(4.0f, upperFloors, glm::vec3(coords.x + 0.0f, coords.y + currentHeight, coords.z + 2.0f), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->buildingFlats->addFlat(4.0f, upperFloors, glm::vec3(coords.x - 2.0f, coords.y + currentHeight, coords.z + 0.0f), 00.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->buildingFlats->addFlat(4.0f, upperFloors, glm::vec3(coords.x + 2.0f, coords.y + currentHeight, coords.z + 0.0f), 00.0f, glm::vec3(0.0f, 1.0f, 0.0f));

    this->buildingFlats->addFlat(4.0f, upperFloors, glm::vec3(coords.x + 0.0f, coords.y + inverseCurrentHeight, coords.z - 2.0f), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->buildingFlats->addFlat(4.0f, upperFloors, glm::vec3(coords.x + 0.0f, coords.y + inverseCurrentHeight, coords.z + 2.0f), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->buildingFlats->addFlat(4.0f, upperFloors, glm::vec3(coords.x - 2.0f, coords.y + inverseCurrentHeight, coords.z + 0.0f), 00.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->buildingFlats->addFlat(4.0f, upperFloors, glm::vec3(coords.x + 2.0f, coords.y + inverseCurrentHeight, coords.z + 0.0f), 00.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    flatTexIndex += 6 * 8;

    // End Generate Upper Floors

    // Begin Generate Ring
    currentHeight += static_cast<float>(upperFloors / 2.0f) + gapSize + static_cast<float>(ringFloors / 2.0f);

    // Outer Layer
    this->buildingFlats->addFlat(4.0f, ringFloors, glm::vec3(coords.x - 3.0f, coords.y + currentHeight, coords.z + 0.0f), 00.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->buildingFlats->addFlat(4.0f, ringFloors, glm::vec3(coords.x + 3.0f, coords.y + currentHeight, coords.z + 0.0f), 00.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->buildingFlats->addFlat(4.0f, ringFloors, glm::vec3(coords.x + 0.0f, coords.y + currentHeight, coords.z + 3.0f), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->buildingFlats->addFlat(4.0f, ringFloors, glm::vec3(coords.x + 0.0f, coords.y + currentHeight, coords.z - 3.0f), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));

    // Core
    this->buildingFlats->addFlat(2.0f, ringFloors, glm::vec3(coords.x - 1.0f, coords.y + currentHeight, coords.z + 0.0f), 00.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->buildingFlats->addFlat(2.0f, ringFloors, glm::vec3(coords.x + 1.0f, coords.y + currentHeight, coords.z + 0.0f), 00.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->buildingFlats->addFlat(2.0f, ringFloors, glm::vec3(coords.x + 0.0f, coords.y + currentHeight, coords.z - 1.0f), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->buildingFlats->addFlat(2.0f, ringFloors, glm::vec3(coords.x + 0.0f, coords.y + currentHeight, coords.z + 1.0f), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    flatTexIndex += 6 * 8;

    // Middle  Layer
    this->buildingFlats->addFlat(4.0f, ringFloors, glm::vec3(coords.x + 0.0f, coords.y + currentHeight, coords.z - 2.0f), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->buildingFlats->addFlat(4.0f, ringFloors, glm::vec3(coords.x + 0.0f, coords.y + currentHeight, coords.z + 2.0f), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->buildingFlats->addFlat(4.0f, ringFloors, glm::vec3(coords.x - 2.0f, coords.y + currentHeight, coords.z + 0.0f), 00.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->buildingFlats->addFlat(4.0f, ringFloors, glm::vec3(coords.x + 2.0f, coords.y + currentHeight, coords.z + 0.0f), 00.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    flatTexIndex += 6 * 4;
    // End Generate Ring

    // Begin Generate Fences
    currentHeight = baseFloors + bufferFloors + upperFloors + static_cast<float>(fenceFloors / 2.0f);

    this->buildingFlats->addTexture("IronFenceTop2.png", flatTexIndex);

    this->buildingFlats->addFlat(4.0f, fenceFloors, glm::vec3(coords.x - 3.0f, coords.y + currentHeight, coords.z + 0.0f), 00.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->buildingFlats->addFlat(4.0f, fenceFloors, glm::vec3(coords.x + 3.0f, coords.y + currentHeight, coords.z + 0.0f), 00.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->buildingFlats->addFlat(4.0f, fenceFloors, glm::vec3(coords.x + 0.0f, coords.y + currentHeight, coords.z + 3.0f), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->buildingFlats->addFlat(4.0f, fenceFloors, glm::vec3(coords.x + 0.0f, coords.y + currentHeight, coords.z - 3.0f), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    flatTexIndex += 6 * 4;

    currentHeight += -static_cast<float>(fenceFloors / 2.0f) + gapSize + ringFloors + static_cast<float>(fenceFloors / 2.0f);

    this->buildingFlats->addFlat(4.0f, fenceFloors, glm::vec3(coords.x - 3.0f, coords.y + currentHeight, coords.z + 0.0f), 00.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->buildingFlats->addFlat(4.0f, fenceFloors, glm::vec3(coords.x + 3.0f, coords.y + currentHeight, coords.z + 0.0f), 00.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->buildingFlats->addFlat(4.0f, fenceFloors, glm::vec3(coords.x + 0.0f, coords.y + currentHeight, coords.z + 3.0f), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->buildingFlats->addFlat(4.0f, fenceFloors, glm::vec3(coords.x + 0.0f, coords.y + currentHeight, coords.z - 3.0f), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    flatTexIndex += 6 * 4;

    currentHeight += -static_cast<float>(fenceFloors / 2.0f) + gapSize + upperFloors + bufferFloors + baseFloors + static_cast<float>(fenceFloors / 2.0f);

    this->buildingFlats->addFlat(6.0f, fenceFloors, glm::vec3(coords.x - 3.0f, coords.y + currentHeight, coords.z + 0.0f), 00.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->buildingFlats->addFlat(6.0f, fenceFloors, glm::vec3(coords.x + 3.0f, coords.y + currentHeight, coords.z + 0.0f), 00.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->buildingFlats->addFlat(6.0f, fenceFloors, glm::vec3(coords.x + 0.0f, coords.y + currentHeight, coords.z + 3.0f), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->buildingFlats->addFlat(6.0f, fenceFloors, glm::vec3(coords.x + 0.0f, coords.y + currentHeight, coords.z - 3.0f), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    flatTexIndex += 6 * 4;

    inverseCurrentHeight = buildingHeight - (baseFloors + bufferFloors + upperFloors + static_cast<float>(fenceFloors / 2.0f));
    this->buildingFlats->addTexture("IronFenceTop2Flip.png", flatTexIndex);

    this->buildingFlats->addFlat(4.0f, fenceFloors, glm::vec3(coords.x - 3.0f, coords.y + inverseCurrentHeight, coords.z + 0.0f), 00.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->buildingFlats->addFlat(4.0f, fenceFloors, glm::vec3(coords.x + 3.0f, coords.y + inverseCurrentHeight, coords.z + 0.0f), 00.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->buildingFlats->addFlat(4.0f, fenceFloors, glm::vec3(coords.x + 0.0f, coords.y + inverseCurrentHeight, coords.z + 3.0f), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->buildingFlats->addFlat(4.0f, fenceFloors, glm::vec3(coords.x + 0.0f, coords.y + inverseCurrentHeight, coords.z - 3.0f), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    flatTexIndex += 6 * 4;

    inverseCurrentHeight -= -static_cast<float>(fenceFloors / 2.0f) + gapSize + ringFloors + static_cast<float>(fenceFloors / 2.0f);

    this->buildingFlats->addFlat(4.0f, fenceFloors, glm::vec3(coords.x - 3.0f, coords.y + inverseCurrentHeight, coords.z + 0.0f), 00.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->buildingFlats->addFlat(4.0f, fenceFloors, glm::vec3(coords.x + 3.0f, coords.y + inverseCurrentHeight, coords.z + 0.0f), 00.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->buildingFlats->addFlat(4.0f, fenceFloors, glm::vec3(coords.x + 0.0f, coords.y + inverseCurrentHeight, coords.z + 3.0f), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->buildingFlats->addFlat(4.0f, fenceFloors, glm::vec3(coords.x + 0.0f, coords.y + inverseCurrentHeight, coords.z - 3.0f), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    flatTexIndex += 6 * 4;
    // End Generate Fences

    // Begin Generate Pillars
    this->buildingFlats->addTexture("TechFlat2.png", flatTexIndex);

    this->buildingFlats->addFlat(1.0f, buildingHeight, glm::vec3(coords.x - 2.5f, coords.y + static_cast<float>(buildingHeight / 2.0f), coords.z - 3.0f), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->buildingFlats->addFlat(1.0f, buildingHeight, glm::vec3(coords.x - 3.0f, coords.y + static_cast<float>(buildingHeight / 2.0f), coords.z - 2.5f), 00.0f, glm::vec3(0.0f, 1.0f, 0.0f));

    this->buildingFlats->addFlat(1.0f, buildingHeight, glm::vec3(coords.x + 2.5f, coords.y + static_cast<float>(buildingHeight / 2.0f), coords.z - 3.0f), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->buildingFlats->addFlat(1.0f, buildingHeight, glm::vec3(coords.x + 3.0f, coords.y + static_cast<float>(buildingHeight / 2.0f), coords.z - 2.5f), 00.0f, glm::vec3(0.0f, 1.0f, 0.0f));

    this->buildingFlats->addFlat(1.0f, buildingHeight, glm::vec3(coords.x - 2.5f, coords.y + static_cast<float>(buildingHeight / 2.0f), coords.z + 3.0f), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->buildingFlats->addFlat(1.0f, buildingHeight, glm::vec3(coords.x - 3.0f, coords.y + static_cast<float>(buildingHeight / 2.0f), coords.z + 2.5f), 00.0f, glm::vec3(0.0f, 1.0f, 0.0f));

    this->buildingFlats->addFlat(1.0f, buildingHeight, glm::vec3(coords.x + 2.5f, coords.y + static_cast<float>(buildingHeight / 2.0f), coords.z + 3.0f), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->buildingFlats->addFlat(1.0f, buildingHeight, glm::vec3(coords.x + 3.0f, coords.y + static_cast<float>(buildingHeight / 2.0f), coords.z + 2.5f), 00.0f, glm::vec3(0.0f, 1.0f, 0.0f));

    this->buildingFlats->addFlat(1.0f, buildingHeight, glm::vec3(coords.x - 2.5f, coords.y + static_cast<float>(buildingHeight / 2.0f), coords.z - 2.0f), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->buildingFlats->addFlat(1.0f, buildingHeight, glm::vec3(coords.x - 2.0f, coords.y + static_cast<float>(buildingHeight / 2.0f), coords.z - 2.5f), 00.0f, glm::vec3(0.0f, 1.0f, 0.0f));

    this->buildingFlats->addFlat(1.0f, buildingHeight, glm::vec3(coords.x + 2.5f, coords.y + static_cast<float>(buildingHeight / 2.0f), coords.z - 2.0f), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->buildingFlats->addFlat(1.0f, buildingHeight, glm::vec3(coords.x + 2.0f, coords.y + static_cast<float>(buildingHeight / 2.0f), coords.z - 2.5f), 00.0f, glm::vec3(0.0f, 1.0f, 0.0f));

    this->buildingFlats->addFlat(1.0f, buildingHeight, glm::vec3(coords.x - 2.5f, coords.y + static_cast<float>(buildingHeight / 2.0f), coords.z + 2.0f), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->buildingFlats->addFlat(1.0f, buildingHeight, glm::vec3(coords.x - 2.0f, coords.y + static_cast<float>(buildingHeight / 2.0f), coords.z + 2.5f), 00.0f, glm::vec3(0.0f, 1.0f, 0.0f));

    this->buildingFlats->addFlat(1.0f, buildingHeight, glm::vec3(coords.x + 2.5f, coords.y + static_cast<float>(buildingHeight / 2.0f), coords.z + 2.0f), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->buildingFlats->addFlat(1.0f, buildingHeight, glm::vec3(coords.x + 2.0f, coords.y + static_cast<float>(buildingHeight / 2.0f), coords.z + 2.5f), 00.0f, glm::vec3(0.0f, 1.0f, 0.0f));

    flatTexIndex += 6 * 16;
    // End Generate Pillars

    // Begin Generate Roofs
    currentRoofHeight += baseFloors + bufferFloors + upperFloors;

    this->buildingFlats->addTexture("TechGrillePattern1_NP.png", flatTexIndex);

    this->buildingFlats->addFlat(4.0f, 1.0f, glm::vec3(coords.x - 2.5f, coords.y + currentRoofHeight, coords.z + 0.0f), 90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
    this->buildingFlats->addFlat(4.0f, 1.0f, glm::vec3(coords.x + 2.5f, coords.y + currentRoofHeight, coords.z + 0.0f), 90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
    this->buildingFlats->addFlat(1.0f, 4.0f, glm::vec3(coords.x + 0.0f, coords.y + currentRoofHeight, coords.z + 2.5f), 90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
    this->buildingFlats->addFlat(1.0f, 4.0f, glm::vec3(coords.x + 0.0f, coords.y + currentRoofHeight, coords.z - 2.5f), 90.0f, glm::vec3(0.0f, 0.0f, 1.0f));

    this->buildingFlats->addFlat(2.0f, 2.0f, glm::vec3(coords.x + 0.0f, coords.y + currentRoofHeight, coords.z + 0.0f), 90.0f, glm::vec3(0.0f, 0.0f, 1.0f));

    currentRoofHeight += gapSize;

    this->buildingFlats->addFlat(4.0f, 1.0f, glm::vec3(coords.x - 2.5f, coords.y + currentRoofHeight, coords.z + 0.0f), 90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
    this->buildingFlats->addFlat(4.0f, 1.0f, glm::vec3(coords.x + 2.5f, coords.y + currentRoofHeight, coords.z + 0.0f), 90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
    this->buildingFlats->addFlat(1.0f, 4.0f, glm::vec3(coords.x + 0.0f, coords.y + currentRoofHeight, coords.z + 2.5f), 90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
    this->buildingFlats->addFlat(1.0f, 4.0f, glm::vec3(coords.x + 0.0f, coords.y + currentRoofHeight, coords.z - 2.5f), 90.0f, glm::vec3(0.0f, 0.0f, 1.0f));

    this->buildingFlats->addFlat(2.0f, 2.0f, glm::vec3(coords.x + 0.0f, coords.y + currentRoofHeight, coords.z + 0.0f), 90.0f, glm::vec3(0.0f, 0.0f, 1.0f));

    currentRoofHeight += ringFloors;

    this->buildingFlats->addFlat(4.0f, 1.0f, glm::vec3(coords.x - 2.5f, coords.y + currentRoofHeight, coords.z + 0.0f), 90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
    this->buildingFlats->addFlat(4.0f, 1.0f, glm::vec3(coords.x + 2.5f, coords.y + currentRoofHeight, coords.z + 0.0f), 90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
    this->buildingFlats->addFlat(1.0f, 4.0f, glm::vec3(coords.x + 0.0f, coords.y + currentRoofHeight, coords.z + 2.5f), 90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
    this->buildingFlats->addFlat(1.0f, 4.0f, glm::vec3(coords.x + 0.0f, coords.y + currentRoofHeight, coords.z - 2.5f), 90.0f, glm::vec3(0.0f, 0.0f, 1.0f));

    this->buildingFlats->addFlat(2.0f, 2.0f, glm::vec3(coords.x + 0.0f, coords.y + currentRoofHeight, coords.z + 0.0f), 90.0f, glm::vec3(0.0f, 0.0f, 1.0f));

    currentRoofHeight += gapSize;

    this->buildingFlats->addFlat(4.0f, 1.0f, glm::vec3(coords.x - 2.5f, coords.y + currentRoofHeight, coords.z + 0.0f), 90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
    this->buildingFlats->addFlat(4.0f, 1.0f, glm::vec3(coords.x + 2.5f, coords.y + currentRoofHeight, coords.z + 0.0f), 90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
    this->buildingFlats->addFlat(1.0f, 4.0f, glm::vec3(coords.x + 0.0f, coords.y + currentRoofHeight, coords.z + 2.5f), 90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
    this->buildingFlats->addFlat(1.0f, 4.0f, glm::vec3(coords.x + 0.0f, coords.y + currentRoofHeight, coords.z - 2.5f), 90.0f, glm::vec3(0.0f, 0.0f, 1.0f));

    this->buildingFlats->addFlat(2.0f, 2.0f, glm::vec3(coords.x + 0.0f, coords.y + currentRoofHeight, coords.z + 0.0f), 90.0f, glm::vec3(0.0f, 0.0f, 1.0f));

    currentRoofHeight += baseFloors + bufferFloors + upperFloors;

    this->buildingFlats->addFlat(6.0f, 6.0f, glm::vec3(coords.x + 0.0f, coords.y + currentRoofHeight, coords.z + 0.0f), 90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
}

void Building::generateTypeThreeBuilding(const glm::vec3 coords)
{
    // Data
    int flatTexIndex = 0;
    float currentHeight = 0.0f;
    float currentSmallerRingLayerHeight = 0.0f;
    float currentLargerRingLayerHeight = 0.0f;
    float currentFenceHeight = 0.0f;
    float currentRoofHeight = 0.0f;

    const float baseOneFloors = static_cast<float>(RandomNumberGenerator::getRandomNumber(3, 4));
    const float baseTwoFloors = static_cast<float>(RandomNumberGenerator::getRandomNumber(4, 5));
    const float bufferFloors = static_cast<float>(RandomNumberGenerator::getRandomNumber(3, 4));
    const float smallerRingFloors = 1.0f;
    const float largerRingFloors = 1.0f;
    const float numberOfRingLayers = static_cast<float>(RandomNumberGenerator::getRandomNumber(5, 6));
    const float singleUpperUnitFloors = static_cast<float>(RandomNumberGenerator::getRandomNumber(6, 7));
    const float upperFloors = singleUpperUnitFloors * numberOfRingLayers + smallerRingFloors + largerRingFloors;
    const float roofCoreFloors = 1.0f;
    const float pillarsFloors = baseOneFloors + baseTwoFloors + bufferFloors + upperFloors;
    const float fenceFloors = 1.0f;

    // Begin Generate Building Plot
    this->buildingFlats->addTexture("TechFlat4.png", flatTexIndex);
    this->buildingFlats->addFlat(8, 8, glm::vec3(coords.x, coords.y, coords.z), 90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
    flatTexIndex += 6;
    // End Generate Building Plot

    // Begin Generate Base

    currentHeight += static_cast<float>(baseOneFloors / 2.0f);
    this->buildingFlats->addTexture("TechWallGrille1.png", flatTexIndex);

    // Faces
    this->buildingFlats->addFlat(4.0f, baseOneFloors, glm::vec3(coords.x - 3.0f, coords.y + currentHeight, coords.z + 0.0f), 00.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->buildingFlats->addFlat(4.0f, baseOneFloors, glm::vec3(coords.x + 3.0f, coords.y + currentHeight, coords.z + 0.0f), 00.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->buildingFlats->addFlat(4.0f, baseOneFloors, glm::vec3(coords.x + 0.0f, coords.y + currentHeight, coords.z + 3.0f), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->buildingFlats->addFlat(4.0f, baseOneFloors, glm::vec3(coords.x + 0.0f, coords.y + currentHeight, coords.z - 3.0f), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    flatTexIndex += 6 * 4;

    currentHeight += static_cast<float>(baseOneFloors / 2.0f) + static_cast<float>(baseTwoFloors / 2.0f);

    this->buildingFlats->addFlat(4.0f, baseTwoFloors, glm::vec3(coords.x - 2.0f, coords.y + currentHeight, coords.z + 0.0f), 00.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->buildingFlats->addFlat(4.0f, baseTwoFloors, glm::vec3(coords.x + 2.0f, coords.y + currentHeight, coords.z + 0.0f), 00.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->buildingFlats->addFlat(4.0f, baseTwoFloors, glm::vec3(coords.x + 0.0f, coords.y + currentHeight, coords.z + 2.0f), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->buildingFlats->addFlat(4.0f, baseTwoFloors, glm::vec3(coords.x + 0.0f, coords.y + currentHeight, coords.z - 2.0f), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    flatTexIndex += 6 * 4;
    // End Generate Base

    // Begin Generate Buffer Floors
    currentHeight += static_cast<float>(baseTwoFloors / 2.0f) + static_cast<float>(bufferFloors / 2.0f);
    this->buildingFlats->addTexture("IronFence1_NP.png", flatTexIndex);

    this->buildingFlats->addFlat(4.0f, bufferFloors, glm::vec3(coords.x - 2.0f, coords.y + currentHeight, coords.z + 0.0f), 00.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->buildingFlats->addFlat(4.0f, bufferFloors, glm::vec3(coords.x + 2.0f, coords.y + currentHeight, coords.z + 0.0f), 00.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->buildingFlats->addFlat(4.0f, bufferFloors, glm::vec3(coords.x + 0.0f, coords.y + currentHeight, coords.z + 2.0f), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->buildingFlats->addFlat(4.0f, bufferFloors, glm::vec3(coords.x + 0.0f, coords.y + currentHeight, coords.z - 2.0f), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    flatTexIndex += 6 * 4;
    // End Generate Buffer Floors

    // Begin Generate Upper Floors
    currentHeight += static_cast<float>(bufferFloors / 2.0f) + static_cast<float>(upperFloors / 2.0f);
    this->buildingFlats->addTexture("TechGrille1_NP.png", flatTexIndex);

    this->buildingFlats->addFlat(4.0f, upperFloors, glm::vec3(coords.x - 2.0f, coords.y + currentHeight, coords.z + 0.0f), 00.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->buildingFlats->addFlat(4.0f, upperFloors, glm::vec3(coords.x + 2.0f, coords.y + currentHeight, coords.z + 0.0f), 00.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->buildingFlats->addFlat(4.0f, upperFloors, glm::vec3(coords.x + 0.0f, coords.y + currentHeight, coords.z + 2.0f), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->buildingFlats->addFlat(4.0f, upperFloors, glm::vec3(coords.x + 0.0f, coords.y + currentHeight, coords.z - 2.0f), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    flatTexIndex += 6 * 4;
    // End Generate Upper Floors

    // Begin Generate Roof Core
    currentHeight += static_cast<float>(upperFloors / 2.0f) - static_cast<float>(roofCoreFloors / 2.0f);
    this->buildingFlats->addTexture("IronFence4_NP.png", flatTexIndex);

    this->buildingFlats->addFlat(2.0f, roofCoreFloors, glm::vec3(coords.x - 1.0f, coords.y + currentHeight, coords.z + 0.0f), 00.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->buildingFlats->addFlat(2.0f, roofCoreFloors, glm::vec3(coords.x + 1.0f, coords.y + currentHeight, coords.z + 0.0f), 00.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->buildingFlats->addFlat(2.0f, roofCoreFloors, glm::vec3(coords.x + 0.0f, coords.y + currentHeight, coords.z + 1.0f), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->buildingFlats->addFlat(2.0f, roofCoreFloors, glm::vec3(coords.x + 0.0f, coords.y + currentHeight, coords.z - 1.0f), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    flatTexIndex += 6 * 4;
    // End Generate Roof Core

    // Begin Generate Fences
    currentFenceHeight = static_cast<float>(fenceFloors / 2.0f) + baseOneFloors;
    this->buildingFlats->addTexture("IronFenceTop3.png", flatTexIndex);

    this->buildingFlats->addFlat(4.0f, fenceFloors, glm::vec3(coords.x - 3.0f, coords.y + currentFenceHeight, coords.z + 0.0f), 00.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->buildingFlats->addFlat(4.0f, fenceFloors, glm::vec3(coords.x + 3.0f, coords.y + currentFenceHeight, coords.z + 0.0f), 00.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->buildingFlats->addFlat(4.0f, fenceFloors, glm::vec3(coords.x + 0.0f, coords.y + currentFenceHeight, coords.z + 3.0f), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->buildingFlats->addFlat(4.0f, fenceFloors, glm::vec3(coords.x + 0.0f, coords.y + currentFenceHeight, coords.z - 3.0f), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    flatTexIndex += 6 * 4;

    currentFenceHeight += baseTwoFloors + bufferFloors + upperFloors;

    this->buildingFlats->addFlat(4.0f, fenceFloors, glm::vec3(coords.x - 2.0f, coords.y + currentFenceHeight, coords.z + 0.0f), 00.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->buildingFlats->addFlat(4.0f, fenceFloors, glm::vec3(coords.x + 2.0f, coords.y + currentFenceHeight, coords.z + 0.0f), 00.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->buildingFlats->addFlat(4.0f, fenceFloors, glm::vec3(coords.x + 0.0f, coords.y + currentFenceHeight, coords.z + 2.0f), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->buildingFlats->addFlat(4.0f, fenceFloors, glm::vec3(coords.x + 0.0f, coords.y + currentFenceHeight, coords.z - 2.0f), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    flatTexIndex += 6 * 4;
    // End Generate Fences

    //  Begin Generate Rings
    currentSmallerRingLayerHeight = static_cast<float>(smallerRingFloors / 2.0f) + baseOneFloors + baseTwoFloors + bufferFloors;
    currentLargerRingLayerHeight = currentSmallerRingLayerHeight + smallerRingFloors;
    this->buildingFlats->addTexture("TechWall3Alt.png", flatTexIndex);

    for (int i = 0; i <= numberOfRingLayers; i++)
    {

        // Faces
        this->buildingFlats->addFlat(4.0f, smallerRingFloors, glm::vec3(coords.x - 4.0f, coords.y + currentSmallerRingLayerHeight, coords.z + 0.0f), 00.0f, glm::vec3(0.0f, 1.0f, 0.0f));
        this->buildingFlats->addFlat(4.0f, smallerRingFloors, glm::vec3(coords.x + 4.0f, coords.y + currentSmallerRingLayerHeight, coords.z + 0.0f), 00.0f, glm::vec3(0.0f, 1.0f, 0.0f));
        this->buildingFlats->addFlat(4.0f, smallerRingFloors, glm::vec3(coords.x + 0.0f, coords.y + currentSmallerRingLayerHeight, coords.z + 4.0f), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
        this->buildingFlats->addFlat(4.0f, smallerRingFloors, glm::vec3(coords.x + 0.0f, coords.y + currentSmallerRingLayerHeight, coords.z - 4.0f), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));

        flatTexIndex += 6 * 4;

        // Folds
        this->buildingFlats->addFlat(1.0f, smallerRingFloors, glm::vec3(coords.x - 2.0f, coords.y + currentSmallerRingLayerHeight, coords.z - 3.5f), 00.0f, glm::vec3(0.0f, 1.0f, 0.0f));
        this->buildingFlats->addFlat(1.0f, smallerRingFloors, glm::vec3(coords.x - 3.5f, coords.y + currentSmallerRingLayerHeight, coords.z - 2.0f), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));

        this->buildingFlats->addFlat(1.0f, smallerRingFloors, glm::vec3(coords.x - 2.0f, coords.y + currentSmallerRingLayerHeight, coords.z + 3.5f), 00.0f, glm::vec3(0.0f, 1.0f, 0.0f));
        this->buildingFlats->addFlat(1.0f, smallerRingFloors, glm::vec3(coords.x - 3.5f, coords.y + currentSmallerRingLayerHeight, coords.z + 2.0f), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));

        this->buildingFlats->addFlat(1.0f, smallerRingFloors, glm::vec3(coords.x + 2.0f, coords.y + currentSmallerRingLayerHeight, coords.z - 3.5f), 00.0f, glm::vec3(0.0f, 1.0f, 0.0f));
        this->buildingFlats->addFlat(1.0f, smallerRingFloors, glm::vec3(coords.x + 3.5f, coords.y + currentSmallerRingLayerHeight, coords.z - 2.0f), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));

        this->buildingFlats->addFlat(1.0f, smallerRingFloors, glm::vec3(coords.x + 2.0f, coords.y + currentSmallerRingLayerHeight, coords.z + 3.5f), 00.0f, glm::vec3(0.0f, 1.0f, 0.0f));
        this->buildingFlats->addFlat(1.0f, smallerRingFloors, glm::vec3(coords.x + 3.5f, coords.y + currentSmallerRingLayerHeight, coords.z + 2.0f), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));

        flatTexIndex += 6 * 8;

        // Faces

        this->buildingFlats->addFlat(6.0f, largerRingFloors, glm::vec3(coords.x - 5.0f, coords.y + currentLargerRingLayerHeight, coords.z + 0.0f), 00.0f, glm::vec3(0.0f, 1.0f, 0.0f));
        this->buildingFlats->addFlat(6.0f, largerRingFloors, glm::vec3(coords.x + 5.0f, coords.y + currentLargerRingLayerHeight, coords.z + 0.0f), 00.0f, glm::vec3(0.0f, 1.0f, 0.0f));
        this->buildingFlats->addFlat(6.0f, largerRingFloors, glm::vec3(coords.x + 0.0f, coords.y + currentLargerRingLayerHeight, coords.z + 5.0f), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
        this->buildingFlats->addFlat(6.0f, largerRingFloors, glm::vec3(coords.x + 0.0f, coords.y + currentLargerRingLayerHeight, coords.z - 5.0f), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));

        flatTexIndex += 6 * 4;
        // Folds
        this->buildingFlats->addFlat(2.0f, largerRingFloors, glm::vec3(coords.x - 3.0f, coords.y + currentLargerRingLayerHeight, coords.z - 4.0f), 00.0f, glm::vec3(0.0f, 1.0f, 0.0f));
        this->buildingFlats->addFlat(2.0f, largerRingFloors, glm::vec3(coords.x - 4.0f, coords.y + currentLargerRingLayerHeight, coords.z - 3.0f), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));

        this->buildingFlats->addFlat(2.0f, largerRingFloors, glm::vec3(coords.x - 3.0f, coords.y + currentLargerRingLayerHeight, coords.z + 4.0f), 00.0f, glm::vec3(0.0f, 1.0f, 0.0f));
        this->buildingFlats->addFlat(2.0f, largerRingFloors, glm::vec3(coords.x - 4.0f, coords.y + currentLargerRingLayerHeight, coords.z + 3.0f), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));

        this->buildingFlats->addFlat(2.0f, largerRingFloors, glm::vec3(coords.x + 3.0f, coords.y + currentLargerRingLayerHeight, coords.z - 4.0f), 00.0f, glm::vec3(0.0f, 1.0f, 0.0f));
        this->buildingFlats->addFlat(2.0f, largerRingFloors, glm::vec3(coords.x + 4.0f, coords.y + currentLargerRingLayerHeight, coords.z - 3.0f), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));

        this->buildingFlats->addFlat(2.0f, largerRingFloors, glm::vec3(coords.x + 3.0f, coords.y + currentLargerRingLayerHeight, coords.z + 4.0f), 00.0f, glm::vec3(0.0f, 1.0f, 0.0f));
        this->buildingFlats->addFlat(2.0f, largerRingFloors, glm::vec3(coords.x + 4.0f, coords.y + currentLargerRingLayerHeight, coords.z + 3.0f), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));

        flatTexIndex += 6 * 8;

        currentSmallerRingLayerHeight += singleUpperUnitFloors;
        currentLargerRingLayerHeight = currentSmallerRingLayerHeight + smallerRingFloors;
    }
    // End Generate Rings

    // Begin Generate Pillars
    const float pillarsHeight = static_cast<float>(pillarsFloors / 2.0f);
    this->buildingFlats->addTexture("TechFlat2.png", flatTexIndex);

    this->buildingFlats->addFlat(1.0f, pillarsFloors, glm::vec3(coords.x - 2.0f, coords.y + pillarsHeight, coords.z - 2.5f), 00.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->buildingFlats->addFlat(1.0f, pillarsFloors, glm::vec3(coords.x - 2.5f, coords.y + pillarsHeight, coords.z - 2.0f), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->buildingFlats->addFlat(1.0f, pillarsFloors, glm::vec3(coords.x - 3.0f, coords.y + pillarsHeight, coords.z - 2.5f), 00.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->buildingFlats->addFlat(1.0f, pillarsFloors, glm::vec3(coords.x - 2.5f, coords.y + pillarsHeight, coords.z - 3.0f), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));

    this->buildingFlats->addFlat(1.0f, pillarsFloors, glm::vec3(coords.x - 2.0f, coords.y + pillarsHeight, coords.z + 2.5f), 00.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->buildingFlats->addFlat(1.0f, pillarsFloors, glm::vec3(coords.x - 2.5f, coords.y + pillarsHeight, coords.z + 2.0f), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->buildingFlats->addFlat(1.0f, pillarsFloors, glm::vec3(coords.x - 3.0f, coords.y + pillarsHeight, coords.z + 2.5f), 00.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->buildingFlats->addFlat(1.0f, pillarsFloors, glm::vec3(coords.x - 2.5f, coords.y + pillarsHeight, coords.z + 3.0f), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));

    this->buildingFlats->addFlat(1.0f, pillarsFloors, glm::vec3(coords.x + 2.0f, coords.y + pillarsHeight, coords.z - 2.5f), 00.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->buildingFlats->addFlat(1.0f, pillarsFloors, glm::vec3(coords.x + 2.5f, coords.y + pillarsHeight, coords.z - 2.0f), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->buildingFlats->addFlat(1.0f, pillarsFloors, glm::vec3(coords.x + 3.0f, coords.y + pillarsHeight, coords.z - 2.5f), 00.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->buildingFlats->addFlat(1.0f, pillarsFloors, glm::vec3(coords.x + 2.5f, coords.y + pillarsHeight, coords.z - 3.0f), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));

    this->buildingFlats->addFlat(1.0f, pillarsFloors, glm::vec3(coords.x + 2.0f, coords.y + pillarsHeight, coords.z + 2.5f), 00.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->buildingFlats->addFlat(1.0f, pillarsFloors, glm::vec3(coords.x + 2.5f, coords.y + pillarsHeight, coords.z + 2.0f), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->buildingFlats->addFlat(1.0f, pillarsFloors, glm::vec3(coords.x + 3.0f, coords.y + pillarsHeight, coords.z + 2.5f), 00.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->buildingFlats->addFlat(1.0f, pillarsFloors, glm::vec3(coords.x + 2.5f, coords.y + pillarsHeight, coords.z + 3.0f), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    flatTexIndex += 6 * 16;
    // End Generate Pillars

    // Begin Generate Roofs
    currentRoofHeight += baseOneFloors;
    this->buildingFlats->addTexture("TechGrillePattern1_NP.png", flatTexIndex);

    this->buildingFlats->addFlat(4.0f, 1.0f, glm::vec3(coords.x - 2.5f, coords.y + currentRoofHeight, coords.z + 0.0f), 90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
    this->buildingFlats->addFlat(4.0f, 1.0f, glm::vec3(coords.x + 2.5f, coords.y + currentRoofHeight, coords.z + 0.0f), 90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
    this->buildingFlats->addFlat(1.0f, 4.0f, glm::vec3(coords.x + 0.0f, coords.y + currentRoofHeight, coords.z + 2.5f), 90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
    this->buildingFlats->addFlat(1.0f, 4.0f, glm::vec3(coords.x + 0.0f, coords.y + currentRoofHeight, coords.z - 2.5f), 90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
    flatTexIndex += 6 * 4;

    currentRoofHeight += baseTwoFloors + bufferFloors + upperFloors;

    this->buildingFlats->addFlat(4.0f, 1.0f, glm::vec3(coords.x - 1.5f, coords.y + currentRoofHeight, coords.z + 0.0f), 90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
    this->buildingFlats->addFlat(4.0f, 1.0f, glm::vec3(coords.x + 1.5f, coords.y + currentRoofHeight, coords.z + 0.0f), 90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
    this->buildingFlats->addFlat(1.0f, 4.0f, glm::vec3(coords.x + 0.0f, coords.y + currentRoofHeight, coords.z + 1.5f), 90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
    this->buildingFlats->addFlat(1.0f, 4.0f, glm::vec3(coords.x + 0.0f, coords.y + currentRoofHeight, coords.z - 1.5f), 90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
    flatTexIndex += 6 * 4;

    currentRoofHeight -= roofCoreFloors;

    this->buildingFlats->addFlat(2.0f, 2.0f, glm::vec3(coords.x + 0.0f, coords.y + currentRoofHeight, coords.z + 0.0f), 90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
    flatTexIndex += 6;

    currentRoofHeight = pillarsFloors;
    this->buildingFlats->addFlat(1.0f, 1.0f, glm::vec3(coords.x - 2.5f, coords.y + currentRoofHeight, coords.z - 2.5f), 90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
    this->buildingFlats->addFlat(1.0f, 1.0f, glm::vec3(coords.x - 2.5f, coords.y + currentRoofHeight, coords.z + 2.5f), 90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
    this->buildingFlats->addFlat(1.0f, 1.0f, glm::vec3(coords.x + 2.5f, coords.y + currentRoofHeight, coords.z - 2.5f), 90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
    this->buildingFlats->addFlat(1.0f, 1.0f, glm::vec3(coords.x + 2.5f, coords.y + currentRoofHeight, coords.z + 2.5f), 90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
    flatTexIndex += 6 * 4;
}