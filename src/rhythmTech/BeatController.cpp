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
	m_startingTime = SDL_GetTicks();

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
	m_isBeatFrame = false;
	int dTime = m_environment->getCurrentTick() - m_startingTime;

	int interval = 60000 / m_bpm;
	int beat = dTime / interval;
	m_currentInterval = dTime % interval;

	if (beat > m_beatCount)
	{
		m_beatCount = beat;
		m_isBeatFrame = true;
	}

	m_bpp = 100.0f * (float)m_currentInterval / (float)interval;
}