#include <memory>
#include <string>
#include <glm/glm.hpp>

namespace glwrap
{
	class GltfModel;
	class ModelMesh;
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

		/**
		* \brief Retrieve path to Metallic Roughness map for loading
		*/
		std::string getMdetalRoughPath();
		/**
		* \brief Set Metallic Roughness map to draw with when Material is used
		*/
		void setMetalRough(std::shared_ptr<Texture> _texture);

		/**
		* \brief Retrieve path to Normal map for loading
		*/
		std::string getNormalPath();
		/**
		* \brief Set Normal map to draw with when Material is used
		*/
		void setNormal(std::shared_ptr<Texture> _texture);

		/**
		* \brief Retrieve path to Occlusion map for loading
		*/
		std::string getOcclusionPath();
		/**
		* \brief Set Occlusion map to draw with when Material is used
		*/
		void setOcclusion(std::shared_ptr<Texture> _texture);

		/**
		* \brief Retrieve path to Emissive map for loading
		*/
		std::string getEmissivePath();
		/**
		* \brief Set Emissive map to draw with when Material is used
		*/
		void setEmissive(std::shared_ptr<Texture> _texture);

	private:
		friend class GltfModel;
		friend class ModelMesh;
		friend class ObjMtlModel;
		friend class ObjPart;

		std::string m_name; //!< Name of Material

		std::string m_colourPath; //!< Path to Texture File
		std::weak_ptr<Texture> m_colourMap; //!< Texture to apply when using Material
		char m_colourAttrib; //!< Texture attribute Id in shader
		glm::vec4 m_colourFactor; //!< Texture colour scale factor

		std::string m_metalRoughPath; //!< Path to Metallic Roughness File
		std::weak_ptr<Texture> m_metalRoughMap; //!< Metallic Roughness to apply when using Material
		char m_metalRoughAttrib; //!< Metallic Roughness attribute Id in shader
		glm::vec2 m_metalRoughFactor; //!< Metallic Roughness scale factor

		std::string m_normalPath; //!< Path to Normal File
		std::weak_ptr<Texture> m_normalMap; //!< Normal to apply when using Material
		char m_normalAttrib; //!< Normal attribute Id in shader
		float m_normalFactor; //!< Normal scale factor

		std::string m_occlusionPath; //!< Path to Occlusion File
		std::weak_ptr<Texture> m_occlusionMap; //!< Occlusion to apply when using Material
		char m_occlusionAttrib; //!< Occlusion attribute Id in shader
		float m_occlusionFactor; //!< Occlusion scale factor

		std::string m_emissivePath; //!< Path to Emissive File
		std::weak_ptr<Texture> m_emissiveMap; //!< Emission to apply when using Material
		char m_emissiveAttrib; //!< Metallic Roughness attribute Id in shader
		glm::vec3 m_emissiveFactor; //!< Metallic Roughness scale factor

	};
}