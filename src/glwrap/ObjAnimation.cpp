#include <glwrap/ObjAnimation.h>
#include <glwrap/ObjFrame.h>
#include <glwrap/VertexArray.h>
#include <glwrap/ObjPart.h>
#include <glwrap/FileManager.h>
#include <fstream>

namespace glwrap
{
	ObjAnimation::ObjAnimation(std::shared_ptr<VertexArray> _model)
	{
		this->m_model = _model;
	}

	ObjAnimation::~ObjAnimation()
	{

	}

	void ObjAnimation::parse(std::string _path)
	{
		std::shared_ptr<ObjAnimation> aniPtr = m_self.lock();
		if (_path == "")
		{
			m_frames.push_back(std::make_shared<ObjFrame>(aniPtr));
			m_name = "Default";
			m_frame = 0;
			m_enabled = false;
			m_repeating = true;
			m_mergeFrame.reset(new ObjFrame(m_self.lock()));
		}
		else
		{
			std::ifstream file(FileManager::returnPath(_path).c_str());
			std::string line;
			std::vector<std::string> parameters;
			std::vector<std::shared_ptr<ObjPart> > parts = m_model->getParts();
			std::shared_ptr<ObjPart> cp;
			glm::vec3 v, rotation;
			bool found = false;
			m_mergeFrame.reset(new ObjFrame(m_self.lock()));

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
						m_frames.push_back(std::make_shared<ObjFrame>(aniPtr));
					}

					if (parameters.at(0) == "t")
					{
						found = false;
						//float scale = ;

						for (int partIndex = 0; partIndex < parts.size(); partIndex++)
						{
							cp = parts.at(partIndex);
							v.x = cp->getSize().x * (atof(parameters.at(2).c_str()) / 100.0f);
							v.y = cp->getSize().y * (atof(parameters.at(3).c_str()) / 100.0f);
							v.z = cp->getSize().z * (atof(parameters.at(4).c_str()) / 100.0f);

							rotation.x = glm::radians(atof(parameters.at(5).c_str()));
							rotation.y = glm::radians(atof(parameters.at(6).c_str()));
							rotation.z = glm::radians(atof(parameters.at(7).c_str()));

							if (parts.at(partIndex)->getName() == parameters.at(1))
							{
								m_frames.at(m_frames.size() - 1)->m_translations.push_back(
									std::make_shared<ObjTranslation>(parts.at(partIndex),
										v,
										rotation));
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

	void ObjAnimation::setRepeating(bool _switch)
	{
		m_repeating = _switch;
	}

	void ObjAnimation::setEnabled(bool _switch)
	{
		if (m_enabled != _switch)
		{
			m_frame = 0;
			m_enabled = _switch;
		}
	}

	bool ObjAnimation::getEnabled()
	{
		return m_enabled;
	}

	std::string ObjAnimation::getName()
	{
		return m_name;
	}

	void ObjAnimation::setName(std::string _name)
	{
		m_name = _name;
	}

	std::shared_ptr<ObjFrame> ObjAnimation::getFrame()
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

	std::shared_ptr<ObjFrame> ObjAnimation::getMergeFrame()
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

	int ObjAnimation::getCurrentFrame()
	{
		return m_frame;
	}

	double ObjAnimation::getTrueCurrentFrame()
	{
		return m_frame;
	}

	int ObjAnimation::getMaxFrames()
	{
		return m_frames.size();
	}

	void ObjAnimation::nextFrame(float _deltaTime)
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

	void ObjAnimation::setCurrentFrame(double _currentFrame)
	{
		m_frame = _currentFrame;
	}

	void ObjAnimation::splitString(std::string input, char splitter, std::vector<std::string>* output)
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

	void ObjAnimation::generateMergeFrame(std::shared_ptr<ObjFrame> a,
		std::shared_ptr<ObjFrame> b, double weight)
	{
		ObjFrame::copy(a, m_mergeFrame);
		ObjFrame::merge(b, m_mergeFrame, weight);
	}
}