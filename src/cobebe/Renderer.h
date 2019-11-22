#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <rend/rend.h>
#include "Component.h"

namespace cobebe
{
	class Mesh;
	class Material;

	class Renderer : public Component
	{
	public:
		void onInit();
		void setMesh(std::weak_ptr<Mesh> _mesh);
		std::shared_ptr<Mesh> getMesh();
		std::shared_ptr<Material> getMaterial();

	private:
		std::weak_ptr<Mesh> m_mesh;
		std::shared_ptr<Material> m_material;

		void onDisplay();
	};
}