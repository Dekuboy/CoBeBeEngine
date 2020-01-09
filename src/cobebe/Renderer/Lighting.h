#include <glwrap/glwrap.h>
#include <list>
#include <memory>

namespace cobebe
{
	class PointLight;
	class Shader;
	class Camera;
	class Core;

	struct ShadowModel
	{
		std::weak_ptr<glwrap::VertexArray> m_mesh;
		glm::mat4 m_model;
	};

	class Lighting
	{
	public:
		glm::vec3 getGlobalLightPos();
		glm::vec3 getGlobalLightDir();
		void setGlobalLightDir(glm::vec3 _lightDir);
		glm::vec3 getGlobalLightCol();
		void setGlobalLightCol(glm::vec3 _lightCol);
		glm::vec3 getGlobalLightEmissive();
		void setGlobalLightEmissive(glm::vec3 _lightEmissive);
		glm::vec3 getGlobalLightAmbient();
		void setGlobalLightAmbient(glm::vec3 _lightAmbient);

		glm::mat4 getGlobalLightSpace();

		int getPointLightRCount();
		std::vector<std::shared_ptr<glwrap::DepthCube>> getDepthCubes();
		std::vector<glm::vec3> getPointPositions();
		std::vector<glm::vec3> getPointColours();
		std::vector<float> getFarPlanes();

		std::shared_ptr<PointLight> addPointLight(glm::vec3 _position,
			glm::vec3 _colour, float _radius);
		std::list<std::shared_ptr<PointLight>> getPointLights();

		void setDepthBuffer(std::shared_ptr<Shader> _shadowShader);

		void draw(std::shared_ptr<glwrap::VertexArray> _meshInternal,
			glm::mat4 _modelMat);

	private:
		friend class Core;

		glm::mat4 m_globalLightSpace;
		glm::vec3 m_globalLightPos;
		glm::vec3 m_globalLightDir;
		glm::vec3 m_globalLightCol;
		glm::vec3 m_globalLightEmissive;
		glm::vec3 m_globalLightAmbient;

		float m_globalLightRenderDistance;

		std::shared_ptr<Shader> m_depthShader;
		std::shared_ptr<glwrap::DepthBuffer> m_depthMap;

		std::shared_ptr<Shader> m_cubeShader;
		std::list<std::shared_ptr<PointLight>> m_pointLights;
		int m_maxPointLights;
		std::vector<std::shared_ptr<glwrap::DepthCube>> m_depthCubes;
		std::vector<glm::vec3> m_pointLightPositions;
		std::vector<glm::vec3> m_pointColours;
		std::vector<float> m_farPlanes;

		std::list<ShadowModel> m_shadowModels;

		std::weak_ptr<Core> m_core;

		void setGlobalLightPos(std::shared_ptr<Camera> _camera);

		void clear();
		void onInit();
		void drawLighting();
	};
}