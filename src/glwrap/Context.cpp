#include <glwrap/glwrap.h>

namespace glwrap
{
	std::shared_ptr<Context> Context::initialise()
	{
		std::shared_ptr<Context> rtn = std::make_shared<Context>();

		if (glewInit() != GLEW_OK)
		{
			throw std::exception();
		}

		rtn->m_self = rtn;

		return rtn;
	}

	std::shared_ptr<Texture> Context::createTexture(std::string _path)
	{
		std::shared_ptr<Texture> rtn = std::make_shared<Texture>(_path);
		rtn->m_context = m_self;
		return rtn;
	}

	std::shared_ptr<ShaderProgram> Context::createShader(std::string _path)
	{
		std::shared_ptr<ShaderProgram> rtn = std::make_shared<ShaderProgram>();
		rtn->m_context = m_self;
		rtn->m_self = rtn;
		rtn->parse(_path);
		return rtn;
	}

	std::shared_ptr<VertexBuffer> Context::createBuffer()
	{
		std::shared_ptr<VertexBuffer> rtn = std::make_shared<VertexBuffer>();
		rtn->m_context = m_self;
		return rtn;
	}

	std::shared_ptr<VertexArray> Context::createMesh()
	{
		std::shared_ptr<VertexArray> rtn = std::make_shared<VertexArray>();
		rtn->m_context = m_self;
		rtn->m_self = rtn;
		return rtn;
	}

	std::shared_ptr<VertexArray> Context::createMesh(std::string _path)
	{
		std::shared_ptr<VertexArray> rtn = std::make_shared<VertexArray>();
		rtn->m_context = m_self;
		rtn->m_self = rtn;
		rtn->parse(_path);
		return rtn;
	}

	std::shared_ptr<VertexArray> Context::createMesh(std::string _path, bool _calcTanBitan)
	{
		std::shared_ptr<VertexArray> rtn = std::make_shared<VertexArray>();
		rtn->m_context = m_self;
		rtn->m_self = rtn;
		rtn->parse(_path, _calcTanBitan);
		return rtn;
	}

	std::shared_ptr<ObjMtlModel> Context::createObjMtlMesh(std::string _path)
	{
		std::shared_ptr<ObjMtlModel> rtn = std::make_shared<ObjMtlModel>();
		rtn->m_context = m_self;
		rtn->m_self = rtn;
		rtn->parse(_path);
		return rtn;
	}

	std::shared_ptr<ObjMtlModel> Context::createObjMtlMesh(std::string _path, bool _calcTanBitan)
	{
		std::shared_ptr<ObjMtlModel> rtn = std::make_shared<ObjMtlModel>();
		rtn->m_context = m_self;
		rtn->m_self = rtn;
		rtn->parse(_path, _calcTanBitan);
		return rtn;
	}

	std::shared_ptr<ObjPart> Context::createPart(std::shared_ptr<VertexArray> _mesh, std::string _name)
	{
		std::shared_ptr<ObjPart> rtn = std::make_shared<ObjPart>(_mesh, _name);
		rtn->m_context = m_self;
		rtn->m_self = rtn;
		return rtn;
	}

	std::shared_ptr<ObjAnimation> Context::createAnimation(std::shared_ptr<VertexArray> _model)
	{
		std::shared_ptr<ObjAnimation> rtn = std::make_shared<ObjAnimation>(_model);
		rtn->m_context = m_self;
		rtn->m_self = rtn;
		rtn->parse("");
		return rtn;
	}

	std::shared_ptr<ObjAnimation> Context::createAnimation(std::shared_ptr<VertexArray> _model, std::string _path)
	{
		std::shared_ptr<ObjAnimation> rtn = std::make_shared<ObjAnimation>(_model);
		rtn->m_context = m_self;
		rtn->m_self = rtn;
		rtn->parse(_path);
		return rtn;
	}

	std::shared_ptr<RenderTexture> Context::createRenderTexture(int _width, int _height)
	{
		std::shared_ptr<RenderTexture> rtn = std::make_shared<RenderTexture>(_width, _height);
		rtn->m_context = m_self;
		return rtn;
	}

	std::shared_ptr<RenderTexture> Context::createRenderTexture(int _width, int _height, int _multisamples)
	{
		std::shared_ptr<RenderTexture> rtn = std::make_shared<RenderTexture>(_width, _height, _multisamples);
		rtn->m_context = m_self;
		return rtn;
	}

	std::shared_ptr<DepthBuffer> Context::createDepthBuffer(int _width, int _height)
	{
		std::shared_ptr<DepthBuffer> rtn = std::make_shared<DepthBuffer>(_width, _height);
		rtn->m_context = m_self;
		return rtn;
	}

	std::shared_ptr<DepthCube> Context::createDepthCube(int _width, int _height)
	{
		std::shared_ptr<DepthCube> rtn = std::make_shared<DepthCube>(_width, _height);
		rtn->m_context = m_self;
		return rtn;
	}

	std::shared_ptr<GBuffer> Context::createGBuffer(int _width, int _height)
	{
		std::shared_ptr<GBuffer> rtn = std::make_shared<GBuffer>(_width, _height);
		rtn->m_context = m_self;
		return rtn;
	}

	std::shared_ptr<ShaderProgram> Context::getCurrentShader()
	{
		return m_currentShader.lock();
	}

	void Context::setCurrentShader(std::shared_ptr<ShaderProgram> _shader)
	{
		if (m_currentShader.lock() != _shader)
		{
			glUseProgram(_shader->m_id);
			m_currentShader = _shader;
		}
	}
}