#include <cobebe/Cobebe.h>

std::shared_ptr<cobebe::Core> App;

#if defined(__EMSCRIPTEN__)
#include <emscripten.h>
#include <emscripten/html5.h>

EM_BOOL one_iter(double time, void* userData)
{
	App->run();

	return EM_TRUE;
}
#endif

class CamController : public cobebe::Component
{
public:

private:
	glm::vec2 m_camAngle;
	glm::mat3 m_rotationMatrix;
	glm::mat3 m_xRotation;
	glm::mat3 m_yRotation;
	std::weak_ptr<cobebe::Camera> m_camera;
	std::shared_ptr<cobebe::Shader> m_fxaa;

	void rotateHorizontal(float _angle);
	void rotateVertical(float _angle);
	float ClampAngle(float _angle, float _min, float _max);

	void onInit();
	void onTick();
	void onPostDisplay();

};

//class PartCubeRenderer : public cobebe::Renderer
//{
//public:
//	void loadPartTest(std::shared_ptr<cobebe::SkinModel> _model);
//	void loadPartTest(std::shared_ptr<cobebe::WavefrontModel> _model);
//
//private:
//	std::shared_ptr<cobebe::Mesh> m_partTest;
//	int m_partTestType = -1;
//
//	void onPreDisplay();
//	void onDisplay();
//};

int main()
{
	App = cobebe::Core::initialise();
	printf("Initialise\n");
	{
		std::shared_ptr<cobebe::Entity> entity = App->addEntity();
		App->getLighting()->addPointLight(glm::vec3(-12, 2, -5), glm::vec3(0.5f), 25.0f);
		//App->getLighting()->setGlobalLightAmbient(glm::vec3(0.5f));

		std::shared_ptr<cobebe::Renderer> renderer = entity->addComponent<cobebe::Renderer>();
		//renderer->setMesh("objs\\graveyard.obj");
		//renderer->setTexture("images\\graveyard.png");
		//renderer->setWavefrontModel("speedhighway\\speed.obj");
		renderer->setGltfMesh("gltf\\speed.gltf");
		renderer->setShader("emscripten_shaders\\renderG.shad");
		renderer->setCullByPart(true);

		entity->addComponent<cobebe::StaticModelCollider>();

		//entity = App->addEntity();
		//entity->getTransform()->m_position = glm::vec3(-12.0f, 1.7f, -12.0f);
		//std::shared_ptr<cobebe::PBRenderer> pbRenderer = entity->addComponent<cobebe::PBRenderer>();
		//pbRenderer->setMesh("spaceship\\Intergalactic_Spaceship-(Wavefront).obj");
		//pbRenderer->setTexture("spaceship\\textures\\Intergalactic Spaceship_color_4.png");
		//pbRenderer->setNormalMap("spaceship\\textures\\Intergalactic Spaceship_nmap_2_Tris.png");
		//pbRenderer->setMetalMap("spaceship\\textures\\Intergalactic Spaceship_metalness.png");
		//pbRenderer->setShader("pbr_shaders\\renderG_PBR.shad");

		entity = App->addEntity();
		entity->getTransform()->m_position = glm::vec3(0.0f, 0.0f, -5.0f);
		entity->addComponent<CamController>();

		renderer = entity->addComponent<cobebe::Renderer>();
		renderer->setGltfMesh("gltf\\Character Running.gltf");
		renderer->setShader("emscripten_shaders\\renderGSkin.shad");
		std::shared_ptr<cobebe::AnimationController> anm = renderer->addGltfAnimationController();

		//renderer->setMesh("objs\\curuthers.obj");
		//renderer->setTexture("images\\curuthers_diffuse.png");
		//renderer->setShader("deferred_shaders\\renderGAni.shad");
		//std::shared_ptr<cobebe::AnimationController> anm = renderer->addObjAnimationController();
		//renderer->loadAnimation("animations\\run.anm");

		anm->playAnimation(0, true);

		entity = App->addEntity();
		entity->getTransform()->m_position = glm::vec3(0.15f, 0.90f, 0.1f);
		entity->getTransform()->m_scale = glm::vec3(0.1f, 0.05f, 1.0f);

		std::shared_ptr<cobebe::ButtonGUI> gui = entity->addComponent<cobebe::ButtonGUI>();
		gui->setTextureStatic("images\\darkgrey.png");
		gui->setTextureHighlighted("images\\white.png");
		gui->SetTexturePressed("images\\grey.png");
		gui->setInCanvas(true);

		//// ---------------------------

		//entity = App->addEntity();

		//std::shared_ptr<PartCubeRenderer> pcrenderer = entity->addComponent<PartCubeRenderer>();
		////renderer->setWavefrontModel("speedhighway\\speed.obj");
		//pcrenderer->setGltfMesh(skin);
		//skin =
		//	App->loadAsset<cobebe::SkinModel>("gltf\\speed.gltf");
		//pcrenderer->loadPartTest(skin);
		//pcrenderer->setShader("deferred_shaders\\renderG.shad");

	}

#if defined(__EMSCRIPTEN__)
	emscripten_request_animation_frame_loop(one_iter, 0);
#else
	App->run();
#endif

	return 0;
}

void CamController::rotateHorizontal(float _angle)
{
	if (_angle)
	{
		m_camAngle.x += _angle;
		m_camAngle.x = ClampAngle(m_camAngle.x, -360, 360);
		m_xRotation = glm::mat3(glm::rotate(glm::quat(), m_camAngle.x, glm::vec3(0, 1, 0)));
	}

		m_rotationMatrix = m_xRotation;
}

void CamController::rotateVertical(float _angle)
{
	if (_angle)
	{
		m_camAngle.y += _angle;
		m_camAngle.y = ClampAngle(m_camAngle.y, -90, 90);
		m_yRotation = glm::mat3(glm::rotate(glm::quat(), m_camAngle.y, glm::vec3(1, 0, 0)));
	}

		m_rotationMatrix *= m_yRotation;
}

float CamController::ClampAngle(float _angle, float _min, float _max)
{
	if (_angle > glm::radians(360.0f))
	{
		_angle -= glm::radians(360.0f);
	}
	if (_angle < glm::radians(-360.0f))
	{
		_angle += glm::radians(360.0f);
	}
	return glm::clamp(_angle, glm::radians(_min), glm::radians(_max));
}

void CamController::onInit()
{
	m_camAngle = glm::vec2(0);
	m_camera = getCore()->getCurrentCamera();
	//m_fxaa = getCore()->loadAsset<cobebe::Shader>("shaders\\fxaa.shad");
	//m_fxaa->getInternal()->setViewport(glm::vec4(0, 0,
	//	getCore()->getEnvironment()->getWidth(), getCore()->getEnvironment()->getHeight()));
}

void CamController::onTick()
{
	getCore()->getCanvas()->queryButton();
	glm::vec2 camMovement = glm::radians(-0.16f * getMouse()->getMovement());
#ifdef __EMSCRIPTEN__
	camMovement = glm::vec2(0);
#endif

	float moveX = 0, moveY = 0;
	if (getKeyboard()->isKey(cobebeInput::iKey))
	{
		moveY += 1;
	}
	if (getKeyboard()->isKey(cobebeInput::jKey))
	{
		moveX += 1;
	}
	if (getKeyboard()->isKey(cobebeInput::kKey))
	{
		moveY -= 1;
	}
	if (getKeyboard()->isKey(cobebeInput::lKey))
	{
		moveX -= 1;
	}
	if (camMovement.x || camMovement.y || moveX || moveY)
	{
		rotateHorizontal(camMovement.x + glm::radians(moveX));
		rotateVertical(camMovement.y + glm::radians(moveY));

		m_camera.lock()->m_rotation = m_rotationMatrix;
	}

	if (getKeyboard()->isKey(cobebeInput::wKey))
	{
		glm::vec3 z = m_camera.lock()->m_rotation[2];
		m_camera.lock()->m_position += -z;
	}
	if (getKeyboard()->isKey(cobebeInput::aKey))
	{
		glm::vec3 x = m_camera.lock()->m_rotation[0];
		m_camera.lock()->m_position += -x;
	}
	if (getKeyboard()->isKey(cobebeInput::sKey))
	{
		glm::vec3 z = m_camera.lock()->m_rotation[2];
		m_camera.lock()->m_position += z;
	}
	if (getKeyboard()->isKey(cobebeInput::dKey))
	{
		glm::vec3 x = m_camera.lock()->m_rotation[0];
		m_camera.lock()->m_position += x;
	}

	if (getKeyboard()->isKey(cobebeInput::eKey))
	{
		getEntity()->getComponent<cobebe::AnimationController>()->setIncrementDeltaTime(true);
	}
	else
	{
		getEntity()->getComponent<cobebe::AnimationController>()->setIncrementDeltaTime(false);
	}

	//getEntity()->getComponent<cobebe::ObjAnimationController>()->incrementAnimations(6.0 * getEnvironment()->getDeltaTime());
}

void CamController::onPostDisplay()
{
	//m_camera.lock()->setRtUniform("in_Texture", m_fxaa->getInternal());
	//m_fxaa->getInternal()->setUniform("in_FrameBufSize", glm::vec2((float)getEnvironment()->getWidth(), (float)getEnvironment()->getHeight()));
	//m_fxaa->getInternal()->draw();
}

//void PartCubeRenderer::loadPartTest(std::shared_ptr<cobebe::SkinModel> _model)
//{
//	m_partTest = _model;
//	m_partTestType = 2;
//}
//
//void PartCubeRenderer::loadPartTest(std::shared_ptr<cobebe::WavefrontModel> _model)
//{
//	m_partTest = _model;
//	m_partTestType = 1;
//}
//
//void PartCubeRenderer::onPreDisplay()
//{
//
//}
//void PartCubeRenderer::onDisplay()
//{
//	if (m_partTestType == 0 || m_partTestType == 1)
//	{
//		std::shared_ptr<cobebe::WavefrontModel> model =
//			std::dynamic_pointer_cast<cobebe::WavefrontModel>(m_partTest);
//		if (model)
//		{
//			std::vector<std::shared_ptr<glwrap::ObjPart>> partList = std::dynamic_pointer_cast<glwrap::VertexArray>(model->getInternal())->getParts();
//			std::vector<std::shared_ptr<glwrap::ObjPart>>::iterator itr = partList.begin();
//
//			for (itr; itr != partList.end(); itr++)
//			{
//				m_transform.lock()->m_position = (*itr)->getCentre();
//				m_transform.lock()->m_scale = (*itr)->getSize() / 2.0f;
//				m_transform.lock()->setModelMatrix();
//				Renderer::onDisplay();
//			}
//		}
//	}
//	else if (m_partTestType == 2)
//	{
//		std::shared_ptr<cobebe::SkinModel> model =
//			std::dynamic_pointer_cast<cobebe::SkinModel>(m_partTest);
//		if (model)
//		{
//			std::vector<std::shared_ptr<glwrap::ModelMesh>> partList = 
//				std::dynamic_pointer_cast<glwrap::GltfModel>(model->getInternal())->getMeshes();
//			std::vector<std::shared_ptr<glwrap::ModelMesh>>::iterator itr = partList.begin();
//
//			for (itr; itr != partList.end(); itr++)
//			{
//				m_transform.lock()->m_position = (*itr)->getCentre();
//				m_transform.lock()->m_scale = (*itr)->getSize() / 2.0f;
//				m_transform.lock()->setModelMatrix();
//				Renderer::onDisplay();
//			}
//		}
//	}
//}