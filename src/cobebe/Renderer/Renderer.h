#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <cobebe/Core/Component.h>
#include <string>

namespace cobebe
{
	class Camera;
	class Transform;
	class Mesh;
	class Texture;
	class Shader;

	/**
	* Displays an Entity to the screen via loaded assets
	*/
	class Renderer : public Component
	{
	public:
		void onInit();
		/**
		* \brief Stores Camera that Renderer draws to if required
		*/
		void setCamera(std::shared_ptr<Camera> _camera);
		/**
		* \brief Sets Mesh for Renderer to draw
		*/
		void setMesh(std::shared_ptr<Mesh> _mesh);
		/**
		* \brief Sets Mesh for Renderer to draw
		*/
		void setMesh(std::string _path);
		/**
		* \brief Sets Texture for Renderer to apply to Mesh
		*/
		void setTexture(std::shared_ptr<Texture> _texture);
		/**
		* \brief Sets Texture for Renderer to apply to Mesh
		*/
		void setTexture(std::string _path);
		/**
		* \brief Sets Shader for Renderer to draw with
		*/
		void setShader(std::shared_ptr<Shader> _shader);
		/**
		* \brief Sets Shader for Renderer to draw with
		*/
		void setShader(std::string _path);

	private:
		std::shared_ptr<Camera> m_camera; /// Stores Camera to draw to when set
		std::weak_ptr<Transform> m_transform; /// Pointer to Transform component
		std::shared_ptr<Mesh> m_mesh; /// Loaded Mesh to draw
		std::shared_ptr<Texture> m_texture; /// Loaded Texture to apply
		std::shared_ptr<Shader> m_shader; /// Loaded Shader to draw with

		void onDisplay();
	};
}