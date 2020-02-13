#include "BGMusic.h"
#include "BeatController.h"

BGMusic::BGMusic(std::shared_ptr<BeatController> _bc, std::string _path)
{
	m_bc = _bc;
	m_trackPath = _path;
}

void BGMusic::onInit()
{
	m_transform = getEntity()->getTransform();
}

void BGMusic::onTick()
{
	m_transform.lock()->m_position = getCore()->getCurrentCamera()->m_position;
	if (!(m_currentTrack.lock()))
	{
		m_bc.lock()->resetCurrentInterval();

		m_currentTrack = getEntity()->addComponent<cobebe::Speaker>(m_trackPath, true);
	}
}