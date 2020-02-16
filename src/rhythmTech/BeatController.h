#include <cobebe/cobebe.h>

class BeatController : public cobebe::Component
{
public:
	/**
	* \brief Get the current beats per minute
	*/
	float getBpm();
	/**
	* \brief Set the current beats per minute
	*/
	void setBpm(float _bpm);

	/**
	* \brief Check if beat passes on frame
	*/
	bool checkBeatFrame();

	/**
	* \brief Get the current interval between beats
	*/
	int getCurrentInterval();
	/**
	* \brief Reset the current interval
	*/
	void resetCurrentInterval();
	/**
	* \brief Get the total beats passed
	*/
	int getBeatCount();
	/**
	* \brief Get beat percentage passed
	*/
	float getBpp();

private:
	float m_bpm;
	bool m_isBeatFrame;
	int m_startingTime;
	int m_beatCount;
	int m_currentInterval;
	float m_bpp; ///< Beat Percentage Passed

	std::shared_ptr<cobebe::Environment> m_environment;

	void onInit();
	void onTick();

};