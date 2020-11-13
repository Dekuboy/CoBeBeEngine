#ifndef _GLWRAP_VERTEXARRAY
#define _GLWRAP_VERTEXARRAY
#include <GL/glew.h>
#include <glm/glm.hpp>

#include <vector>
#include <string>
namespace glwrap
{
	struct Face;

	class Context;
	class VertexBuffer;
	class Part;
	class Animation;

	class VertexArray
	{
	public:
		VertexArray();
		VertexArray(std::string _path);

		virtual void parse(std::string _path);

		void setBuffer(std::string _attribute, std::shared_ptr<VertexBuffer> _buffer);
		void draw();
		void drawPart(std::string _partName);

		std::shared_ptr<Animation> addAnimation(std::string _path);
		int playAnimationOnce(std::string _name);
		void playAnimationOnce(int _index);
		int enableAnimation(std::string _name);
		void enableAnimation(int _index);
		int enableOnlyAnimation(std::string _name);
		void enableOnlyAnimation(int _index);
		int disableAnimation(std::string _name);
		void disableAnimation(int _index);
		void disableAllAnimations();

		std::vector<std::shared_ptr<Face> > getFaces();
		std::vector<std::shared_ptr<Part> > getParts();
		std::shared_ptr<Part> getPart(std::string _name);
		std::vector<std::shared_ptr<Animation> > getAnimations();

	protected:
		friend class Context;

		bool m_dirty;
		std::vector<std::shared_ptr<Face> > m_faces;
		std::vector<std::shared_ptr<Part> > m_parts;
		std::vector<std::shared_ptr<Animation> > m_animations;
		std::weak_ptr<VertexArray> m_self;
		std::weak_ptr<Context> m_context;

		void splitStringWhitespace(std::string& _input, std::vector<std::string>& _output);
		void splitString(std::string& _input, char _splitter, std::vector<std::string>& _output);

	};
}

#endif