#include "samplecity.h"

SampleCity::~SampleCity()
{
    delete this->lighting;
    this->lighting = nullptr;

    delete this->city;
    this->city = nullptr;

    delete this->m_pFPCam;
    this->m_pFPCam = nullptr;

    wolf::BufferManager::DestroyBuffer(this->m_pFB);

    glfwSetInputMode(m_pApp->getWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

void SampleCity::init()
{
    glEnable(GL_DEPTH_TEST);
    glfwSetInputMode(this->m_pApp->getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    this->m_pFB = wolf::BufferManager::CreateFrameBuffer();
    this->m_pFB->setWindowSize(m_pApp->getScreenSize());

    this->lighting = new Lighting(NUM_POINTLIGHTS);
    this->lighting->addDiffuseLight(glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.5f, 0.5f, 0.5f));
    this->lighting->addAmbientLight(glm::vec3(0.25f, 0.25f, 0.25f));
    this->lighting->addPointLight(glm::vec3(0.0f, 0.8f, 0.5f), glm::vec3(0.5f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f), 0.2f, glm::vec3(0.2f, 0.2f, 0.2f));
    this->city = new City();
    this->m_pFPCam = new FirstPersonCamera(m_pApp);
}

void SampleCity::update(float dt)
{
    this->counter += dt;
    this->m_pFPCam->update(dt);
    this->city->update(dt);
}

void SampleCity::render(int width, int height)
{
    this->m_pFB->RenderBind();
    this->city->render(this->m_pFPCam->getProjMatrix(width, height), this->m_pFPCam->getViewMatrix(), this->lighting);
    this->m_pFB->Blit();
}
