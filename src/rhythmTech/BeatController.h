#include <cobebe/cobebe.h>

class BeatController : public cobebe::Component
{
public:


private:
	float m_bpm;
	float m_beatInterval;

	void onInit();
	void onTick();

};