#include <glm/glm.hpp>

#include <vector>
#include <string>

namespace glwrap
{
	class VertexArray;
	class ObjFrame;
	class Context;

	/**
	* \brief 
	*/
	class ObjAnimation
	{
	public:
		ObjAnimation(std::shared_ptr<VertexArray> _model);
		~ObjAnimation();

		void parse(std::string _path);

		bool getEnabled();
		std::string getName();
		void setRepeating(bool _switch);
		void setEnabled(bool _switch);
		void setName(std::string _name);

		std::shared_ptr<ObjFrame> getFrame();
		std::shared_ptr<ObjFrame> getMergeFrame();
		int getCurrentFrame();
		double getTrueCurrentFrame();
		int getMaxFrames();
		void nextFrame(float _deltaTime);
		void setCurrentFrame(double _currentFrame);

	private:
		friend class Context;

		std::shared_ptr<VertexArray> m_model;
		std::string m_name;
		double m_frame;
		bool m_enabled;
		bool m_repeating;
		std::vector<std::shared_ptr<ObjFrame> > m_frames;
		std::shared_ptr<ObjFrame> m_mergeFrame;
		std::weak_ptr<ObjAnimation> m_self;
		std::weak_ptr<Context> m_context;

		void splitString(std::string input, char splitter, 
			std::vector<std::string>* output);
		void generateMergeFrame(std::shared_ptr<ObjFrame> a, 
			std::shared_ptr<ObjFrame> b, double weight);

	};
}