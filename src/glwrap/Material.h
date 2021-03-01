#include <memory>
#include <string>

namespace glwrap
{
	class ObjMtlModel;
	class ObjPart;
	class Texture;

	/**
	* Holds Texture Information for Models
	*/
	class Material
	{
	public:
		/**
		* \brief Retrieve path to Texture for loading
		*/
		std::string getTexturePath();
		/**
		* \brief Set Texture to draw with when Material is used
		*/
		void setTexture(std::shared_ptr<Texture> _texture);

	private:
		friend class ObjMtlModel;
		friend class ObjPart;

		std::string m_name; //!< Name of Material
		std::string m_mapPath; //!< Path to Texture File
		std::weak_ptr<Texture> m_textureMap; //!< Texture to apply when using Material

	};
}