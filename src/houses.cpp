#include "houses.h"

Houses::Houses()
{
    this->housesFlats = new Polys();
}

Houses::~Houses()
{
    delete this->housesFlats;
    this->housesFlats = nullptr;
}

void Houses::update(float dt)
{
}

void Houses::render(const glm::mat4 &mProj, const glm::mat4 &mView)
{
    this->housesFlats->render(mProj, mView);
}

void Houses::render(const glm::mat4 &mProj, const glm::mat4 &mView, const glm::vec3 &lightDiffDir, const glm::vec3 &lightDiffCol, const glm::vec3 &lightAmbCol)
{
    this->housesFlats->render(mProj, mView, lightDiffDir, lightDiffCol, lightAmbCol);
}

void Houses::render(const glm::mat4 &mProj, const glm::mat4 &mView, Lighting *lighting)
{
    this->housesFlats->render(mProj, mView, lighting);
}

void Houses::beginConstructingHouses()
{
    this->housesFlats->beginConstructingVertices();
}
void Houses::constructHouse(glm::vec3 coords)

{
    const float houseWidth = 1.4f;
    const float houseLength = 1.8f;
    const float houseWallHeight = 1.0f;
    const float houseWallThickness = 0.05f;

    const float houseCurbHeight = 0.01f;

    const float houseFrontWallWidthLeft = 0.35f;
    const float houseFrontWallWidthMid = 0.3f;
    const float houseFrontWallWidthRight = 0.35f;
    const float houseOverhangHeight = 0.3f;
    const float houseFrontHeight = houseWallHeight - houseOverhangHeight;
    const float houseDoorFrameHeight = houseWallHeight - houseOverhangHeight - houseCurbHeight;
    const float houseDoorFrameWidth = static_cast<float>((houseLength - houseFrontWallWidthMid) / 2.0f) - houseFrontWallWidthLeft;
    const float houseWindowWidth = static_cast<float>((houseLength - houseFrontWallWidthMid) / 2.0f) - houseFrontWallWidthRight;
    const float houseWindowUnderhangHeight = 0.25f;
    const float houseWindowHeight = houseWallHeight - houseOverhangHeight - houseWindowUnderhangHeight;

    const float houseRoofAngle = 30.0f;
    const float houseRoofLength = houseLength + 0.2f;
    const float houseRoofThickness = 0.02f;
    const float houseRoofSideWidth = abs(static_cast<float>((houseWidth / 2.0f) / glm::cos(glm::radians(houseRoofAngle))));
    const float houseRoofHeightProj = abs(glm::sin(glm::radians(houseRoofAngle)) * houseRoofSideWidth);
    const float houseRoofWidthProj = static_cast<float>(houseWidth / 2.0f);
    const float houseRoofOverhangWidth = 0.25f;
    const float houseRoofOverhangHeightProj = abs(glm::sin(glm::radians(houseRoofAngle)) * houseRoofOverhangWidth);
    const float houseRoofOverhangWidthProj = abs(glm::cos(glm::radians(houseRoofAngle)) * houseRoofOverhangWidth);

    const float houseInnerWallRoofHeightProj = abs(houseWallThickness * glm::tan(glm::radians(houseRoofAngle)));
    const float houseInnerWidth = houseWidth - houseWallThickness * 2.0f;
    const float houseInnerLength = houseLength - houseWallThickness * 2.0f;
    const float houseInnerHeight = houseWallHeight + houseInnerWallRoofHeightProj;
    const float houseInnerRoofWidthProj = static_cast<float>(houseInnerWidth / 2.0f);
    const float houseInnerRoofHeightProj = houseRoofHeightProj - houseInnerWallRoofHeightProj;
    const float houseInnerOverhangHeight = houseOverhangHeight + houseInnerWallRoofHeightProj;
    const float houseInnerFrontWallWidthLeft = houseFrontWallWidthLeft - houseWallThickness;
    const float houseInnerFrontWallWidthRight = houseFrontWallWidthRight - houseWallThickness;
    const float houseInnerFrontHeight = houseInnerHeight - houseInnerOverhangHeight;

    const float housePillarLength = houseRoofOverhangWidthProj;
    const float housePillarWidth = 0.11f;
    const float housePillarHeight = houseWallHeight - houseRoofOverhangHeightProj;
    const float housePillarTopHeight = houseWallHeight - housePillarHeight;
    const float housePillarUpperHeight = 0.1f;
    const float housePillarUpperLength = houseRoofOverhangWidthProj;
    const float housePillarOverhangLength = 0.08f;
    const float housePillarLowerLength = housePillarUpperLength - housePillarOverhangLength;
    const float housePillarLowerHeight = housePillarHeight - housePillarUpperHeight;

    const float doorGap = 0.001f;
    const float doorThickness = 0.025f;
    const float doorWidth = static_cast<float>(houseDoorFrameWidth / 2.0f) - doorGap;
    const float doorHeight = houseDoorFrameHeight - doorGap;

    const float windowGap = 0.002f;
    const float windowThickness = 0.025f;
    const float windowWidth = static_cast<float>(houseWindowWidth / 2.0f) - windowGap;
    const float windowHeight = houseWindowHeight - windowGap;

    // Generate Ground
    this->housesFlats->addTexture("citypack/Grey.png", this->texIndex);
    this->housesFlats->addPoly04(50.0f, 50.0f,
                                 glm::vec3(
                                     coords.x,
                                     coords.y,
                                     coords.z),
                                 glm::vec3(0, 0, 270.0f));
    this->texIndex += 6 * 1;
    // Generate Floor
    this->housesFlats->addTexture("citypack/White.png", this->texIndex);
    this->housesFlats->addPoly04(houseInnerWidth, houseInnerLength,
                                 glm::vec3(
                                     coords.x,
                                     coords.y + houseCurbHeight,
                                     coords.z),
                                 glm::vec3(0, 0, 270.0f));
    this->housesFlats->addPoly04(houseWallThickness, houseDoorFrameWidth,
                                 glm::vec3(
                                     coords.x - static_cast<float>((houseLength - houseDoorFrameWidth) / 2.0f) + houseFrontWallWidthLeft,
                                     coords.y + houseCurbHeight,
                                     coords.z + static_cast<float>((houseWidth - houseWallThickness) / 2.0f)),
                                 glm::vec3(0, 0, 270.0f));
    this->texIndex += 6 * 2;

    // Generate  Left, Right, Back Walls
    // Outers
    this->housesFlats->addTexture("citypack/Yellow.png", this->texIndex);
    this->housesFlats->addPoly04(houseWidth, houseWallHeight, glm::vec3(coords.x - static_cast<float>(houseLength / 2.0f), coords.y + static_cast<float>(houseWallHeight / 2.0f), coords.z), glm::vec3(00.0f, 000.0f, 00.0f));
    this->housesFlats->addPoly04(houseWidth, houseWallHeight, glm::vec3(coords.x + static_cast<float>(houseLength / 2.0f), coords.y + static_cast<float>(houseWallHeight / 2.0f), coords.z), glm::vec3(00.0f, 180.0f, 00.0f));
    this->housesFlats->addPoly04(houseLength, houseWallHeight, glm::vec3(coords.x, coords.y + static_cast<float>(houseWallHeight / 2.0f), coords.z - static_cast<float>(houseWidth / 2.0f)), glm::vec3(00.0f, 270.0f, 00.0f));

    // Inners
    this->housesFlats->addPoly04(houseInnerWidth, houseInnerHeight, glm::vec3(coords.x - static_cast<float>(houseInnerLength / 2.0f), coords.y + static_cast<float>(houseInnerHeight / 2.0f), coords.z), glm::vec3(00.0f, 180.0f, 00.0f));
    this->housesFlats->addPoly04(houseInnerWidth, houseInnerHeight, glm::vec3(coords.x + static_cast<float>(houseInnerLength / 2.0f), coords.y + static_cast<float>(houseInnerHeight / 2.0f), coords.z), glm::vec3(00.0f, 000.0f, 00.0f));
    this->housesFlats->addPoly04(houseInnerLength, houseInnerHeight, glm::vec3(coords.x, coords.y + static_cast<float>(houseInnerHeight / 2.0f), coords.z - static_cast<float>(houseInnerWidth / 2.0f)), glm::vec3(00.0f, 90.0f, 00.0f));
    this->texIndex += 6 * 6;

    // Generate Front
    // Outers
    this->housesFlats->addPoly04(houseFrontWallWidthLeft, houseFrontHeight, glm::vec3(coords.x - static_cast<float>((houseLength - houseFrontWallWidthLeft) / 2.0f), coords.y + static_cast<float>(houseFrontHeight / 2.0f), coords.z + static_cast<float>(houseWidth / 2.0f)), glm::vec3(00.0f, 90.0f, 00.0f));
    this->housesFlats->addPoly04(houseFrontWallWidthRight, houseFrontHeight, glm::vec3(coords.x + static_cast<float>((houseLength - houseFrontWallWidthRight) / 2.0f), coords.y + static_cast<float>(houseFrontHeight / 2.0f), coords.z + static_cast<float>(houseWidth / 2.0f)), glm::vec3(00.0f, 90.0f, 00.0f));
    this->housesFlats->addPoly04(houseFrontWallWidthMid, houseWallHeight - houseOverhangHeight, glm::vec3(coords.x, coords.y + static_cast<float>(houseFrontHeight / 2.0f), coords.z + static_cast<float>(houseWidth / 2.0f)), glm::vec3(00.0f, 90.0f, 00.0f));
    this->housesFlats->addPoly04(houseLength, houseOverhangHeight, glm::vec3(coords.x, coords.y + static_cast<float>(houseWallHeight - houseOverhangHeight / 2.0f), coords.z + static_cast<float>(houseWidth / 2.0f)), glm::vec3(00.0f, 90.0f, 00.0f));
    this->housesFlats->addPoly04(houseWindowWidth, houseWindowUnderhangHeight, glm::vec3(coords.x + static_cast<float>((houseFrontWallWidthMid + houseWindowWidth) / 2.0f), coords.y + static_cast<float>(houseWindowUnderhangHeight / 2.0f), coords.z + static_cast<float>(houseWidth / 2.0f)), glm::vec3(00.0f, 90.0f, 00.0f));
    this->texIndex += 6 * 5;

    // Door Frame
    this->housesFlats->addPoly04(houseWallThickness, houseDoorFrameHeight,
                                 glm::vec3(
                                     coords.x - (static_cast<float>(houseLength / 2.0f) - houseFrontWallWidthLeft),
                                     coords.y + static_cast<float>(houseDoorFrameHeight / 2.0f) + houseCurbHeight,
                                     coords.z + static_cast<float>((houseWidth - houseWallThickness) / 2.0f)),
                                 glm::vec3(00.0f, 180.0f, 00.0f));
    this->housesFlats->addPoly04(houseWallThickness, houseDoorFrameHeight,
                                 glm::vec3(
                                     coords.x - (static_cast<float>(houseLength / 2.0f) - houseFrontWallWidthLeft - houseDoorFrameWidth),
                                     coords.y + static_cast<float>(houseDoorFrameHeight / 2.0f) + houseCurbHeight,
                                     coords.z + static_cast<float>((houseWidth - houseWallThickness) / 2.0f)),
                                 glm::vec3(00.0f, 000.0f, 00.0f));
    this->housesFlats->addPoly04(houseWallThickness, houseDoorFrameWidth,
                                 glm::vec3(
                                     coords.x - (static_cast<float>((houseLength - houseDoorFrameWidth) / 2.0f) - houseFrontWallWidthLeft),
                                     coords.y + houseDoorFrameHeight + houseCurbHeight,
                                     coords.z + static_cast<float>((houseWidth - houseWallThickness) / 2.0f)),
                                 glm::vec3(0, 0, 90.0f));
    this->texIndex += 6 * 3;

    // Window Frame
    this->housesFlats->addPoly04(houseWallThickness, houseWindowHeight,
                                 glm::vec3(
                                     coords.x + (static_cast<float>(houseLength / 2.0f) - houseFrontWallWidthRight - houseWindowWidth),
                                     coords.y + (houseWindowUnderhangHeight + static_cast<float>(houseWindowHeight / 2.0f)),
                                     coords.z + static_cast<float>((houseWidth - houseWallThickness) / 2.0f)),
                                 glm::vec3(00.0f, 180.0f, 00.0f));
    this->housesFlats->addPoly04(houseWallThickness, houseWindowHeight,
                                 glm::vec3(
                                     coords.x + (static_cast<float>(houseLength / 2.0f) - houseFrontWallWidthRight),
                                     coords.y + (houseWindowUnderhangHeight + static_cast<float>(houseWindowHeight / 2.0f)),
                                     coords.z + static_cast<float>((houseWidth - houseWallThickness) / 2.0f)),
                                 glm::vec3(00.0f, 000.0f, 00.0f));
    this->housesFlats->addPoly04(houseWallThickness, houseWindowWidth,
                                 glm::vec3(
                                     coords.x + (static_cast<float>((houseLength - houseWindowWidth) / 2.0f) - houseFrontWallWidthRight),
                                     coords.y + (houseWindowUnderhangHeight + houseWindowHeight),
                                     coords.z + static_cast<float>((houseWidth - houseWallThickness) / 2.0f)),
                                 glm::vec3(0, 0, 90.0f));
    this->housesFlats->addPoly04(houseWallThickness, houseWindowWidth,
                                 glm::vec3(
                                     coords.x + (static_cast<float>((houseLength - houseWindowWidth) / 2.0f) - houseFrontWallWidthRight),
                                     coords.y + houseWindowUnderhangHeight,
                                     coords.z + static_cast<float>((houseWidth - houseWallThickness) / 2.0f)),
                                 glm::vec3(0, 0, 270.0f));
    this->texIndex += 6 * 4;

    // Inners
    this->housesFlats->addPoly04(houseInnerFrontWallWidthLeft, houseInnerHeight, glm::vec3(coords.x - static_cast<float>((houseInnerLength - houseInnerFrontWallWidthLeft) / 2.0f), coords.y + static_cast<float>(houseInnerHeight / 2.0f), coords.z + static_cast<float>(houseInnerWidth / 2.0f)), glm::vec3(00.0f, 270.0f, 00.0f));
    this->housesFlats->addPoly04(houseFrontWallWidthMid, houseInnerHeight, glm::vec3(coords.x, coords.y + static_cast<float>(houseInnerHeight / 2.0f), coords.z + static_cast<float>(houseInnerWidth / 2.0f)), glm::vec3(00.0f, 270.0f, 00.0f));
    this->housesFlats->addPoly04(houseInnerFrontWallWidthRight, houseInnerHeight, glm::vec3(coords.x + static_cast<float>((houseInnerLength - houseInnerFrontWallWidthRight) / 2.0f), coords.y + static_cast<float>(houseInnerHeight / 2.0f), coords.z + static_cast<float>(houseInnerWidth / 2.0f)), glm::vec3(00.0f, 270.0f, 00.0f));
    this->housesFlats->addPoly04(houseInnerLength, houseInnerOverhangHeight, glm::vec3(coords.x, coords.y + (houseFrontHeight + static_cast<float>(houseInnerOverhangHeight / 2.0f)), coords.z + (static_cast<float>(houseInnerWidth / 2.0f))), glm::vec3(00.0f, 270.0f, 00.0f));
    this->housesFlats->addPoly04(houseWindowWidth, houseWindowUnderhangHeight, glm::vec3(coords.x + static_cast<float>((houseFrontWallWidthMid + houseWindowWidth) / 2.0f), coords.y + static_cast<float>(houseWindowUnderhangHeight / 2.0f), coords.z + static_cast<float>(houseInnerWidth / 2.0f)), glm::vec3(00.0f, 270.0f, 00.0f));
    this->texIndex += 6 * 5;

    this->housesFlats->addPoly04(housePillarWidth, housePillarLowerHeight, glm::vec3(coords.x - static_cast<float>((houseLength - housePillarWidth) / 2.0f), coords.y + static_cast<float>(housePillarLowerHeight / 2.0f), coords.z + (static_cast<float>(houseWidth / 2.0f) + housePillarLowerLength)), glm::vec3(00.0f, 90.0f, 00.0f));
    this->housesFlats->addPoly04(housePillarLowerLength, housePillarLowerHeight, glm::vec3(coords.x - static_cast<float>(houseLength / 2.0f), coords.y + static_cast<float>(housePillarLowerHeight / 2.0f), coords.z + (static_cast<float>((houseWidth + housePillarLowerLength) / 2.0f))), glm::vec3(00.0f, 00.0f, 00.0f));
    this->housesFlats->addPoly04(housePillarLowerLength, housePillarLowerHeight, glm::vec3(coords.x - (static_cast<float>(houseLength / 2.0f) - housePillarWidth), coords.y + static_cast<float>(housePillarLowerHeight / 2.0f), coords.z + (static_cast<float>((houseWidth + housePillarLowerLength) / 2.0f))), glm::vec3(00.0f, 180.0f, 00.0f));

    this->housesFlats->addPoly04(housePillarWidth, housePillarUpperHeight, glm::vec3(coords.x - static_cast<float>((houseLength - housePillarWidth) / 2.0f), coords.y + (housePillarLowerHeight + static_cast<float>(housePillarUpperHeight / 2.0f)), coords.z + (static_cast<float>(houseWidth / 2.0f) + housePillarUpperLength)), glm::vec3(00.0f, 90.0f, 00.0f));
    this->housesFlats->addPoly04(housePillarUpperLength, housePillarUpperHeight, glm::vec3(coords.x - static_cast<float>(houseLength / 2.0f), coords.y + (housePillarLowerHeight + static_cast<float>(housePillarUpperHeight / 2.0f)), coords.z + (static_cast<float>((houseWidth + housePillarUpperLength) / 2.0f))), glm::vec3(00.0f, 00.0f, 00.0f));
    this->housesFlats->addPoly04(housePillarUpperLength, housePillarUpperHeight, glm::vec3(coords.x - (static_cast<float>(houseLength / 2.0f) - housePillarWidth), coords.y + (housePillarLowerHeight + static_cast<float>(housePillarUpperHeight / 2.0f)), coords.z + (static_cast<float>((houseWidth + housePillarUpperLength) / 2.0f))), glm::vec3(00.0f, 180.0f, 00.0f));
    this->housesFlats->addPoly04(housePillarUpperLength, housePillarWidth, glm::vec3(coords.x - static_cast<float>((houseLength - housePillarWidth) / 2.0f), coords.y + housePillarLowerHeight, coords.z + (static_cast<float>((houseWidth + housePillarUpperLength) / 2.0f))), glm::vec3(00.0f, 00.0f, 90.0f));
    this->texIndex += 6 * 7;

    this->housesFlats->addPoly04(housePillarWidth, housePillarLowerHeight, glm::vec3(coords.x + static_cast<float>((houseLength - housePillarWidth) / 2.0f), coords.y + static_cast<float>(housePillarLowerHeight / 2.0f), coords.z + (static_cast<float>(houseWidth / 2.0f) + housePillarLowerLength)), glm::vec3(00.0f, 90.0f, 00.0f));
    this->housesFlats->addPoly04(housePillarLowerLength, housePillarLowerHeight, glm::vec3(coords.x + (static_cast<float>(houseLength / 2.0f) - housePillarWidth), coords.y + static_cast<float>(housePillarLowerHeight / 2.0f), coords.z + (static_cast<float>((houseWidth + housePillarLowerLength) / 2.0f))), glm::vec3(00.0f, 00.0f, 00.0f));
    this->housesFlats->addPoly04(housePillarLowerLength, housePillarLowerHeight, glm::vec3(coords.x + static_cast<float>(houseLength / 2.0f), coords.y + static_cast<float>(housePillarLowerHeight / 2.0f), coords.z + (static_cast<float>((houseWidth + housePillarLowerLength) / 2.0f))), glm::vec3(00.0f, 180.0f, 00.0f));

    this->housesFlats->addPoly04(housePillarWidth, housePillarUpperHeight, glm::vec3(coords.x + static_cast<float>((houseLength - housePillarWidth) / 2.0f), coords.y + (housePillarLowerHeight + static_cast<float>(housePillarUpperHeight / 2.0f)), coords.z + (static_cast<float>(houseWidth / 2.0f) + housePillarUpperLength)), glm::vec3(00.0f, 90.0f, 00.0f));
    this->housesFlats->addPoly04(housePillarUpperLength, housePillarUpperHeight, glm::vec3(coords.x + (static_cast<float>(houseLength / 2.0f) - housePillarWidth), coords.y + (housePillarLowerHeight + static_cast<float>(housePillarUpperHeight / 2.0f)), coords.z + (static_cast<float>((houseWidth + housePillarUpperLength) / 2.0f))), glm::vec3(00.0f, 00.0f, 00.0f));
    this->housesFlats->addPoly04(housePillarUpperLength, housePillarUpperHeight, glm::vec3(coords.x + static_cast<float>(houseLength / 2.0f), coords.y + (housePillarLowerHeight + static_cast<float>(housePillarUpperHeight / 2.0f)), coords.z + (static_cast<float>((houseWidth + housePillarUpperLength) / 2.0f))), glm::vec3(00.0f, 180.0f, 00.0f));
    this->housesFlats->addPoly04(housePillarUpperLength, housePillarWidth, glm::vec3(coords.x + static_cast<float>((houseLength - housePillarWidth) / 2.0f), coords.y + housePillarLowerHeight, coords.z + (static_cast<float>((houseWidth + housePillarUpperLength) / 2.0f))), glm::vec3(00.0f, 00.0f, 90.0f));
    this->texIndex += 6 * 7;

    this->housesFlats->addPoly04(housePillarWidth, housePillarLowerHeight, glm::vec3(coords.x - static_cast<float>((houseLength - housePillarWidth) / 2.0f), coords.y + static_cast<float>(housePillarLowerHeight / 2.0f), coords.z - (static_cast<float>(houseWidth / 2.0f) + housePillarLowerLength)), glm::vec3(00.0f, 270.0f, 00.0f));
    this->housesFlats->addPoly04(housePillarLowerLength, housePillarLowerHeight, glm::vec3(coords.x - static_cast<float>(houseLength / 2.0f), coords.y + static_cast<float>(housePillarLowerHeight / 2.0f), coords.z - (static_cast<float>((houseWidth + housePillarLowerLength) / 2.0f))), glm::vec3(00.0f, 00.0f, 00.0f));
    this->housesFlats->addPoly04(housePillarLowerLength, housePillarLowerHeight, glm::vec3(coords.x - (static_cast<float>(houseLength / 2.0f) - housePillarWidth), coords.y + static_cast<float>(housePillarLowerHeight / 2.0f), coords.z - (static_cast<float>((houseWidth + housePillarLowerLength) / 2.0f))), glm::vec3(00.0f, 180.0f, 00.0f));

    this->housesFlats->addPoly04(housePillarWidth, housePillarUpperHeight, glm::vec3(coords.x - static_cast<float>((houseLength - housePillarWidth) / 2.0f), coords.y + (housePillarLowerHeight + static_cast<float>(housePillarUpperHeight / 2.0f)), coords.z - (static_cast<float>(houseWidth / 2.0f) + housePillarUpperLength)), glm::vec3(00.0f, 270.0f, 00.0f));
    this->housesFlats->addPoly04(housePillarUpperLength, housePillarUpperHeight, glm::vec3(coords.x - static_cast<float>(houseLength / 2.0f), coords.y + (housePillarLowerHeight + static_cast<float>(housePillarUpperHeight / 2.0f)), coords.z - (static_cast<float>((houseWidth + housePillarUpperLength) / 2.0f))), glm::vec3(00.0f, 00.0f, 00.0f));
    this->housesFlats->addPoly04(housePillarUpperLength, housePillarUpperHeight, glm::vec3(coords.x - (static_cast<float>(houseLength / 2.0f) - housePillarWidth), coords.y + (housePillarLowerHeight + static_cast<float>(housePillarUpperHeight / 2.0f)), coords.z - (static_cast<float>((houseWidth + housePillarUpperLength) / 2.0f))), glm::vec3(00.0f, 180.0f, 00.0f));
    this->housesFlats->addPoly04(housePillarUpperLength, housePillarWidth, glm::vec3(coords.x - static_cast<float>((houseLength - housePillarWidth) / 2.0f), coords.y + housePillarLowerHeight, coords.z - (static_cast<float>((houseWidth + housePillarUpperLength) / 2.0f))), glm::vec3(00.0f, 00.0f, 90.0f));
    this->texIndex += 6 * 7;

    this->housesFlats->addPoly04(housePillarWidth, housePillarLowerHeight, glm::vec3(coords.x + static_cast<float>((houseLength - housePillarWidth) / 2.0f), coords.y + static_cast<float>(housePillarLowerHeight / 2.0f), coords.z - (static_cast<float>(houseWidth / 2.0f) + housePillarLowerLength)), glm::vec3(00.0f, 270.0f, 00.0f));
    this->housesFlats->addPoly04(housePillarLowerLength, housePillarLowerHeight, glm::vec3(coords.x + (static_cast<float>(houseLength / 2.0f) - housePillarWidth), coords.y + static_cast<float>(housePillarLowerHeight / 2.0f), coords.z - (static_cast<float>((houseWidth + housePillarLowerLength) / 2.0f))), glm::vec3(00.0f, 00.0f, 00.0f));
    this->housesFlats->addPoly04(housePillarLowerLength, housePillarLowerHeight, glm::vec3(coords.x + static_cast<float>(houseLength / 2.0f), coords.y + static_cast<float>(housePillarLowerHeight / 2.0f), coords.z - (static_cast<float>((houseWidth + housePillarLowerLength) / 2.0f))), glm::vec3(00.0f, 180.0f, 00.0f));

    this->housesFlats->addPoly04(housePillarWidth, housePillarUpperHeight, glm::vec3(coords.x + static_cast<float>((houseLength - housePillarWidth) / 2.0f), coords.y + (housePillarLowerHeight + static_cast<float>(housePillarUpperHeight / 2.0f)), coords.z - (static_cast<float>(houseWidth / 2.0f) + housePillarUpperLength)), glm::vec3(00.0f, 270.0f, 00.0f));
    this->housesFlats->addPoly04(housePillarUpperLength, housePillarUpperHeight, glm::vec3(coords.x + (static_cast<float>(houseLength / 2.0f) - housePillarWidth), coords.y + (housePillarLowerHeight + static_cast<float>(housePillarUpperHeight / 2.0f)), coords.z - (static_cast<float>((houseWidth + housePillarUpperLength) / 2.0f))), glm::vec3(00.0f, 00.0f, 00.0f));
    this->housesFlats->addPoly04(housePillarUpperLength, housePillarUpperHeight, glm::vec3(coords.x + static_cast<float>(houseLength / 2.0f), coords.y + (housePillarLowerHeight + static_cast<float>(housePillarUpperHeight / 2.0f)), coords.z - (static_cast<float>((houseWidth + housePillarUpperLength) / 2.0f))), glm::vec3(00.0f, 180.0f, 00.0f));
    this->housesFlats->addPoly04(housePillarUpperLength, housePillarWidth, glm::vec3(coords.x + static_cast<float>((houseLength - housePillarWidth) / 2.0f), coords.y + housePillarLowerHeight, coords.z - (static_cast<float>((houseWidth + housePillarUpperLength) / 2.0f))), glm::vec3(00.0f, 00.0f, 90.0f));
    this->texIndex += 6 * 7;
    // Generate Roof Walls

    // Outers
    this->housesFlats->addPoly03(houseRoofWidthProj, houseRoofHeightProj, glm::vec3(coords.x - static_cast<float>(houseLength / 2.0f), coords.y + houseWallHeight + static_cast<float>(houseRoofHeightProj / 2.0f), coords.z + static_cast<float>(houseRoofWidthProj / 2.0f)), glm::vec3(00.0f, 00.0f, 00.0f), 1, 1);
    this->housesFlats->addPoly03(houseRoofWidthProj, houseRoofHeightProj, glm::vec3(coords.x - static_cast<float>(houseLength / 2.0f), coords.y + houseWallHeight + static_cast<float>(houseRoofHeightProj / 2.0f), coords.z - static_cast<float>(houseRoofWidthProj / 2.0f)), glm::vec3(00.0f, 00.0f, 00.0f), 1, -1);

    this->housesFlats->addPoly03(houseRoofWidthProj, houseRoofHeightProj, glm::vec3(coords.x + static_cast<float>(houseLength / 2.0f), coords.y + houseWallHeight + static_cast<float>(houseRoofHeightProj / 2.0f), coords.z + static_cast<float>(houseRoofWidthProj / 2.0f)), glm::vec3(00.0f, 00.0f, 00.0f), -1, 1);
    this->housesFlats->addPoly03(houseRoofWidthProj, houseRoofHeightProj, glm::vec3(coords.x + static_cast<float>(houseLength / 2.0f), coords.y + houseWallHeight + static_cast<float>(houseRoofHeightProj / 2.0f), coords.z - static_cast<float>(houseRoofWidthProj / 2.0f)), glm::vec3(00.0f, 00.0f, 00.0f), -1, -1);
    this->texIndex += 3 * 4;

    // Inners
    this->housesFlats->addPoly03(houseInnerRoofWidthProj, houseInnerRoofHeightProj, glm::vec3(coords.x - static_cast<float>(houseInnerLength / 2.0f), coords.y + houseInnerHeight + static_cast<float>(houseInnerRoofHeightProj / 2.0f), coords.z + static_cast<float>(houseInnerRoofWidthProj / 2.0f)), glm::vec3(00.0f, 00.0f, 00.0f), -1, 1);
    this->housesFlats->addPoly03(houseInnerRoofWidthProj, houseInnerRoofHeightProj, glm::vec3(coords.x - static_cast<float>(houseInnerLength / 2.0f), coords.y + houseInnerHeight + static_cast<float>(houseInnerRoofHeightProj / 2.0f), coords.z - static_cast<float>(houseInnerRoofWidthProj / 2.0f)), glm::vec3(00.0f, 00.0f, 00.0f), -1, -1);

    this->housesFlats->addPoly03(houseInnerRoofWidthProj, houseInnerRoofHeightProj, glm::vec3(coords.x + static_cast<float>(houseInnerLength / 2.0f), coords.y + houseInnerHeight + static_cast<float>(houseInnerRoofHeightProj / 2.0f), coords.z + static_cast<float>(houseInnerRoofWidthProj / 2.0f)), glm::vec3(00.0f, 00.0f, 00.0f), 1, 1);
    this->housesFlats->addPoly03(houseInnerRoofWidthProj, houseInnerRoofHeightProj, glm::vec3(coords.x + static_cast<float>(houseInnerLength / 2.0f), coords.y + houseInnerHeight + static_cast<float>(houseInnerRoofHeightProj / 2.0f), coords.z - static_cast<float>(houseInnerRoofWidthProj / 2.0f)), glm::vec3(00.0f, 00.0f, 00.0f), 1, -1);
    this->texIndex += 3 * 4;

    // Generate Pillar Tops
    this->housesFlats->addPoly03(housePillarLength, housePillarTopHeight, glm::vec3(coords.x - static_cast<float>(houseLength / 2.0f), coords.y + housePillarHeight + static_cast<float>(housePillarTopHeight / 2.0f), coords.z + (static_cast<float>((houseWidth + housePillarLength) / 2.0f))), glm::vec3(00.0f, 00.0f, 00.0f), 1, 1);
    this->housesFlats->addPoly03(housePillarLength, housePillarTopHeight, glm::vec3(coords.x - (static_cast<float>(houseLength / 2.0f) - housePillarWidth), coords.y + housePillarHeight + static_cast<float>(housePillarTopHeight / 2.0f), coords.z + (static_cast<float>((houseWidth + housePillarLength) / 2.0f))), glm::vec3(00.0f, 00.0f, 00.0f), -1, 1);

    this->housesFlats->addPoly03(housePillarLength, housePillarTopHeight, glm::vec3(coords.x + (static_cast<float>(houseLength / 2.0f) - housePillarWidth), coords.y + housePillarHeight + static_cast<float>(housePillarTopHeight / 2.0f), coords.z + (static_cast<float>((houseWidth + housePillarLength) / 2.0f))), glm::vec3(00.0f, 00.0f, 00.0f), 1, 1);
    this->housesFlats->addPoly03(housePillarLength, housePillarTopHeight, glm::vec3(coords.x + static_cast<float>(houseLength / 2.0f), coords.y + housePillarHeight + static_cast<float>(housePillarTopHeight / 2.0f), coords.z + (static_cast<float>((houseWidth + housePillarLength) / 2.0f))), glm::vec3(00.0f, 00.0f, 00.0f), -1, 1);

    this->housesFlats->addPoly03(housePillarLength, housePillarTopHeight, glm::vec3(coords.x - static_cast<float>(houseLength / 2.0f), coords.y + housePillarHeight + static_cast<float>(housePillarTopHeight / 2.0f), coords.z - static_cast<float>((houseWidth + housePillarLength) / 2.0f)), glm::vec3(00.0f, 00.0f, 00.0f), 1, -1);
    this->housesFlats->addPoly03(housePillarLength, housePillarTopHeight, glm::vec3(coords.x - (static_cast<float>(houseLength / 2.0f) - housePillarWidth), coords.y + housePillarHeight + static_cast<float>(housePillarTopHeight / 2.0f), coords.z - static_cast<float>((houseWidth + housePillarLength) / 2.0f)), glm::vec3(00.0f, 00.0f, 00.0f), -1, -1);

    this->housesFlats->addPoly03(housePillarLength, housePillarTopHeight, glm::vec3(coords.x + (static_cast<float>(houseLength / 2.0f) - housePillarWidth), coords.y + housePillarHeight + static_cast<float>(housePillarTopHeight / 2.0f), coords.z - static_cast<float>((houseWidth + housePillarLength) / 2.0f)), glm::vec3(00.0f, 00.0f, 00.0f), 1, -1);
    this->housesFlats->addPoly03(housePillarLength, housePillarTopHeight, glm::vec3(coords.x + static_cast<float>(houseLength / 2.0f), coords.y + housePillarHeight + static_cast<float>(housePillarTopHeight / 2.0f), coords.z - static_cast<float>((houseWidth + housePillarLength) / 2.0f)), glm::vec3(00.0f, 00.0f, 00.0f), -1, -1);
    this->texIndex += 3 * 8;

    // Generate Roof
    this->housesFlats->addTexture("citypack/Brown.png", this->texIndex);
    this->housesFlats->addPoly04(houseRoofSideWidth, houseRoofLength, glm::vec3(coords.x, coords.y + houseWallHeight + static_cast<float>(houseRoofHeightProj / 2.0f), coords.z + static_cast<float>((houseWidth - houseRoofWidthProj) / 2.0f)), glm::vec3(+houseRoofAngle, 0.0f, 270.0f));
    this->housesFlats->addPoly04(houseRoofSideWidth, houseRoofLength, glm::vec3(coords.x, coords.y + houseWallHeight + static_cast<float>(houseRoofHeightProj / 2.0f), coords.z - static_cast<float>((houseWidth - houseRoofWidthProj) / 2.0f)), glm::vec3(-houseRoofAngle, 0.0f, 270.0f));
    this->housesFlats->addPoly04(houseRoofOverhangWidth, houseRoofLength, glm::vec3(coords.x, coords.y + houseWallHeight - static_cast<float>(houseRoofOverhangHeightProj / 2.0f), coords.z + static_cast<float>((houseWidth + houseRoofOverhangWidthProj) / 2.0f)), glm::vec3(+houseRoofAngle, 0.0f, 270.0f));
    this->housesFlats->addPoly04(houseRoofOverhangWidth, houseRoofLength, glm::vec3(coords.x, coords.y + houseWallHeight - static_cast<float>(houseRoofOverhangHeightProj / 2.0f), coords.z - static_cast<float>((houseWidth + houseRoofOverhangWidthProj) / 2.0f)), glm::vec3(-houseRoofAngle, 0.0f, 270.0f));
    this->texIndex += 6 * 4;

    // Generate Doors
    // Left Door
    this->housesFlats->addTexture("citypack/GreyBlue.png", this->texIndex);
    this->housesFlats->addPoly04(doorWidth, doorHeight,
                                 glm::vec3(
                                     coords.x - (static_cast<float>((houseLength) / 2.0f) - houseFrontWallWidthLeft - static_cast<float>((houseDoorFrameWidth) / 4.0f)),
                                     coords.y + static_cast<float>(doorHeight / 2.0f) + houseCurbHeight,
                                     coords.z + static_cast<float>(houseWidth / 2.0f)),
                                 glm::vec3(00.0f, 90.0f, 00.0f));
    this->housesFlats->addPoly04(doorWidth, doorHeight,
                                 glm::vec3(
                                     coords.x - (static_cast<float>((houseLength) / 2.0f) - houseFrontWallWidthLeft - static_cast<float>((houseDoorFrameWidth) / 4.0f)),
                                     coords.y + static_cast<float>(doorHeight / 2.0f) + houseCurbHeight,
                                     coords.z + static_cast<float>(houseWidth / 2.0f) - doorThickness),
                                 glm::vec3(00.0f, 270.0f, 00.0f));
    this->housesFlats->addPoly04(doorThickness, doorHeight,
                                 glm::vec3(
                                     coords.x - (static_cast<float>((houseLength - doorGap) / 2.0f) - houseFrontWallWidthLeft),
                                     coords.y + static_cast<float>(doorHeight / 2.0f) + houseCurbHeight,
                                     coords.z + static_cast<float>((houseWidth - doorThickness) / 2.0f)),
                                 glm::vec3(00.0f, 00.0f, 00.0f));
    this->housesFlats->addPoly04(doorThickness, doorHeight,
                                 glm::vec3(
                                     coords.x - (static_cast<float>((houseLength - doorGap) / 2.0f) - houseFrontWallWidthLeft - doorWidth),
                                     coords.y + static_cast<float>(doorHeight / 2.0f) + houseCurbHeight,
                                     coords.z + static_cast<float>((houseWidth - doorThickness) / 2.0f)),
                                 glm::vec3(00.0f, 180.0f, 00.0f));
    this->housesFlats->addPoly04(doorThickness, doorWidth,
                                 glm::vec3(
                                     coords.x - (static_cast<float>((houseLength) / 2.0f) - houseFrontWallWidthLeft - static_cast<float>((houseDoorFrameWidth) / 4.0f)),
                                     coords.y + doorHeight + houseCurbHeight,
                                     coords.z + static_cast<float>((houseWidth - doorThickness) / 2.0f)),
                                 glm::vec3(00.0f, 00.0f, 270.0f));
    this->texIndex += 6 * 5;

    // Right Door
    this->housesFlats->addPoly04(doorWidth, doorHeight,
                                 glm::vec3(
                                     coords.x - (static_cast<float>(houseLength / 2.0f) - houseFrontWallWidthLeft - static_cast<float>((3.0f * houseDoorFrameWidth) / 4.0f)),
                                     coords.y + static_cast<float>(doorHeight / 2.0f) + houseCurbHeight,
                                     coords.z + static_cast<float>(houseWidth / 2.0f)),
                                 glm::vec3(00.0f, 90.0f, 00.0f));
    this->housesFlats->addPoly04(doorWidth, doorHeight,
                                 glm::vec3(
                                     coords.x - (static_cast<float>(houseLength / 2.0f) - houseFrontWallWidthLeft - static_cast<float>((3.0f * houseDoorFrameWidth) / 4.0f)),
                                     coords.y + static_cast<float>(doorHeight / 2.0f) + houseCurbHeight,
                                     coords.z + static_cast<float>(houseWidth / 2.0f) - doorThickness),
                                 glm::vec3(00.0f, 270.0f, 00.0f));
    this->housesFlats->addPoly04(doorThickness, doorHeight,
                                 glm::vec3(
                                     coords.x - (static_cast<float>((houseLength - houseDoorFrameWidth) / 2.0f) - houseFrontWallWidthLeft - doorGap),
                                     coords.y + static_cast<float>(doorHeight / 2.0f) + houseCurbHeight,
                                     coords.z + static_cast<float>((houseWidth - doorThickness) / 2.0f)),
                                 glm::vec3(00.0f, 00.0f, 00.0f));
    this->housesFlats->addPoly04(doorThickness, doorHeight,
                                 glm::vec3(
                                     coords.x - (static_cast<float>((houseLength + doorGap) / 2.0f) - houseFrontWallWidthLeft - houseDoorFrameWidth),
                                     coords.y + static_cast<float>(doorHeight / 2.0f) + houseCurbHeight,
                                     coords.z + static_cast<float>((houseWidth - doorThickness) / 2.0f)),
                                 glm::vec3(00.0f, 180.0f, 00.0f));
    this->housesFlats->addPoly04(doorThickness, doorWidth,
                                 glm::vec3(
                                     coords.x - (static_cast<float>(houseLength / 2.0f) - houseFrontWallWidthLeft - static_cast<float>((3.0f * houseDoorFrameWidth) / 4.0f)),
                                     coords.y + doorHeight + houseCurbHeight,
                                     coords.z + static_cast<float>((houseWidth - doorThickness) / 2.0f)),
                                 glm::vec3(00.0f, 00.0f, 270.0f));
    this->texIndex += 6 * 5;

    // Generate Windows
    // Left Window
    this->housesFlats->addPoly04(windowWidth, windowHeight, glm::vec3(coords.x + (static_cast<float>(houseLength / 2.0f) - houseFrontWallWidthRight - static_cast<float>((3.0f * houseDoorFrameWidth) / 4.0f)), coords.y + (houseWindowUnderhangHeight + static_cast<float>(windowHeight / 2.0f)), coords.z + static_cast<float>(houseWidth / 2.0f)), glm::vec3(00.0f, 90.0f, 00.0f));
    this->housesFlats->addPoly04(windowWidth, windowHeight, glm::vec3(coords.x + (static_cast<float>(houseLength / 2.0f) - houseFrontWallWidthRight - static_cast<float>((3.0f * houseDoorFrameWidth) / 4.0f)), coords.y + (houseWindowUnderhangHeight + static_cast<float>(windowHeight / 2.0f)), coords.z + (static_cast<float>(houseWidth / 2.0f) - windowThickness)), glm::vec3(00.0f, 270.0f, 00.0f));
    this->housesFlats->addPoly04(windowThickness, windowHeight, glm::vec3(coords.x + (static_cast<float>((houseLength + windowGap) / 2.0f) - houseFrontWallWidthRight - houseWindowWidth), coords.y + (houseWindowUnderhangHeight + static_cast<float>(windowHeight / 2.0f)), coords.z + static_cast<float>((houseWidth - windowThickness) / 2.0f)), glm::vec3(00.0f, 00.0f, 00.0f));
    this->housesFlats->addPoly04(windowThickness, windowHeight, glm::vec3(coords.x + (static_cast<float>((houseLength - houseWindowWidth - windowGap) / 2.0f) - houseFrontWallWidthRight), coords.y + (houseWindowUnderhangHeight + static_cast<float>(windowHeight / 2.0f)), coords.z + static_cast<float>((houseWidth - windowThickness) / 2.0f)), glm::vec3(00.0f, 180.0f, 00.0f));
    this->housesFlats->addPoly04(windowThickness, windowWidth, glm::vec3(coords.x + (static_cast<float>((houseLength) / 2.0f) - houseFrontWallWidthRight - static_cast<float>((3.0f * houseWindowWidth) / 4.0f)), coords.y + (houseWindowUnderhangHeight + windowHeight), coords.z + static_cast<float>((houseWidth - windowThickness) / 2.0f)), glm::vec3(00.0f, 00.0f, 270.0f));
    this->texIndex += 6 * 5;

    // Right Window
    this->housesFlats->addPoly04(windowWidth, windowHeight, glm::vec3(coords.x + (static_cast<float>((houseLength) / 2.0f) - houseFrontWallWidthRight - static_cast<float>(houseDoorFrameWidth / 4.0f)), coords.y + (houseWindowUnderhangHeight + static_cast<float>(windowHeight / 2.0f)), coords.z + static_cast<float>(houseWidth / 2.0f)), glm::vec3(00.0f, 90.0f, 00.0f));
    this->housesFlats->addPoly04(windowWidth, windowHeight, glm::vec3(coords.x + (static_cast<float>((houseLength) / 2.0f) - houseFrontWallWidthRight - static_cast<float>(houseDoorFrameWidth / 4.0f)), coords.y + (houseWindowUnderhangHeight + static_cast<float>(windowHeight / 2.0f)), coords.z + (static_cast<float>(houseWidth / 2.0f) - windowThickness)), glm::vec3(00.0f, 270.0f, 00.0f));
    this->housesFlats->addPoly04(windowThickness, windowHeight, glm::vec3(coords.x + (static_cast<float>((houseLength - houseWindowWidth + windowGap) / 2.0f) - houseFrontWallWidthRight), coords.y + (houseWindowUnderhangHeight + static_cast<float>(windowHeight / 2.0f)), coords.z + static_cast<float>((houseWidth - windowThickness) / 2.0f)), glm::vec3(00.0f, 00.0f, 00.0f));
    this->housesFlats->addPoly04(windowThickness, windowHeight, glm::vec3(coords.x + (static_cast<float>((houseLength - windowGap) / 2.0f) - houseFrontWallWidthRight), coords.y + (houseWindowUnderhangHeight + static_cast<float>(windowHeight / 2.0f)), coords.z + static_cast<float>((houseWidth - windowThickness) / 2.0f)), glm::vec3(00.0f, 180.0f, 00.0f));
    this->housesFlats->addPoly04(windowThickness, windowWidth, glm::vec3(coords.x + (static_cast<float>((houseLength) / 2.0f) - houseFrontWallWidthRight - static_cast<float>(houseDoorFrameWidth / 4.0f)), coords.y + (houseWindowUnderhangHeight + windowHeight), coords.z + static_cast<float>((houseWidth - windowThickness) / 2.0f)), glm::vec3(00.0f, 00.0f, 270.0f));
    this->texIndex += 6 * 5;
}

void Houses::endConstructingHouses()
{
    this->housesFlats->endConstructingVertices();
}

void Houses::endInitialisation()
{
    this->housesFlats->endInitialisation();
}
