#include <glwrap/Animation.h>
#include <glwrap/Frame.h>
#include <glwrap/VertexArray.h>
#include <glwrap/Part.h>
#include <glwrap/FileManager.h>
#include <fstream>

namespace glwrap
{
	Animation::Animation(std::shared_ptr<VertexArray> _model)
	{
		this->m_model = _model;
	}

	Animation::~Animation()
	{

	}

	void Animation::parse(std::string _path)
	{
		if (_path == "")
		{
			m_frames.push_back(std::make_shared<Frame>(m_self.lock()));
			m_name = "Default";
			m_frame = 0;
			m_enabled = false;
			m_repeating = true;
			m_mergeFrame.reset(new Frame(m_self.lock()));
		}
		else
		{
			std::ifstream file(FileManager::returnPath(_path).c_str());
			std::string line;
			std::vector<std::string> parameters;
			std::vector<std::shared_ptr<Part>> parts = m_model->getParts();
			bool found = false;
			m_mergeFrame.reset(new Frame(m_self.lock()));

			m_name = "";
			m_frame = 0;
			m_enabled = false;
			m_repeating = true;

			if (file.is_open() == false)
			{
				throw std::exception();
			}

			while (file.eof() == false)
			{
				getline(file, line);
				splitString(line, ' ', &parameters);

				if (parameters.size() > 0)
				{
					if (parameters.at(0) == "n")
					{
						m_name = parameters.at(1);
					}

					if (parameters.at(0) == "f")
					{
						m_frames.push_back(std::make_shared<Frame>(m_self.lock()));
					}

					if (parameters.at(0) == "t")
					{
						found = false;
						//float scale = ;

						for (int partIndex = 0; partIndex < parts.size(); partIndex++)
						{
							std::shared_ptr<Part> cp = parts.at(partIndex);
							glm::vec3 v;
							v.x = cp->getSize().x * (atof(parameters.at(2).c_str()) / 100.0f);
							v.y = cp->getSize().y * (atof(parameters.at(3).c_str()) / 100.0f);
							v.z = cp->getSize().z * (atof(parameters.at(4).c_str()) / 100.0f);

							if (parts.at(partIndex)->getName() == parameters.at(1))
							{
								m_frames.at(m_frames.size() - 1)->m_translations.push_back(
									std::make_shared<Translation>(parts.at(partIndex),
										v.x/* * scale*/,
										v.y/* * scale*/,
										v.z/* * scale*/,
										glm::radians(atof(parameters.at(5).c_str())),
										glm::radians(atof(parameters.at(6).c_str())),
										glm::radians(atof(parameters.at(7).c_str()))));
								found = true;
							}
						}

						if (found == false)
						{
							throw std::exception();
						}
					}
				}
			}
		}
	}

	void Animation::setRepeating(bool _switch)
	{
		m_repeating = _switch;
	}

	void Animation::setEnabled(bool _switch)
	{
		if (m_enabled != _switch)
		{
			m_frame = 0;
			m_enabled = _switch;
		}
	}

	bool Animation::getEnabled()
	{
		return m_enabled;
	}

	std::string Animation::getName()
	{
		return m_name;
	}

	void Animation::setName(std::string _name)
	{
		m_name = _name;
	}

	std::shared_ptr<Frame> Animation::getFrame()
	{
		if (m_frame < m_frames.size())
		{
			return m_frames.at(m_frame);
		}
		else
		{
			return m_frames.at(m_frames.size() - 1);
		}
	}

	std::shared_ptr<Frame> Animation::getMergeFrame()
	{
		double nearestFrame = (int)m_frame;
		double weight = m_frame - nearestFrame;

		if (m_frame + 1 >= m_frames.size())
		{
			generateMergeFrame(m_frames.at(m_frames.size() - 1), m_frames.at(0),
				weight);
		}
		else
		{
			generateMergeFrame(m_frames.at(nearestFrame), m_frames.at(nearestFrame + 1),
				weight);
		}

		return m_mergeFrame;
	}

	int Animation::getCurrentFrame()
	{
		return m_frame;
	}

	double Animation::getTrueCurrentFrame()
	{
		return m_frame;
	}

	int Animation::getMaxFrames()
	{
		return m_frames.size();
	}

	void Animation::nextFrame(float _deltaTime)
	{
		if (m_enabled == true)
		{
			m_frame += _deltaTime;

			if (m_frame >= m_frames.size())
			{
				if (m_repeating == true)
				{
					m_frame = 0;
				}
				else
				{
					m_enabled = false;
					m_frame = 0;
				}
			}
		}
	}

	void Animation::setCurrentFrame(double _currentFrame)
	{
		m_frame = _currentFrame;
	}

	void Animation::splitString(std::string input, char splitter, std::vector<std::string>* output)
	{
		std::string current;

		output->clear();

		for (int charIndex = 0; charIndex < input.length(); charIndex++)
		{
			if (input[charIndex] != splitter)
			{
				current += input[charIndex];
			}
			else
			{
				output->push_back(current);
				current = "";
			}
		}

		if (current.length() > 0)
		{
			output->push_back(current);
		}
	}

	void Animation::generateMergeFrame(std::shared_ptr<Frame> a,
		std::shared_ptr<Frame> b, double weight)
	{
		Frame::copy(a, m_mergeFrame);
		Frame::merge(b, m_mergeFrame, weight);
	}
}