#include <memory>
#include <string>

namespace glwrap
{
	class VertexBuffer;
	class VertexArray;
	class Texture;
	class RenderTexture;
	class DepthBuffer;
	class ShaderProgram;

	class Context
	{
	public:
		static std::shared_ptr<Context> initialise();

		std::shared_ptr<Texture> createTexture(std::string _path);
		std::shared_ptr<ShaderProgram> createShader(std::string _path);
		std::shared_ptr<VertexBuffer> createBuffer();
		std::shared_ptr<VertexArray> createMesh(std::string _path);
		std::shared_ptr<RenderTexture> createRenderTexture(int _width, int _height);
		std::shared_ptr<DepthBuffer> createDepthBuffer(int _width, int _height);

	private:
		std::weak_ptr<Context> m_self;

	};
}