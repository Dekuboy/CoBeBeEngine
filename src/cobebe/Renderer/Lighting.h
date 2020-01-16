#include <glwrap/glwrap.h>
#include <list>
#include <memory>

namespace cobebe
{
	class PointLight;
	class Shader;
	class Camera;
	class Core;

	/**
	* \brief Stores render variables to draw to depth maps
	*/
	struct ShadowModel
	{
		std::weak_ptr<glwrap::VertexArray> m_mesh; ///< Stores mesh to render
		glm::mat4 m_model; ///< Stores joined model matrix
	};

	/**
	* \brief Stores all variables related to lighting
	* -handles drawing and applying depth maps
	*/
	class Lighting
	{
	public:
		/**
		* \brief Retrieve global directional light position
		*/
		glm::vec3 getGlobalLightPos();
		/**
		* \brief Sets global directional light position
		*/
		void setGlobalLightPos(glm::vec3 _position);
		/**
		* \brief Retrieve global directional light direction
		*/
		glm::vec3 getGlobalLightDir();
		/**
		* \brief Sets global directional light direction
		*/
		void setGlobalLightDir(glm::vec3 _lightDir);
		/**
		* \brief Retrieves global directional light colour
		*/
		glm::vec3 getGlobalLightCol();
		/**
		* \brief Sets global directional light colour
		*/
		void setGlobalLightCol(glm::vec3 _lightCol);
		/**
		* \brief Retrieves global light emissive value
		*/
		glm::vec3 getGlobalLightEmissive();
		/**
		* \brief Sets global light emissive value
		*/
		void setGlobalLightEmissive(glm::vec3 _lightEmissive);
		/**
		* \brief Retrieves global light ambient value
		*/
		glm::vec3 getGlobalLightAmbient();
		/**
		* \brief Sets global light ambient value
		*/
		void setGlobalLightAmbient(glm::vec3 _lightAmbient);

		/**
		* \brief Retrieves light space matrix for rendering
		*/
		glm::mat4 getGlobalLightSpace();

		/**
		* \brief Sets PointLight count to input shader
		*/
		void setPointLightRCount(std::shared_ptr<Shader> _shadowShader);
		/**
		* \brief Sets DepthCubes to input shader
		*/
		void setDepthCubes(std::shared_ptr<Shader> _shadowShader);
		/**
		* \brief Sets PointLight positions to input shader
		*/
		void setPointPositions(std::shared_ptr<Shader> _shadowShader);
		/**
		* \brief Sets PointLight colours to input shader
		*/
		void setPointColours(std::shared_ptr<Shader> _shadowShader);
		/**
		* \brief Sets PointLight ranges to input shader
		*/
		void setFarPlanes(std::shared_ptr<Shader> _shadowShader);

		/**
		* \brief Adds PointLight to engine
		*/
		std::shared_ptr<PointLight> addPointLight();
		/**
		* \brief Adds PointLight to engine using parameters
		*/
		std::shared_ptr<PointLight> addPointLight(glm::vec3 _position,
			glm::vec3 _colour, float _radius);
		/**
		* \brief Retrieves PointLights
		*/
		std::list<std::shared_ptr<PointLight>> getPointLights();
		/**
		* \brief Removes input PointLight from Engine
		*/
		void removePointLight(std::shared_ptr<PointLight> _light);
		/**
		* \brief Removes all PointLight from engine
		*/
		void emptyPointLights();


		/**
		* \brief Sets directional light depth map to input shader
		*/
		void setDepthBuffer(std::shared_ptr<Shader> _shadowShader);


		/**
		* \brief Sets variables to draw to depth map
		*/
		void draw(std::shared_ptr<glwrap::VertexArray> _meshInternal,
			glm::mat4 _modelMat);

	private:
		friend class Core;

		glm::mat4 m_globalLightSpace; ///< Global directional light space matrix
		glm::vec3 m_globalLightPos; ///< Global directional light position
		glm::vec3 m_globalLightDir; ///< Global light direction
		glm::vec3 m_globalLightCol; ///< Global directional light colour
		glm::vec3 m_globalLightEmissive; ///< Global light emission
		glm::vec3 m_globalLightAmbient; ///< Global ambient light

		float m_globalLightRenderDistance; ///< Directional light depth map range

		std::shared_ptr<Shader> m_depthShader; ///< Directional light depth shader
		std::shared_ptr<glwrap::DepthBuffer> m_depthMap; ///< Directional light depth map

		std::shared_ptr<Shader> m_cubeShader; ///< PointLight depth shader
		std::list<std::shared_ptr<PointLight>> m_pointLights; ///< All PointLights available in engine
		int m_maxPointLights; ///< Max possible PointLights
		std::vector<std::shared_ptr<glwrap::DepthCube>> m_depthCubes; ///< Stored DepthCubes for applying PointLights
		std::vector<glm::vec3> m_pointLightPositions; ///< PointLight positions to pass into shader
		std::vector<glm::vec3> m_pointColours; ///< PointLight colours to pass into shader
		std::vector<float> m_farPlanes; ///< PointLight ranges to pass into shader

		std::list<ShadowModel> m_shadowModels; ///< Models ready to draw

		std::weak_ptr<Core> m_core; ///< Pointer to games Core

		/**
		* \brief Function to set directional light to optimal position
		*/
		void setGlobalLightPos(std::shared_ptr<Camera> _camera);

		/**
		* \brief Clears all depth maps
		*/
		void clear();

		/**
		* \brief Initialises variables after Core pointer set
		*/
		void onInit();

		/**
		* \brief Temporary function to draw to all depth maps before display
		*/
		void drawLighting();
	};
}