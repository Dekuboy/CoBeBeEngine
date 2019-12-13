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
		friend class Context;
		GLuint m_id;
		bool m_dirty;
		std::vector<std::shared_ptr<VertexBuffer>> m_buffers;
		std::weak_ptr<Context> m_context;

		void splitStringWhitespace(std::string& input, std::vector<std::string>& output);
		void splitString(std::string& input, char splitter, std::vector<std::string>& output);

	public:
		VertexArray();
		VertexArray(std::string path);
		void setBuffer(std::string attribute, std::shared_ptr<VertexBuffer> buffer);
		int getVertexCount();
		GLuint getId();

	};
}
