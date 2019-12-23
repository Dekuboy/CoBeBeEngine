#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <cobebe/Core/Component.h>

namespace cobebe
{
	class Camera;
	class Transform;
	class Mesh;
	class Texture;
	class Shader;

	class Renderer : public Component
	{
	public:
		void onInit();
		void setCamera(std::shared_ptr<Camera> _camera);
		void setMesh(std::shared_ptr<Mesh> _mesh);
		void setTexture(std::shared_ptr<Texture> _texture);
		void setShader(std::shared_ptr<Shader> _shader);

	private:
		std::shared_ptr<Camera> m_camera;
		std::weak_ptr<Transform> m_transform;
		std::shared_ptr<Mesh> m_mesh;
		std::shared_ptr<Texture> m_texture;
		std::shared_ptr<Shader> m_shader;

		void onDisplay();
	};
}