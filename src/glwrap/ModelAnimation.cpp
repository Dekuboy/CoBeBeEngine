#include <glwrap/ModelAnimation.h>
#include <glwrap/GltfParse.h>

#include <glm/ext.hpp>

namespace glwrap
{
	ModelTransform::ModelTransform()
	{
		for (int i = 0; i < 4; i++)
		{
			m_interpolate[i] = 'n';
		}
		m_time = 0;
		m_translate = nullptr;
		m_quat = nullptr;
		m_scale = nullptr;
		m_weights = nullptr;
	}

	ModelTransform::~ModelTransform()
	{
		if (m_translate)
		{
			delete m_translate;
		}
		if (m_quat)
		{
			delete m_quat;
		}
		if (m_scale)
		{
			delete m_scale;
		}
		if (m_weights)
		{
			delete m_weights;
		}
	}

	ModelAnimation::ModelAnimation(gltfparse::AniParse& _animationValues, std::vector<gltfparse::AccessData>& _data)
	{
		ModelMovement* currentFrame = nullptr;
		ModelTransform* currentTransform;
		gltfparse::AccessData* input, *output;
		gltfparse::Channel* channel;
		gltfparse::AniSampler* sampler;
		int end = _animationValues.m_channels.size(), nodeCheck;
		for (int i = 0; i < end; i++)
		{
			channel = &_animationValues.m_channels.at(i);
			sampler = &_animationValues.m_samplers.at(channel->m_sampler);
			nodeCheck = channel->m_node;
			for (int j = 0; j < m_frames.size(); j++)
			{
				if (m_frames.at(j).m_node == nodeCheck)
				{
					currentFrame = &m_frames.at(j);
				}
			}
			if (!currentFrame)
			{
				m_frames.push_back(ModelMovement());
				currentFrame = &m_frames.back();
				currentFrame->m_node = nodeCheck;
			}
			while (nodeCheck > -1)
			{
				input = &_data.at(sampler->m_input);
				output = &_data.at(sampler->m_output);
				if (currentFrame->m_transforms.size() != input->m_float.size())
				{
					if (currentFrame->m_transforms.size() > 0)
					{
						throw std::exception();
					}
					currentFrame->m_transforms.resize(input->m_float.size());
					if (channel->m_path == 't')
					{
						for (int j = 0; j < input->m_float.size(); j++)
						{
							currentTransform = &currentFrame->m_transforms.at(j);
							currentTransform->m_time = input->m_float.at(j);
							currentTransform->m_interpolate[0] = sampler->m_interpolate;
							currentTransform->m_translate = new glm::vec3();
							currentTransform->m_translate->x = output->m_float.at(j * 3);
							currentTransform->m_translate->y = output->m_float.at(j * 3 + 1);
							currentTransform->m_translate->z = output->m_float.at(j * 3 + 2);
						}
					}
					else if (channel->m_path == 'r')
					{
						for (int j = 0; j < input->m_float.size(); j++)
						{
							currentTransform = &currentFrame->m_transforms.at(j);
							currentTransform->m_time = input->m_float.at(j);
							currentTransform->m_interpolate[1] = sampler->m_interpolate;
							currentTransform->m_quat = new glm::quat();
							currentTransform->m_quat->x = output->m_float.at(j * 4);
							currentTransform->m_quat->y = output->m_float.at(j * 4 + 1);
							currentTransform->m_quat->z = output->m_float.at(j * 4 + 2);
							currentTransform->m_quat->w = -output->m_float.at(j * 4 + 3);
						}
						*currentTransform->m_quat = glm::normalize(*currentTransform->m_quat);
					}
					//else if (channel->m_path == 's')
					//{
					//	for (int j = 0; j < input->m_float.size(); j++)
					//	{
					//		currentTransform = &currentFrame->m_transforms.at(j);
					//		currentTransform->m_time = input->m_float.at(j);
					//		currentTransform->m_interpolate[2] = sampler->m_interpolate;
					//		currentTransform->m_scale = new glm::vec3();
					//		currentTransform->m_scale->x = output->m_float.at(j * 3);
					//		currentTransform->m_scale->y = output->m_float.at(j * 3 + 1);
					//		currentTransform->m_scale->z = output->m_float.at(j * 3 + 2);
					//	}
					//}
					if (currentTransform)
					{
						if (currentTransform->m_time > m_totalTime)
						{
							m_totalTime = currentTransform->m_time;
						}
					}
				}
				else
				{
					if (channel->m_path == 't')
					{
						for (int j = 0; j < input->m_float.size(); j++)
						{
							currentTransform = &currentFrame->m_transforms.at(j);
							currentTransform->m_interpolate[0] = sampler->m_interpolate;
							currentTransform->m_translate = new glm::vec3();
							currentTransform->m_translate->x = output->m_float.at(j * 3);
							currentTransform->m_translate->y = output->m_float.at(j * 3 + 1);
							currentTransform->m_translate->z = output->m_float.at(j * 3 + 2);
						}
					}
					else if (channel->m_path == 'r')
					{
						for (int j = 0; j < input->m_float.size(); j++)
						{
							currentTransform = &currentFrame->m_transforms.at(j);
							currentTransform->m_interpolate[1] = sampler->m_interpolate;
							currentTransform->m_quat = new glm::quat();
							currentTransform->m_quat->x = output->m_float.at(j * 4);
							currentTransform->m_quat->y = output->m_float.at(j * 4 + 1);
							currentTransform->m_quat->z = output->m_float.at(j * 4 + 2);
							currentTransform->m_quat->w = -output->m_float.at(j * 4 + 3);
						}
						*currentTransform->m_quat = glm::normalize(*currentTransform->m_quat);
					}
					//else if (channel->m_path == 's')
					//{
					//	for (int j = 0; j < input->m_float.size(); j++)
					//	{
					//		currentTransform = &currentFrame->m_transforms.at(j);
					//		currentTransform->m_interpolate[2] = sampler->m_interpolate;
					//		currentTransform->m_scale = new glm::vec3();
					//		currentTransform->m_scale->x = output->m_float.at(j * 3);
					//		currentTransform->m_scale->y = output->m_float.at(j * 3 + 1);
					//		currentTransform->m_scale->z = output->m_float.at(j * 3 + 2);
					//	}
					//}
				}
				if (i + 1 < end)
				{
					if (_animationValues.m_channels.at(i + 1).m_node == nodeCheck)
					{
						i++;
						channel = &_animationValues.m_channels.at(i);
						sampler = &_animationValues.m_samplers.at(channel->m_sampler);
					}
					else
					{
						currentFrame = nullptr;
						nodeCheck = -1;
					}
				}
				else
				{
					currentFrame = nullptr;
					nodeCheck = -1;
				}
				currentTransform = nullptr;
			}
		}
	}

	bool ModelAnimation::getInterpolatedPosition(ModelTransform& _target, int _node)
	{
		if (m_enabled)
		{
			return getInterpolatedPosition(_target, _node, m_time);
		}
		return false;
	}

	bool ModelAnimation::getInterpolatedPosition(ModelTransform& _target, int _node, double _time)
	{
		int frameCheck = findNodeFrame(_node);
		if (frameCheck == -1)
		{
			return false;
		}
		if (m_frames.at(frameCheck).m_transforms.size() == 0)
		{
			return false;
		}
		if (_time == 0)
		{
			if (m_frames.at(frameCheck).m_transforms.at(0).m_time == 0)
			{
				ModelTransform* copyFrom = &m_frames.at(frameCheck).m_transforms.at(0);
				if (copyFrom->m_translate)
				{
					if (!_target.m_translate)
					{
						_target.m_translate = new glm::vec3();
					}
					*_target.m_translate = *copyFrom->m_translate;
				}
				if (copyFrom->m_quat)
				{
					if (!_target.m_quat)
					{
						_target.m_quat = new glm::quat();
					}
					*_target.m_quat = *copyFrom->m_quat;
				}
				if (copyFrom->m_scale)
				{
					if (!_target.m_scale)
					{
						_target.m_scale = new glm::vec3();
					}
					*_target.m_scale = *copyFrom->m_scale;
				}
			}
			else
			{
				return false;
			}
		}
		else if (_time > m_totalTime)
		{
			if (m_repeating)
			{
				int diff = _time / m_totalTime;
				if (diff)
				{
					_time -= (float)diff * m_totalTime;
				}

				int from, to;
				std::vector<ModelTransform>* transforms = &m_frames.at(frameCheck).m_transforms;
				for (int i = 0; i < transforms->size(); i++)
				{
					if (_time < transforms->at(i).m_time)
					{
						to = i;
						if (i > 0)
						{
							from = i - 1;
						}
						else
						{
							from = transforms->size() - 1;
						}
						break;
					}
				}
				if (from == to)
				{
					ModelTransform* copyFrom = &transforms->at(to);
					if (copyFrom->m_translate)
					{
						if (!_target.m_translate)
						{
							_target.m_translate = new glm::vec3();
						}
						*_target.m_translate = *copyFrom->m_translate;
					}
					if (copyFrom->m_quat)
					{
						if (!_target.m_quat)
						{
							_target.m_quat = new glm::quat();
						}
						*_target.m_quat = *copyFrom->m_quat;
					}
					if (copyFrom->m_scale)
					{
						if (!_target.m_scale)
						{
							_target.m_scale = new glm::vec3();
						}
						*_target.m_scale = *copyFrom->m_scale;
					}
				}
				else
				{
					interpolateTransform(_target, _time, transforms->at(from), transforms->at(to));
				}
			}
			else
			{
				m_enabled = false;
				return false;
			}
		}
		else
		{
			int from = -1, to;
			std::vector<ModelTransform>* transforms = &m_frames.at(frameCheck).m_transforms;
			for (int i = 0; i < transforms->size(); i++)
			{
				if (_time < transforms->at(i).m_time)
				{
					to = i;
					if (i > 0)
					{
						from = i - 1;
					}
					break;
				}
			}
			if (from == -1)
			{
				interpolateTransform(_target, _time, _target, transforms->at(to));
			}
			else
			{
				interpolateTransform(_target, _time, transforms->at(from), transforms->at(to));
			}
		}
		return true;
	}

	int ModelAnimation::getMaxFrames()
	{
		return m_frames.size();
	}

	void ModelAnimation::nextFrame(float _deltaTime)
	{
		if (m_enabled == true)
		{
			m_time += _deltaTime;

			if (m_time >= m_totalTime)
			{
				if (m_repeating == false)
				{
					m_time = 0;
					m_enabled = false;
				}
				else
				{
					int diff = m_time / m_totalTime;
					if (diff)
					{
						m_time -= (float)diff * m_totalTime;
					}
				}
			}
		}
	}

	int ModelAnimation::findNodeFrame(int _node)
	{
		for (int i = 0; i < m_frames.size(); i++)
		{
			if (m_frames.at(i).m_node == _node)
			{
				return i;
			}
		}
		return -1;
	}

	void ModelAnimation::interpolateTransform(ModelTransform& _target, double _time, ModelTransform& _from, ModelTransform& _to)
	{
		float timeDiff = _to.m_time - _from.m_time;
		float percentile = _time - _from.m_time;
		percentile /= timeDiff;
		if (_to.m_translate)
		{
			if (!_target.m_translate)
			{
				_target.m_translate = new glm::vec3(0);
			}
			if (_from.m_translate)
			{
				interpolateVector(_target.m_translate, _from.m_translate, _to.m_translate, percentile, _to.m_interpolate[0]);
			}
			else
			{
				glm::vec3 temp(0);
				interpolateVector(_target.m_translate, &temp, _to.m_translate, percentile, _to.m_interpolate[0]);
			}
		}
		if (_to.m_quat)
		{
			if (!_target.m_quat)
			{
				_target.m_quat = new glm::quat();
			}
			if (_from.m_translate)
			{
				interpolateQuat(_target.m_quat, _from.m_quat, _to.m_quat, percentile, _to.m_interpolate[1]);
			}
			else
			{
				glm::quat temp;
				interpolateQuat(_target.m_quat, &temp, _to.m_quat, percentile, _to.m_interpolate[1]);
			}
		}
		if (_to.m_scale)
		{
			if (!_target.m_scale)
			{
				_target.m_scale = new glm::vec3(0);
			}
			if (_from.m_translate)
			{
				interpolateVector(_target.m_scale, _from.m_scale, _to.m_scale, percentile, _to.m_interpolate[2]);
			}
			else
			{
				glm::vec3 temp(0);
				interpolateVector(_target.m_scale, &temp, _to.m_scale, percentile, _to.m_interpolate[2]);
			}
		}
	}

	void ModelAnimation::interpolateVector(glm::vec3* _target, glm::vec3* _from, glm::vec3* _to, float _factor, char _method)
	{
		if (_method == 'l')
		{
			*_target = *_from + _factor * (*_to - *_from);
		}
		if (_method == 's')
		{
			*_target = *_from;
		}
		if (_method == 'c')
		{

		}
	}

	void ModelAnimation::interpolateQuat(glm::quat* _target, glm::quat* _from, glm::quat* _to, float _factor, char _method)
	{
		if (_method == 'l')
		{
			*_target = glm::slerp(*_from, *_to, _factor);
		}
		if (_method == 's')
		{
			*_target = *_from;
		}
		if (_method == 'c')
		{

		}
	}
}