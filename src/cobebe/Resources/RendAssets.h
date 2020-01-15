#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <cobebe/Resources/Asset.h>
#include <cobebe/Resources/Resources.h>
#include <cobebe/NonCopyable.h>

namespace cobebe
{
	class Renderer;
	class Canvas;
	class Lighting;
	class Camera;

	/**
	* Stores a VertexArray to set in Renderer
	*/
	class Mesh : private NonCopyable, public Asset
	{
	public:
		std::vector<std::shared_ptr<glwrap::Face>> getFaces();

	private:
		friend class Renderer;

		std::shared_ptr<glwrap::VertexArray> m_internal; /// Pointer to OpenGL VertexArray

		void onLoad(const std::string& _path);

	};


	/**
	* Stores a Texture to set in Renderer
	*/
	class Texture : private NonCopyable, public Asset
	{
	public:

	private:
		friend class Renderer;
		friend class Canvas;

		std::shared_ptr<glwrap::Texture> m_internal; /// Pointer to OpenGL Texture

		void onLoad(const std::string& _path);

	};


	/**
	* Stores a Shader to set in Renderer
	*/
	class Shader : private NonCopyable, public Asset
	{
	public:
		void setEmissive(glm::vec3 _emissive);
		void setAmbient(glm::vec3 _ambient);
		void setLightPos(glm::vec3 _lightPos);
		void setLightDir(glm::vec3 _lightDir);
		void setLightCol(glm::vec3 _lightCol);
		void setLightSpace(glm::mat4 _lightSpace);

		void setLightSpace(std::vector<glm::mat4> _lightSpace);

		void setPointLightCount(int _count);
		void setDepthCubes(std::vector<std::shared_ptr<glwrap::DepthCube>> _depthCubes);
		void setPointLightPositions(std::vector<glm::vec3> _pointLightPositions);
		void setPointLightColours(std::vector<glm::vec3> _pointColours);
		void setFarPlanes(std::vector<float> _farPlanes);

		bool getUniformCheck();
		void setUniformCheck(bool _switch);
		bool getShadowCheck();
		void setShadowCheck(bool _switch);

		void setCam(std::shared_ptr<Camera> _camera);

		void resetChecks();

	private:
		friend class Renderer;
		friend class Canvas;
		friend class Lighting;

		std::shared_ptr<glwrap::ShaderProgram> m_internal; /// Pointer to OpenGL ShaderProgram
		bool m_uniformCheck;
		bool m_shadowCheck;

		std::shared_ptr<Camera> m_camSet;

		void onLoad(const std::string& _path);

	};
}