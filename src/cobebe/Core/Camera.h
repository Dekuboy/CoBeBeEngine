#include <memory>
#include <string>
#include <glm/glm.hpp>
#include <glwrap/glwrap.h>

namespace cobebe
{
	class Core;
	class Texture;
	class Renderer;

	class Camera
	{
	public:
		Camera();

		glm::vec3 m_position;
		glm::mat3 m_rotation;

		glm::mat4 getView();

		glm::mat4 getProjection();
		void setProjection(float _angle, float _width, float _height, float _near, float _far);

	private:
		friend class Core;
		friend class Renderer;
		bool m_isOn;
		std::shared_ptr<glwrap::RenderTexture> m_texture;

		glm::mat4 m_projection;
	};
}