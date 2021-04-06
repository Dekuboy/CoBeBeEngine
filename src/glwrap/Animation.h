#ifndef _GLWRAP_ANIMATION
#define _GLWRAP_ANIMATION
#include <vector>
#include <string>

namespace glwrap
{
	class Context;

	class Animation
	{
	public:
		/**
		* \brief Check if Animation is enabled
		*/
		bool getEnabled();
		/**
		* \brief Retrieve Animation name
		*/
		std::string getName();
		/**
		* \brief Set Animation to repeat
		*/
		void setRepeating(bool _switch);
		/**
		* \brief Set Animation to apply when base model is drawn
		*/
		void setEnabled(bool _switch);
		/**
		* \brief Set Animation name to input value
		*/
		void setName(std::string _name);
		/**
		* \brief Get current frame number in use
		*/
		int getCurrentFrame();
		/**
		* \brief Get current frame number in use
		*/
		double getTrueCurrentFrame();
		/**
		* \brief Get max frames of animation
		*/
		virtual int getMaxFrames();
		/**
		* \brief Move frame of animation forward by _deltaTime
		*/
		virtual void nextFrame(float _deltaTime);
		/**
		* \brief Set frame to input value
		*/
		virtual void setCurrentFrame(double _currentFrame);

	protected:
		friend class Context;

		std::string m_name; //!< Name of animation
		double m_time; //!< Current frame of animation
		bool m_enabled; //!< Is animation set to play when the model is drawn
		bool m_repeating; //!< Does the animation repeat once it has finished
		std::weak_ptr<Context> m_context; //!< Pointer to glwrap context

	};
}
#endif