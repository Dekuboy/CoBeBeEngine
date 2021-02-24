#include <memory>
#include <string>

namespace glwrap
{
	class VertexBuffer;
	class VertexArray;
	class ObjPart;
	class ObjAnimation;
	class Texture;
	class RenderTexture;
	class GBuffer;
	class DepthBuffer;
	class ShaderProgram;
	class ObjMtlModel;

	class Context
	{
	public:
		static std::shared_ptr<Context> initialise();

		std::shared_ptr<Texture> createTexture(std::string _path);
		std::shared_ptr<ShaderProgram> createShader(std::string _path);
		std::shared_ptr<VertexBuffer> createBuffer();
		std::shared_ptr<VertexArray> createMesh();
		std::shared_ptr<VertexArray> createMesh(std::string _path);
		std::shared_ptr<VertexArray> createMesh(std::string _path, bool _calcTanBitan);
		std::shared_ptr<ObjMtlModel> createObjMtlMesh(std::string _path);
		std::shared_ptr<ObjMtlModel> createObjMtlMesh(std::string _path, bool _calcTanBitan);
		std::shared_ptr<ObjPart> createPart(std::shared_ptr<VertexArray> _mesh, std::string _name);
		std::shared_ptr<ObjAnimation> createAnimation(std::shared_ptr<VertexArray> _model);
		std::shared_ptr<ObjAnimation> createAnimation(std::shared_ptr<VertexArray> _model, std::string _path);
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