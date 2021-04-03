#include <glwrap/Animation.h>
#include <glm/glm.hpp>

namespace gltfparse
{
	class AniParse;
}

namespace glwrap
{
	class Context;

	struct ModelTransform
	{
		ModelTransform();

		char m_interpolate[4];
		glm::vec3 m_translate;
		glm::vec3 m_scale;
		glm::vec4 m_quat;
		glm::vec4 m_weights;
	};

	class ModelAnimation : public Animation
	{
	public:
		ModelAnimation(gltfparse::AniParse& _animationValues);

		/**
		* \brief Get interpolated frame between two keyframes
		*/
		void getInterpolatedPosition(ModelTransform& _target, double _time);
		/**
		* \brief Get max frames of animation
		*/
		int getMaxFrames();
		/**
		* \brief Move frame of animation forward by _deltaTime
		*/
		void nextFrame(float _deltaTime);

	private:
		std::vector<ModelTransform> m_frames; //!< Information on the frames of animation
		ModelTransform m_mergeFrame; //!< Interpolated frame at current animation time

	};
}