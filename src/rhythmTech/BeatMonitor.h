#include <cobebe/Cobebe.h>

class BeatController;

class BeatMonitor : public cobebe::Component
{
public:
	BeatMonitor(std::shared_ptr<BeatController> _bc);

private:
	std::weak_ptr<BeatController> m_bc;

	std::weak_ptr<cobebe::ImageGUI> m_monitorBG;
	std::list<std::weak_ptr<cobebe::ImageGUI>> m_blocks;
	std::weak_ptr<cobebe::ImageGUI> m_monitorFG;

	void onInit();
	void onTick();

};