#include <glm/glm.hpp>
#include <vector>
#include <GL/glew.h>
#include <memory>

namespace glwrap
{
	class Context;

	/**
	* \brief Stores info of an attribute buffer in GL
	*/
	class VertexBuffer
	{
	public:
		VertexBuffer();
		~VertexBuffer();

		/**
		* \brief Adds value to buffer
		*/
		void add(glm::vec2 _value);
		/**
		* \brief Adds value to buffer
		*/
		void add(glm::vec3 _value);
		/**
		* \brief Adds value to buffer
		*/
		void add(glm::vec4 _value);
		/**
		* \brief Adds value to buffer
		*/
		void add(glm::ivec2 _value);
		/**
		* \brief Adds value to buffer
		*/
		void add(glm::ivec3 _value);
		/**
		* \brief Adds value to buffer
		*/
		void add(glm::ivec4 _value);

		/**
		* \brief Retrieve number of components (vec length)
		*/
		int getComponents();
		/**
		* \brief Retrieve total data size
		*/
		int getDataSize();
		/**
		* \brief Retrieve GL buffer Id
		*/
		GLuint getId();

	private:
		friend class Context;

		GLuint m_id; //!< GL Id of VertexBuffer
		int m_components; //!< Vector length in VertexBuffer to keep data consistent
		std::vector <GLfloat> m_floatData; //!< Data to send to GL
		std::vector <int> m_intData; //!< Data to send to GL
		bool m_dirty; //!< If the buffer has been altered, update in GL
		bool m_isFloat; //!< True the buffer uses Glfloat values
		std::weak_ptr<Context> m_context; //!< Pointer to glwrap context

	};
}