#ifndef _COBEBE_ANIMATOR
#define _COBEBE_ANIMATOR
#include <cobebe/Core/Component.h>
#include <string>
#include <list>

namespace cobebe
{
	class Renderer;

	struct AnimationValues
	{
		int m_id;
		float m_time;
		bool m_repeating;
		float m_speed;
	};

	class AnimationController : public Component
	{
	public:
		AnimationController();

		virtual void loadAnimation(std::string _path) {}

		int playAnimation(std::string _name, bool _repeating = false, float _time = 0, float _speed = 1);
		virtual void playAnimation(int _id, bool _repeating = false, float _time = 0, float _speed = 1);
		int playOnlyAnimation(std::string _name, bool _repeating = false, float _time = 0, float _speed = 1);
		virtual void playOnlyAnimation(int _id, bool _repeating = false, float _time = 0, float _speed = 1);
		int stopAnimation(std::string _name);
		virtual void stopAnimation(int _id);
		void stopAllAnimations();
		int setAnimationTime(std::string _name, float _time);
		virtual void setAnimationTime(int _id, float _time);
		int setAnimationSpeed(std::string _name, float _speed);
		virtual void setAnimationSpeed(int _id, float _speed);

		virtual int checkName(std::string& _name) { return -1; }
		void incrementAnimations(float _deltaTime);

		void setIncrementDeltaTime(bool _switch) { m_incrementDeltaTime = _switch; }
		virtual void setToDraw() {}
		virtual void resetModel() {}

	protected:
		friend class Renderer;

		std::list<AnimationValues> m_values;
		bool m_incrementDeltaTime;

		virtual AnimationValues* checkId(int _id) { return nullptr; }

		void onTick();

	};
}

#endif