#include <cobebe/Cobebe.h>

class Bloom : public cobebe::Component
{
public:

private:
	std::shared_ptr<cobebe::Shader> m_lightKeyShader;
	std::shared_ptr<cobebe::Shader> m_blurShader;
	std::shared_ptr<cobebe::Shader> m_mergeShader;
	std::shared_ptr<glwrap::ShaderProgram> m_nullShader;

	std::shared_ptr<glwrap::RenderTexture> m_lightKeyRt;
	std::shared_ptr<glwrap::RenderTexture> m_blurRt;
	std::shared_ptr<glwrap::RenderTexture> m_blur2Rt;
	std::shared_ptr<glwrap::RenderTexture> m_mergeRt;

	std::shared_ptr<cobebe::Camera> m_camera;

	void blur();

	void onInit();
	void onPostDisplay();
};