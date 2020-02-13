#include "BeatController.h"

float BeatController::getBpm()
{
	return m_bpm;
}

void BeatController::setBpm(float _bpm)
{
	m_bpm = _bpm;
}

bool BeatController::checkBeatFrame()
{
	return m_isBeatFrame;
}

int BeatController::getCurrentInterval()
{
	return (int)m_currentInterval;
}

void BeatController::resetCurrentInterval()
{
	m_currentInterval = 0;
	m_startingTime = m_environment->getCurrentTick();

	m_isBeatFrame = true;

	m_bpp = 0;
}

float BeatController::getBpp()
{
	return m_bpp;
}

void BeatController::onInit()
{
	m_environment = getEnvironment();
	m_bpm = 80;
	m_currentInterval = 0;
	m_startingTime = m_environment->getCurrentTick();
	m_beatCount = 0;
	m_bpp = 0;
}

void BeatController::onTick()
{
	int dTime = m_environment->getCurrentTick() - m_startingTime;

	float interval = 60000.0f / m_bpm;

	float currentIntervalF = dTime;
}