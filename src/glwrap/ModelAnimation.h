#include <glm/glm.hpp>

#include <vector>
#include <string>

namespace gltfparse
{
	class Animation;
}

namespace glwrap
{
	class Context;

	struct ModelTransform
	{
		~ModelTransform();

		glm::vec3* m_translate;
		glm::vec3* m_scale;
		glm::vec4* m_quat;
		glm::mat4* m_matrix;
	};

	class ModelAnimation
	{
	public:
		ModelAnimation(gltfparse::Animation& _animationValues);

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
		* \brief Get interpolated frame between two keyframes
		*/
		void getInterpolatedPosition(ModelTransform& _target, double _time);
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
		int getMaxFrames();
		/**
		* \brief Move frame of animation forward by _deltaTime
		*/
		void nextFrame(float _deltaTime);
		/**
		* \brief Set frame to input value
		*/
		void setCurrentFrame(double _currentFrame);

	private:
		std::string m_name; //!< Name of animation
		double m_frame; //!< Current frame of animation
		bool m_enabled; //!< Is animation set to play when the model is drawn
		bool m_repeating; //!< Does the animation repeat once it has finished
		std::vector<ModelTransform> m_frames; //!< Information on the frames of animation
		ModelTransform m_mergeFrame; //!< Interpolated frame at current animation time
		std::weak_ptr<ModelAnimation> m_self; //!< Pointer to self to place inside ObjFrame
		std::weak_ptr<Context> m_context; //!< Pointer to glwrap context

	};
}