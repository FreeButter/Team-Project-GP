// This include
#include "pch.h"
#include "SoundController.h"

SoundController::SoundController()
{

	if (FMOD::System_Create(&m_pSystem) != FMOD_OK)
	{
		// Report Error
		//LogManager::GetInstance().Log("FMOD Init Fail!");
		return;
	}

	int driverCount = 0;
	m_pSystem->getNumDrivers(&driverCount);

	if (driverCount == 0)
	{
		// Report Error
		//LogManager::GetInstance().Log("FMOD driver Init Fail!");
		return;
	}

	// Initialize our Instance with 36 Channels
	m_pSystem->init(36, FMOD_INIT_NORMAL, 0);
}


void
SoundController::createSound(SoundClass *pSound, const char* pFile)
{
	m_pSystem->createSound(pFile, FMOD_DEFAULT, 0, pSound);
}

void
SoundController::playSound(SoundClass pSound, bool bLoop)
{

	if (!bLoop)
		pSound->setMode(FMOD_LOOP_OFF);
	else
	{
		pSound->setMode(FMOD_LOOP_NORMAL);
		pSound->setLoopCount(-1);
	}

	// might need a channel for the last args
	m_pSystem->playSound(pSound, 0, false, 0);
}

void
SoundController::releaseSound(SoundClass pSound)
{
	pSound->release();
}