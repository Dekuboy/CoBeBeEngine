#ifndef _COBEBE_ANIMATOR
#define _COBEBE_ANIMATOR
#include <cobebe/Core/Component.h>
#include <string>
#include <list>

namespace cobebe
{
	class Renderer;

	/**
	* \brief Stores values for applying and updating animations
	*/
	struct AnimationValues
	{
		int m_id; //!< Id of animation values are tied to
		float m_time; //!< Current time animation has been running
		bool m_repeating; //!< Determine if animation is looping
		float m_speed; //!< Multiplier of animation run speed
	};
	
	/**
	* \brief Manages animations and values tied to model
	*/
	class AnimationController : public Component
	{
	public:
		AnimationController();

		/**
		* \brief Load animation to attach to model
		*/
		virtual void loadAnimation(std::string _path) {}

		/**
		* \brief Play animation of name with input values, returns animation Id for easy access
		*/
		int playAnimation(std::string _name, bool _repeating = false, float _time = 0, float _speed = 1);
		/**
		* \brief Play animation of Id with input values
		*/
		virtual void playAnimation(int _id, bool _repeating = false, float _time = 0, float _speed = 1);
		/**
		* \brief Play animation of name with input values and cancel others, returns animation Id for easy access
		*/
		int playOnlyAnimation(std::string _name, bool _repeating = false, float _time = 0, float _speed = 1);
		/**
		* \brief Play animation of Id with input values and cancel others
		*/
		virtual void playOnlyAnimation(int _id, bool _repeating = false, float _time = 0, float _speed = 1);
		/**
		* \brief Stop animation of name, returns animation Id for easy access
		*/
		int stopAnimation(std::string _name);
		/**
		* \brief Stop animation of Id
		*/
		virtual void stopAnimation(int _id);
		/**
		* \brief Stop all animations
		*/
		void stopAllAnimations();
		/**
		* \brief Set animation of name to input time, returns animation Id for easy access
		*/
		int setAnimationTime(std::string _name, float _time);
		/**
		* \brief Set animation of Id to input time
		*/
		virtual void setAnimationTime(int _id, float _time);
		/**
		* \brief Set animation of name to input speed, returns animation Id for easy access
		*/
		int setAnimationSpeed(std::string _name, float _speed);
		/**
		* \brief Set animation of Id to input speed
		*/
		void setAnimationSpeed(int _id, float _speed);
		
		/**
		* \brief Find Id of input animation name
		*/
		virtual int checkName(std::string& _name) { return -1; }
		/**
		* \brief Increment all running animation times by input time
		*/
		void incrementAnimations(float _deltaTime);

		/**
		* \brief Set to increment all animations by environment deltaTime every frame
		*/
		void setIncrementDeltaTime(bool _switch) { m_incrementDeltaTime = _switch; }
		/**
		* \brief Applies animation values to attached model
		*/
		virtual void setToDraw() {}
		/**
		* \brief Disable animations currently playing in model
		*/
		virtual void resetModel() {}

	protected:
		friend class Renderer;

		std::list<AnimationValues> m_values; //!< List of values pertaining to model animations
		bool m_incrementDeltaTime; //!< Check if animations should update every frame with environment deltaTime

		/**
		* \brief Checks that input Id is valid
		*/
		virtual AnimationValues* checkId(int _id) { return nullptr; }

		void onTick();

	};
}

#endif