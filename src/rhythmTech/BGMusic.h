#include <cobebe/Cobebe.h>

class BeatController;

class BGMusic : public cobebe::Component
{
public:
	BGMusic(std::shared_ptr<BeatController> _bc, std::string _path);

private:
	std::weak_ptr<BeatController> m_bc;
	std::string m_trackPath;
	std::weak_ptr<cobebe::Speaker> m_currentTrack;
	std::weak_ptr<cobebe::Transform> m_transform;

	void onInit();
	void onTick();

};