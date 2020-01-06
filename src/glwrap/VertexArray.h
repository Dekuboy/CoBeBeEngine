#include <GL/glew.h>
#include <glm/glm.hpp>

#include <vector>
#include <string>
namespace glwrap
{
	struct Face
	{
		glm::vec3 pa;
		glm::vec3 pb;
		glm::vec3 pc;

		glm::vec2 tca;
		glm::vec2 tcb;
		glm::vec2 tcc;

		glm::vec3 na;
		glm::vec3 nb;
		glm::vec3 nc;

		glm::vec2 lmca;
		glm::vec2 lmcb;
		glm::vec2 lmcc;
	};

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
		std::vector<std::shared_ptr<Face>> getFaces();

	private:
		friend class Context;

		GLuint m_id;
		bool m_dirty;
		std::vector<std::shared_ptr<Face>> m_faces;
		std::vector<std::shared_ptr<VertexBuffer>> m_buffers;
		std::weak_ptr<Context> m_context;

		void splitStringWhitespace(std::string& _input, std::vector<std::string>& _output);
		void splitString(std::string& _input, char _splitter, std::vector<std::string>& _output);

	};
}
