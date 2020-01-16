#include <cobebe/Speaker/Speaker.h>
#include <cobebe/Core/Entity.h>
#include <cobebe/Core/Transform.h>
#include <cobebe/Core/Camera.h>
#include <cobebe/Core/Core.h>
#include <cobebe/Resources/Resources.h>
#include <cobebe/Resources/Sound.h>
#include <cobebe/Exception.h>

namespace cobebe
{
	Speaker::Speaker(const std::string _path)
	{
		m_isPlaying = false;
		m_path = _path;
	}

	Speaker::~Speaker()
	{
		alDeleteSources(1, &m_sourceId);
	}

	void Speaker::onInit()
	{
		// Generally not needed. Translate sources instead
		//alListener3f(AL_POSITION, 0.0f, 0.0f, 0.0f);

		m_soundSrc = getCore()->loadAsset<Sound>(m_path);

		/*
		* Create OpenAL sound source
		*/
		m_sourceId = 0;
		alGenSources(1, &m_sourceId);

		m_transform = getTransform();
		glm::vec3 pos = m_transform.lock()->m_position;
		std::shared_ptr<Camera> cam = getCore()->getCurrentCamera();
		glm::vec4 res = cam->getView() * glm::vec4(pos, 1.0f);
		alSource3f(m_sourceId, AL_POSITION, res.x, res.y, res.z);

		alSource3f(m_sourceId, AL_POSITION, 0.0f, 0.0f, 0.0f);
		alSourcei(m_sourceId, AL_BUFFER, m_soundSrc->m_bufferId);
	}

	void Speaker::onTick()
	{
		if (!m_isPlaying)
		{
			alSourcePlay(m_sourceId);
			m_isPlaying = true;
		}

		ALint state = 0;
		alGetSourcei(m_sourceId, AL_SOURCE_STATE, &state);

		if (state == AL_STOPPED)
		{
			m_isPlaying = false;
			m_kill = true;
		}
		else
		{
			glm::vec3 pos = m_transform.lock()->m_position;
			std::shared_ptr<Camera> cam = getCore()->getCurrentCamera();
			glm::vec4 res = cam->getView() * glm::vec4(pos, 1.0f);
			alSource3f(m_sourceId, AL_POSITION, res.x, res.y, res.z);
		}
	}
}