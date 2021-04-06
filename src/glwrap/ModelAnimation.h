#include <glwrap/Animation.h>
#include <glm/glm.hpp>

namespace gltfparse
{
	struct AniParse;
	struct AccessData;
}

namespace glwrap
{
	class Context;

	struct ModelTransform
	{
		ModelTransform();
		~ModelTransform();

		float m_time;
		char m_interpolate[4];
		glm::vec3* m_translate;
		glm::quat* m_quat;
		glm::vec3* m_scale;
		glm::vec4* m_weights;
	};

	struct ModelMovement
	{
		int m_node;
		std::vector<ModelTransform> m_transforms;
	};

	class ModelAnimation : public Animation
	{
	public:
		ModelAnimation(gltfparse::AniParse& _animationValues, std::vector<gltfparse::AccessData>& _data);

		/**
		* \brief Get interpolated frame between two keyframes
		*/
		void getInterpolatedPosition(ModelTransform& _target, int _node);
		/**
		* \brief Get interpolated frame between two keyframes
		*/
		void getInterpolatedPosition(ModelTransform& _target, int _node, double _time);
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
		friend class Context;

		float m_totalTime;
		std::vector<ModelMovement> m_frames; //!< Information on the frames of animation
		ModelMovement m_mergeFrame; //!< Interpolated frame at current animation time

		/**
		* \brief Find the ModelFrame that refers to input node
		*/
		int findNodeFrame(int _node);
		/**
		* \brief Perform Interpolation
		*/
		void interpolateTransform(ModelTransform& _target, double _time, ModelTransform& _from, ModelTransform& _to);

		/**
		* \brief Interpolates between two vec3 values
		*/
		void interpolateVector(glm::vec3* _target, glm::vec3* _from, glm::vec3* _to, float _factor, char _method);
		/**
		* \brief Interpolates between two quat values
		*/
		void interpolateQuat(glm::quat* _target, glm::quat* _from, glm::quat* _to, float _factor, char _method);


	};
}