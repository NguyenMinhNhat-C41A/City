#include "sampleCityscape.h"

const static std::vector<std::string> tracks = {"Track1.mp3", "Track2.mp3", "Track3.mp3", "Track4.mp3"};
static int trackIndex = 0;
SampleCityscape::~SampleCityscape()
{
    delete this->cityscape;
    delete this->m_pFPCam;
    glfwSetInputMode(m_pApp->getWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

void SampleCityscape::init()
{
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);

    glfwSetInputMode(this->m_pApp->getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    this->cityscape = new Cityscape();
    this->m_pFPCam = new FirstPersonCamera(m_pApp);

    this->playTrack();
}

void SampleCityscape::update(const float dt)
{
    if (m_pApp->isKeyDown('r'))
    {
        m_lastDownR = true;
    }
    else if (m_lastDownR)
    {
        this->cityscape->regenerateCity();
        m_lastDownR = false;
    }

    if (m_pApp->isKeyDown('m'))
    {
        m_lastDownM = true;
    }
    else if (m_lastDownM)
    {
        this->switchTracks();
        m_lastDownM = false;
    }

    this->m_pFPCam->update(dt);
    this->cityscape->update(dt);
}

void SampleCityscape::render(const int width, const int height)
{
    glClearColor(0.3f, 0.3f, 0.3f, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    this->cityscape->render(this->m_pFPCam->getProjMatrix(width, height), this->m_pFPCam->getViewMatrix());
}

void SampleCityscape::playTrack()
{
    if (trackIndex >= tracks.size())
    {
        trackIndex = trackIndex % tracks.size();
    }
    std::string trackDir = "data/music/" + tracks.at(trackIndex);
    std::string commandStr = "open \"" + trackDir + "\" type mpegvideo alias mymp3";
    mciSendString(commandStr.c_str(), NULL, 0, NULL);
    mciSendString("play mymp3 repeat", NULL, 0, NULL);
}
void SampleCityscape::switchTracks()
{

    mciSendString("stop mymp3", NULL, 0, NULL);

    mciSendString("close mymp3", NULL, 0, NULL);

    trackIndex = (trackIndex + 1) % tracks.size();

    this->playTrack();
}