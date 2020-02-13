#include "BeatController.h"

float BeatController::getBpm()
{
	return m_bpm;
}

void BeatController::setBpm(float _bpm)
{
	m_bpm = _bpm;
	m_beatInterval = 60.0f / m_bpm;

	m_currentInterval *= m_bpp / 100.0f;
}

bool BeatController::checkBeatFrame()
{
	return m_isBeatFrame;
}

float BeatController::getBeatInterval()
{
	return m_beatInterval;
}

float BeatController::getCurrentInterval()
{
	return m_currentInterval;
}

void BeatController::resetCurrentInterval()
{
	m_currentInterval = 0;

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
	m_beatInterval = 60.0f / m_bpm;
	m_currentInterval = 0;
	m_bpp = 0;
}

void BeatController::onTick()
{
	m_currentInterval += m_environment->getDeltaTime();

	m_isBeatFrame = false;

	if (m_currentInterval > m_beatInterval)
	{
		m_currentInterval -= m_beatInterval;
		m_isBeatFrame = true;
	}

	m_bpp = 100.0f * (m_currentInterval / m_beatInterval);
}