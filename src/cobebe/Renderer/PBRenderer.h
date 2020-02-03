#include <cobebe/Renderer/Renderer.h>

namespace cobebe
{
	/**
	* \brief Displays an Entity to the screen via loaded assets with shadows
	*/
	class PBRenderer : public Renderer
	{
	public:
		/**
		* \brief Sets normal map for Renderer to apply to Mesh
		*/
		void setNormalMap(std::shared_ptr<Texture> _texture);
		/**
		* \brief Sets normal map for Renderer to apply to Mesh
		*/
		void setNormalMap(std::string _path);
		/**
		* \brief Sets metal map for Renderer to apply to Mesh
		*/
		void setMetalMap(std::shared_ptr<Texture> _texture);
		/**
		* \brief Sets metal map for Renderer to apply to Mesh
		*/
		void setMetalMap(std::string _path);
		/**
		* \brief Sets rough map for Renderer to apply to Mesh
		*/
		void setRoughMap(std::shared_ptr<Texture> _texture);
		/**
		* \brief Sets rough map for Renderer to apply to Mesh
		*/
		void setRoughMap(std::string _path);
		/**
		* \brief Sets ao map for Renderer to apply to Mesh
		*/
		void setAoMap(std::shared_ptr<Texture> _texture);
		/**
		* \brief Sets ao map for Renderer to apply to Mesh
		*/
		void setAoMap(std::string _path);

	protected:
		std::shared_ptr<Texture> m_normalMap; ///< Loaded normal map to apply
		std::shared_ptr<Texture> m_metalMap; ///< Loaded metal map to apply
		std::shared_ptr<Texture> m_roughMap; ///< Loaded rough map to apply
		std::shared_ptr<Texture> m_aoMap; ///< Loaded ambient occlusion map to apply

		virtual void onPreDisplay();
		virtual void onDisplay();

	};
}