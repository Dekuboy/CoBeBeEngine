#include <glm/glm.hpp>
#include <vector>
#include <GL/glew.h>
#include <memory>

namespace glwrap
{
	class Context;

	class VertexBuffer
	{
	public:
		VertexBuffer();

		void add(glm::vec2 _value);
		void add(glm::vec3 _value);
		void add(glm::vec4 _value);

		int getComponents();
		int getDataSize();
		GLuint getId();

	private:
		friend class Context;

		GLuint m_id;
		int m_components;
		std::vector <GLfloat> m_data;
		bool m_dirty;
		std::weak_ptr<Context> m_context;

	};
}