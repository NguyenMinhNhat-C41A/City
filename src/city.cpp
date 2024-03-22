#include "city.h"

City::City()
{
    // this->citySky = new Skybox();

    this->houses = new Houses();
    this->houses->beginConstructingHouses();
    this->houses->constructHouse(glm::vec3(0.0f, 0.0f, 0.0f));
    this->houses->endConstructingHouses();
    this->houses->endInitialisation();
}

City::~City()
{
    // delete this->citySky;
    // this->citySky = nullptr;

    delete this->houses;
    this->houses = nullptr;
}

void City::update(const float dt)
{
}

void City::render(const glm::mat4 &mProj, const glm::mat4 &mView)
{
    this->houses->render(mProj, mView);
}

void City::render(const glm::mat4 &mProj, const glm::mat4 &mView, const glm::vec3 &lightDiffDir, const glm::vec3 &lightDiffCol, const glm::vec3 &lightAmbCol)
{
    this->houses->render(mProj, mView, lightDiffDir, lightDiffCol, lightAmbCol);
}

void City::render(const glm::mat4 &mProj, const glm::mat4 &mView, Lighting *lighting)
{
    this->houses->render(mProj, mView, lighting);
}