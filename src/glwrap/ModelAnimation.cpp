#include <glwrap/ModelAnimation.h>
#include <glwrap/GltfParse.h>

namespace glwrap
{
	ModelTransform::ModelTransform()
	{
		for (int i = 0; i < 4; i++)
		{
			m_interpolate[i] = 'n';
		}
	}

	ModelAnimation::ModelAnimation(gltfparse::AniParse& _animationValues)
	{

	}

	void ModelAnimation::getInterpolatedPosition(ModelTransform& _target, double _time)
	{

	}

	int ModelAnimation::getMaxFrames()
	{
		return m_frames.size();
	}

	void ModelAnimation::nextFrame(float _deltaTime)
	{

	}
}