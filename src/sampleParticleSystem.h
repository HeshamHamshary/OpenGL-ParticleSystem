#pragma once
#include "../wolf/wolf.h"
#include "../samplefw/Sample.h"
#include "../samplefw/FreeRoamCamera.h"
#include "../samplefw/Skybox.h"
#include "effect.h"
#include "plane.h"
#define N 78
#define P 80


class SampleParticleSystem: public Sample
{
public:
    SampleParticleSystem(wolf::App* pApp) : Sample(pApp,"Generating System Sample") {}
    ~SampleParticleSystem();

    void init() override;
    void update(float dt) override;
    void render(int width, int height) override;

private:

    const std::string m_skyboxPath      = "data/textures/skybox/skybox.png";
    const std::string m_groundTexPath   = "data/textures/ground/ground.png";
    wolf::Program* m_pProgram           = nullptr;

    float m_sunSpeed                    = 0.01f;
    GLfloat m_sunAngle                  = -100;
    glm::vec3 m_sunDirection            = glm::vec3(375.0f, 375.0f, 125.0f);

    Skybox* m_pSkybox                   = nullptr;
    FreeRoamCamera* m_pFreeRoamCamera   = nullptr;
    Plane* m_pPlane                     = nullptr;

    // Button
    bool m_bLastPKeyDown                = false;
    bool m_bLastNKeyDown                = false;
    bool m_bCurrentKeyDown              = false;

    // Particle System
    Effect* m_pCurEffect                = nullptr;
    int m_iEffectIndex                  = 0;
    std::string m_sFirePath             = "data/effects/fire.pfx";
    std::string m_sForceFieldPath       = "data/effects/forcefield.pfx";
    std::string m_sRainPath             = "data/effects/rain.pfx";
    std::string m_sExplosionPath        = "data/effects/explosion.pfx";
 
    std::vector<Effect*> m_lEffects;
};