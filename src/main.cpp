#include <stdio.h>
#include <iostream>
#include <glm/glm.hpp>
#include "../wolf/wolf.h"
#include "../samplefw/SampleRunner.h"

#include "sampleCityscape.h"
#include "sampleCity.h"

class Week2 : public wolf::App
{
public:
    Week2() : wolf::App("Week 4")
    {
        m_sampleRunner.addSample(new SampleCityscape(this));
        m_sampleRunner.addSample(new SampleCity(this));
    }

    ~Week2()
    {
    }

    void update(float dt) override
    {

        if (isKeyDown('p'))
        {
            m_lastDown = true;
        }
        else if (m_lastDown)
        {
            m_lastDown = false;
            m_sampleRunner.nextSample();
        }

        m_sampleRunner.update(dt);
    }

    void render() override
    {
        m_sampleRunner.render(m_width, m_height);
    }

private:
    bool m_lastDown = false;
    SampleRunner m_sampleRunner;
};

int main(int, char **)
{
    Week2 week2;
    week2.run();
}