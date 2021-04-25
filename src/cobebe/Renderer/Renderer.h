#ifndef _COBEBE_RENDERER
#define _COBEBE_RENDERER
#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <glwrap/glwrap.h>
#include <cobebe/Core/Component.h>
#include <string>

namespace cobebeModel
{
	enum ModelType
	{
		null = -1,
		singleTexObj,
		objMtl,
		skin
	};
}

namespace cobebe
{

	class Camera;
	class Transform;
	class Mesh;
	class WavefrontModel;
	class SkinModel;
	class Texture;
	class Shader;
	class Lighting;
	class AnimationController;
	class ObjAnimationController;
	class GltfAnimationController;

	/**
	* \brief Displays an Entity to the screen via loaded assets
	*/
	class Renderer : public Component
	{
	public:
		/**
		* \brief Stores Camera that Renderer draws to if required
		*/
		void setCamera(std::shared_ptr<Camera> _camera);
		/**
		* \brief Sets Mesh for Renderer to draw
		*/
		void setWavefrontModel(std::shared_ptr<WavefrontModel> _mesh);
		/**
		* \brief Sets Mesh for Renderer to draw
		*/
		void setWavefrontModel(std::string _path);
		/**
		* \brief Sets Mesh for Renderer to draw
		*/
		void setGltfMesh(std::shared_ptr<SkinModel> _mesh);
		/**
		* \brief Sets Mesh for Renderer to draw
		*/
		void setGltfMesh(std::string _path);
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

		/**
		* \brief Set whether a models parts should individually be culled
		*/
		void setCullByPart(bool _switch);

		/**
		* \brief Returns loaded mesh
		*/
		std::shared_ptr<Mesh> getMesh();

		/**
		* \brief Adds ObjAnimationController if applicable
		*/
		std::shared_ptr<ObjAnimationController> addObjAnimationController();
		/**
		*
		*/
		void loadObjAnimation(std::string _path);

		/**
		* \brief Adds GltfAnimationController if applicable
		*/
		std::shared_ptr<GltfAnimationController> addGltfAnimationController();

	protected:
		std::shared_ptr<Camera> m_camera; //!< Stores Camera to draw to when set
		std::weak_ptr<Transform> m_transform; //!< Pointer to Transform component
		std::shared_ptr<Lighting> m_lighting; //!< Pointer to Lighting to get uniforms

		cobebeModel::ModelType m_modelType; //!< Type of Mesh/Model to draw
		std::shared_ptr<Mesh> m_mesh; //!< Loaded Mesh/Model to draw
		std::shared_ptr<Texture> m_texture; //!< Loaded Texture to apply
		std::shared_ptr<Shader> m_shader; //!< Loaded Shader to draw with
		std::shared_ptr<AnimationController> m_animationController; //!< Stores animation info

		bool m_cullByPart; //!< Culls a models individual parts -useful for large or animated objects

		/**
		* \brief Returns texture internal, useful for renderer inheritance
		*/
		std::shared_ptr<glwrap::Texture> getTextureInternal(std::shared_ptr<Texture> _texture);

		virtual void onInit();
		virtual void onTick();
		virtual void onPreDisplay();
		virtual void onDisplay();
	};
}
#endif