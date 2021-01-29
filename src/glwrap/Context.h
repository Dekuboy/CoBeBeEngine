#include <memory>
#include <string>

namespace glwrap
{
	class VertexBuffer;
	class VertexArray;
	class Part;
	class Animation;
	class Texture;
	class RenderTexture;
	class GBuffer;
	class DepthBuffer;
	class ShaderProgram;
	class Model;

	class Context
	{
	public:
		static std::shared_ptr<Context> initialise();

		std::shared_ptr<Texture> createTexture(std::string _path);
		std::shared_ptr<ShaderProgram> createShader(std::string _path);
		std::shared_ptr<VertexBuffer> createBuffer();
		std::shared_ptr<VertexArray> createMesh();
		std::shared_ptr<VertexArray> createMesh(std::string _path);
		std::shared_ptr<Model> createObjMtlMesh(std::string _path);
		std::shared_ptr<Part> createPart(std::shared_ptr<VertexArray> _mesh, std::string _name);
		std::shared_ptr<Animation> createAnimation(std::shared_ptr<VertexArray> _model);
		std::shared_ptr<Animation> createAnimation(std::shared_ptr<VertexArray> _model, std::string _path);
		std::shared_ptr<RenderTexture> createRenderTexture(int _width, int _height);
		std::shared_ptr<RenderTexture> createRenderTexture(int _width, int _height, int _multisamples);
		std::shared_ptr<DepthBuffer> createDepthBuffer(int _width, int _height);
		std::shared_ptr<GBuffer> createGBuffer(int _width, int _height);

		std::shared_ptr<ShaderProgram> getCurrentShader();
		void setCurrentShader(std::shared_ptr<ShaderProgram> _shader);

	private:
		std::weak_ptr<ShaderProgram> m_currentShader;

		std::weak_ptr<Context> m_self;

	};
}