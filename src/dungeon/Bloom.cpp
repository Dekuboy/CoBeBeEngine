#include "Bloom.h"

void Bloom::blur()
{
	std::shared_ptr<glwrap::ShaderProgram> shader = m_lightKeyShader->getInternal();
	m_camera->setRtUniform("in_Texture", shader);
	shader->draw(m_lightKeyRt);

	shader = m_blurShader->getInternal();
	shader->setUniform("in_Texture", m_lightKeyRt);
	shader->draw(m_blurRt);

	for (int i = 0; i < 3; i++)
	{
		shader->setUniform("in_Texture", m_blurRt);
		shader->draw(m_blur2Rt);

		shader->setUniform("in_Texture", m_blur2Rt);
		shader->draw(m_blurRt);
	}

	shader = m_mergeShader->getInternal();
	m_camera->setRtUniform("in_TextureA", shader);
	shader->setUniform("in_TextureB", m_blurRt);
	shader->draw(m_mergeRt);

	m_nullShader->setUniform("in_Texture", m_mergeRt);

	m_camera->draw(m_nullShader);
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