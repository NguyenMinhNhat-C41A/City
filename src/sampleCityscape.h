#pragma once
#include <iostream>
#include "../wolf/wolf.h"
#include "../samplefw/FirstPersonCamera.h"
#include "../samplefw/Sample.h"
#include "cityscape.h"
#include <Windows.h>
#include <Mmsystem.h>

#pragma comment(lib, "Winmm.lib")

class SampleCityscape : public Sample
{
public:
    SampleCityscape(wolf::App *pApp) : Sample(pApp, "City")
    {
    }

    virtual ~SampleCityscape();

    void init() override;
    void update(const float dt) override;
    void render(const int width, const int height) override;

private:
    Cityscape *cityscape;
    FirstPersonCamera *m_pFPCam = nullptr;
    int sample_dt = 0;
    bool m_lastDownR = false;
    bool m_lastDownM = false;

    void playTrack();

    void switchTracks();
};