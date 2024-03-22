#pragma once
#include <iostream>
#include "../wolf/wolf.h"
#include "../samplefw/FirstPersonCamera.h"
#include "../samplefw/Sample.h"
#include "city.h"
#include "lighting.h"

class SampleCity : public Sample
{
public:
    SampleCity(wolf::App *pApp) : Sample(pApp, "SampleCity")
    {
    }

    virtual ~SampleCity();

    void init() override;
    void update(float dt) override;
    void render(int width, int height) override;

private:
    const int NUM_POINTLIGHTS = 1;
    double counter = 0.0f;
    wolf::FrameBuffer *m_pFB = nullptr;
    Lighting *lighting = nullptr;
    City *city = nullptr;
    FirstPersonCamera *m_pFPCam = nullptr;
};