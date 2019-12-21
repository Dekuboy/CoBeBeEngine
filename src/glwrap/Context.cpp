#include "Context.h"
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "Texture.h"
#include "RenderTexture.h"
#include "DepthBuffer.h"
#include "ShaderProgram.h"

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
		std::shared_ptr<ShaderProgram> rtn = std::make_shared<ShaderProgram>(_path);
		rtn->m_context = m_self;
		return rtn;
	}

	std::shared_ptr<VertexBuffer> Context::createBuffer()
	{
		std::shared_ptr<VertexBuffer> rtn = std::make_shared<VertexBuffer>();
		rtn->m_context = m_self;
		return rtn;
	}

	std::shared_ptr<VertexArray> Context::createMesh(std::string _path)
	{
		std::shared_ptr<VertexArray> rtn = std::make_shared<VertexArray>(_path);
		rtn->m_context = m_self;
		return rtn;
	}

	std::shared_ptr<RenderTexture> Context::createRenderTexture(int _width, int _height)
	{
		std::shared_ptr<RenderTexture> rtn = std::make_shared<RenderTexture>(_width, _height);
		rtn->m_context = m_self;
		return rtn;
	}

	std::shared_ptr<DepthBuffer> Context::createDepthBuffer(int _width, int _height)
	{
		std::shared_ptr<DepthBuffer> rtn = std::make_shared<DepthBuffer>(_width, _height);
		rtn->m_context = m_self;
		return rtn;
	}
}