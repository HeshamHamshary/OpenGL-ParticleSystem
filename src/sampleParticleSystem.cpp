#include "sampleParticleSystem.h"
#include "../samplefw/Grid2D.h"

SampleParticleSystem::~SampleParticleSystem()
{
	printf("Destroying Particle System Sample\n");
	
	delete m_pSkybox;
	delete m_pPlane;
	delete m_pFreeRoamCamera;
	for(int i = 0; i < m_lEffects.size(); i++)
		delete m_lEffects[i];
	wolf::ProgramManager::DestroyProgram(m_pProgram);
}

void SampleParticleSystem::init()
{
    // Only init if not already done
    if(!m_pProgram)
    {
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        glEnable(GL_DEPTH_TEST);
		srand(static_cast<unsigned>(time(0)));

		m_pProgram = wolf::ProgramManager::CreateProgram("data/sampleEnvironment.vsh", "data/sampleEnvironment.fsh");

		m_pFreeRoamCamera = new FreeRoamCamera(m_pApp);
		m_pFreeRoamCamera->setPosition(glm::vec3(0.0f, 10.0f, 60.0f));

		m_pSkybox = new Skybox(m_pProgram, m_pFreeRoamCamera, m_skyboxPath);

		m_pPlane = new Plane(m_pProgram, m_groundTexPath);
		m_pPlane->setScale(200.0f);

		// Effects
		Effect* pFireEffect = new Effect(m_sFirePath);
		Effect* pLightEffect = new Effect(m_sForceFieldPath);
		Effect* pExplosionEffect = new Effect(m_sExplosionPath);
		Effect* pRainEffect = new Effect(m_sRainPath);
		m_lEffects.push_back(pFireEffect);
		m_lEffects.push_back(pLightEffect);
		m_lEffects.push_back(pExplosionEffect);
		m_lEffects.push_back(pRainEffect);
		m_pCurEffect = m_lEffects[m_iEffectIndex];
	}
	
    printf("Successfully initialized Particle System Sample\n");
}

void SampleParticleSystem::update(float dt) 
{
	m_pFreeRoamCamera->update(dt);
	m_pSkybox->update(dt);
	m_pCurEffect->update(dt);
	
	// Switch Effects
	m_bCurrentKeyDown = m_pApp->isKeyDown(N);
	if (m_bCurrentKeyDown && !m_bLastNKeyDown)
	{
		m_pCurEffect = m_lEffects[m_iEffectIndex = (m_iEffectIndex + 1) % m_lEffects.size()];
	}
	m_bLastNKeyDown = m_bCurrentKeyDown;

	// Pause Current Effect
	m_bCurrentKeyDown = m_pApp->isKeyDown(P);
	if (m_bCurrentKeyDown && !m_bLastPKeyDown)
	{
		if(m_pCurEffect->isPaused())
			m_pCurEffect->start();
		else
			m_pCurEffect->pause();
	}
	m_bLastPKeyDown = m_bCurrentKeyDown;
	

	// Dynamically move sun around city
	m_sunAngle += dt * m_sunSpeed;
	float sunX = 375.0f * cos(m_sunAngle), sunY = 375.0f * sin(m_sunAngle);
	m_sunDirection = glm::vec3(sunX, sunY, 125.0f);
}

void SampleParticleSystem::render(int width, int height)
{	
	glClearColor(0.3f, 0.3f, 0.3f, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::mat4 mProj = m_pFreeRoamCamera->getProjMatrix(width, height);
	glm::mat4 mView = m_pFreeRoamCamera->getViewMatrix();
	glm::mat4 mWorld = glm::mat4(1.0f);
	
	m_pProgram->SetUniform("u_lightDir", m_sunDirection);

	// Render all objects
	m_pSkybox->render(mProj,mView,width,height);
	m_pPlane->render(mProj,mView,width,height);
	m_pCurEffect->render(mProj,mView);
}