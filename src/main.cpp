#include <stdio.h>
#include <iostream>
#include <glm/glm.hpp>
#include "../wolf/wolf.h"
#include "../samplefw/SampleRunner.h"
#include "sampleParticleSystem.h"

class ParticleSystem: public wolf::App
{
public:
    ParticleSystem() : wolf::App("Particle System")
    {
        m_sampleRunner.addSample(new SampleParticleSystem(this));
    }

    ~ParticleSystem()
    {
    }

    void update(float dt) override
    {
        if(isKeyDown(' '))
        {
            m_lastDown = true;
        }
        else if(m_lastDown)
        {
            m_sampleRunner.nextSample();
            m_lastDown = false;
        }

        m_sampleRunner.update(dt);
    }

    void render() override
    {
        m_sampleRunner.render(m_width, m_height);
    }

private:
    SampleRunner m_sampleRunner;
    bool m_lastDown = false;
};

int main(int, char**) {
    ParticleSystem particleSystem;
    particleSystem.run();
}