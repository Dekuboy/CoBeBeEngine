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
	* \brief Get the interval between beats
	*/
	float getBeatInterval();
	/**
	* \brief Get the current interval between beats
	*/
	float getCurrentInterval();
	/**
	* \brief Reset the current interval
	*/
	void resetCurrentInterval();
	/**
	* \brief Get beat percentage passed
	*/
	float getBpp();

private:
	float m_bpm;
	bool m_isBeatFrame;
	float m_beatInterval;
	float m_currentInterval;
	float m_bpp;

	std::shared_ptr<cobebe::Environment> m_environment;

	void onInit();
	void onTick();

};