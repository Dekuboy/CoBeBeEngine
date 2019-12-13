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
		static std::shared_ptr<Context> initialize();

		std::shared_ptr<Texture> createTexture(std::string path);
		std::shared_ptr<ShaderProgram> createShader(std::string vert, std::string frag);
		std::shared_ptr<VertexBuffer> createBuffer();
		std::shared_ptr<VertexArray> createMesh(std::string path);
		std::shared_ptr<RenderTexture> createRenderTexture(int width, int height);
		std::shared_ptr<DepthBuffer> createDepthBuffer(int width, int height);

	private:
		std::weak_ptr<Context> m_self;
	};
}