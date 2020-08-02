#include <GL/glew.h>
#include <glm/glm.hpp>

#include <memory>
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

		glm::vec3 tan;
		glm::vec3 bitan;

		glm::vec2 lmca;
		glm::vec2 lmcb;
		glm::vec2 lmcc;

		float getMaxX();
		float getMinX();
		float getMaxY();
		float getMinY();
		float getMaxZ();
		float getMinZ();
	};

	class Context;
	class VertexArray;
	class VertexBuffer;

	class Part
	{
	public:
		Part(std::shared_ptr<VertexArray> _mesh, std::string _name);
		~Part();

		std::string getName();
		std::vector<std::shared_ptr<Face> > getFaces();
		void addFace(std::shared_ptr<Face> _face);

		void setBuffer(std::string _attribute, std::shared_ptr<VertexBuffer> _buffer);
		int getVertexCount();
		GLuint getId();

		void draw();

		glm::vec3 getSize();

	private:
		friend class Context;

		std::string m_name;
		GLuint m_id;

		bool m_dirty;
		std::weak_ptr<VertexArray> m_model;
		std::vector<std::shared_ptr<Face> > m_faces;
		std::vector<std::shared_ptr<VertexBuffer> > m_buffers;
		glm::mat4 m_animationUniform;

		std::weak_ptr<Part> m_self;
		std::weak_ptr<Context> m_context;

		float m_offsetX;
		float m_offsetY;
		float m_offsetZ;

		float m_maxX;
		float m_maxY;
		float m_maxZ;
		float m_minX;
		float m_minY;
		float m_minZ;

		void translate(int _undo);

	};
}