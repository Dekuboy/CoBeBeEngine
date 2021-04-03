#include "Bloom.h"

void Bloom::blur()
{
	std::shared_ptr<glwrap::ShaderProgram> shader = m_lightKeyShader->getInternal();
	std::shared_ptr<glwrap::Texture> texture;
	m_camera->setRtUniform("in_Texture", shader);
	shader->draw(m_lightKeyRt);

	shader = m_blurShader->getInternal();
	texture = m_lightKeyRt;
	shader->setUniform("in_Texture", texture);
	shader->draw(m_blurRt);

	for (int i = 0; i < 2; i++)
	{
		texture = m_blurRt;
		shader->setUniform("in_Texture", texture);
		shader->draw(m_blur2Rt);

		texture = m_blur2Rt;
		shader->setUniform("in_Texture", texture);
		shader->draw(m_blurRt);
	}

	shader = m_mergeShader->getInternal();
	m_camera->setRtUniform("in_TextureA", shader);
	texture = m_blurRt;
	shader->setUniform("in_TextureB", texture);
	shader->draw(m_mergeRt);

	texture = m_mergeRt;
	m_nullShader->setUniform("in_Texture", texture);

	m_nullShader->draw();
}

void Bloom::onInit()
{
	std::shared_ptr<cobebe::Core> core = getCore();
	m_lightKeyShader = core->loadAsset<cobebe::Shader>("shaders\\lightkeypass.shad");
	m_blurShader = core->loadAsset<cobebe::Shader>("shaders\\blur.shad");
	m_mergeShader = core->loadAsset<cobebe::Shader>("shaders\\mergepass.shad");
	m_nullShader = getCore()->getNullPassShader();

	std::shared_ptr<cobebe::Environment> envi = getEnvironment();

	int width = envi->getWidth();
	int height = envi->getHeight();

	m_nullShader->setViewport(glm::vec4(0, 0,
		width, height));

	std::shared_ptr<glwrap::Context> context = core->getGLContext();

	m_lightKeyRt = context->createRenderTexture(width, height);
	m_blurRt = context->createRenderTexture(width, height);
	m_blur2Rt = context->createRenderTexture(width, height);
	m_mergeRt = context->createRenderTexture(width, height);

	m_camera = getCore()->getCurrentCamera();
}

void Bloom::onPostDisplay()
{
	blur();
}