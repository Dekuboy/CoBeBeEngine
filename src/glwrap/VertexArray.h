#include <GL/glew.h>
#include <glm/glm.hpp>

#include <vector>
#include <string>
namespace glwrap
{
	class Context;
	class VertexBuffer;

	class VertexArray
	{
	public:
		VertexArray();
		VertexArray(std::string _path);
		void setBuffer(std::string _attribute, std::shared_ptr<VertexBuffer> _buffer);
		int getVertexCount();
		GLuint getId();

	private:
		friend class Context;

		GLuint m_id;
		bool m_dirty;
		std::vector<std::shared_ptr<VertexBuffer>> m_buffers;
		std::weak_ptr<Context> m_context;

		void splitStringWhitespace(std::string& _input, std::vector<std::string>& _output);
		void splitString(std::string& _input, char _splitter, std::vector<std::string>& _output);

	};
}
