#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <cobebe/Core/Component.h>

namespace cobebe
{
	class Mesh;
	class Texture;
	class Shader;

	class Renderer : public Component
	{
	public:
		void onInit();
		void setMesh(std::shared_ptr<Mesh> _mesh);
		void setTexture(std::shared_ptr<Texture> _texture);
		void setShader(std::shared_ptr<Shader> _shader);

	private:
		std::weak_ptr<Mesh> m_mesh;
		std::weak_ptr<Texture> m_texture;
		std::weak_ptr<Shader> m_shader;

		void onDisplay();
	};
}