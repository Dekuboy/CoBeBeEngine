#include <cobebe/Resources/RendAssets.h>
#include <cobebe/Core/Camera.h>

namespace cobebe
{
	std::vector<std::shared_ptr<glwrap::TriFace> > Mesh::getFaces()
	{
		if (m_internal)
		{
			return m_internal->getFaces();
		}
		return std::vector < std::shared_ptr<glwrap::TriFace> >();
	}

	const std::shared_ptr<glwrap::Model3D> Mesh::getInternal()
	{
		return m_internal;
	}

	std::shared_ptr<glwrap::Texture> Mesh::getTexture(std::shared_ptr<Texture> _texture)
	{
		return _texture->m_internal;
	}

	SimpleModel::SimpleModel()
	{
		m_tanBitan = false;
	}

	SimpleModel::SimpleModel(bool _calcTanBitan)
	{
		m_tanBitan = _calcTanBitan;
	}

	void SimpleModel::setAnimationCulling(bool _switch)
	{
		m_simpleModel->setCullAnimation(_switch);
	}

	void SimpleModel::onLoad(const std::string& _path)
	{
		m_path = _path;
		m_simpleModel = m_context.lock()->createMesh(_path, m_tanBitan);
		m_internal = m_simpleModel;
	}

	WavefrontModel::WavefrontModel() : SimpleModel()
	{

	}

	WavefrontModel::WavefrontModel(bool _calcTanBitan) : SimpleModel(_calcTanBitan)
	{

	}

	void WavefrontModel::onLoad(const std::string& _path)
	{
		m_path = _path;
		std::shared_ptr<glwrap::ObjMtlModel> obj = m_context.lock()->createObjMtlMesh(_path, m_tanBitan);

		m_internal = obj;
		m_simpleModel = obj;

		std::list<std::shared_ptr<glwrap::Material> > matList = obj->getMatList();
		std::shared_ptr<Texture> currentTex;
		std::string texPath = "";
		for (std::list<std::shared_ptr<glwrap::Material> >::iterator itr = matList.begin();
			itr != matList.end(); ++itr)
		{
			texPath = (*itr)->getTexturePath();
			if (texPath == "")
			{
				texPath = "images\\white.png";
			}
			currentTex = m_resources.lock()->load<Texture>(texPath);
			(*itr)->setTexture(getTexture(currentTex));
		}
	}

	SkinModel::SkinModel()
	{
		m_tanBitan = false;
	}

	SkinModel::SkinModel(bool _calcTanBitan)
	{
		m_tanBitan = _calcTanBitan;
	}

	void SkinModel::onLoad(const std::string& _path)
	{
		m_path = _path;
		std::shared_ptr<glwrap::GltfModel> gltf = m_context.lock()->createModel(_path, m_tanBitan);

		m_internal = gltf;

		std::list<std::shared_ptr<glwrap::Material> > matList = gltf->getMatList();
		std::shared_ptr<Texture> currentTex;
		std::string texPath = "";
		for (std::list<std::shared_ptr<glwrap::Material> >::iterator itr = matList.begin();
			itr != matList.end(); ++itr)
		{
			texPath = (*itr)->getTexturePath();
			if (texPath == "")
			{
				texPath = "images\\white.png";
			}
			currentTex = m_resources.lock()->load<Texture>(texPath);
			(*itr)->setTexture(getTexture(currentTex));
		}
	}

	void Texture::onLoad(const std::string& _path)
	{
		m_path = _path;
		m_internal = m_context.lock()->createTexture(_path);
	}

	const std::shared_ptr<glwrap::ShaderProgram> Shader::getInternal()
	{
		return m_internal;
	}

	void Shader::setEmissive(glm::vec3 _emissive)
	{
		m_internal->setUniform("in_Emissive", _emissive);
	}

	void Shader::setAmbient(glm::vec3 _ambient)
	{
		m_internal->setUniform("in_Ambient", _ambient);
	}

	void Shader::setLightPos(glm::vec3 _lightPos)
	{
		m_internal->setUniform("in_LightPos", _lightPos);
	}

	void Shader::setLightDir(glm::vec3 _lightDir)
	{
		if (_lightDir != glm::vec3(0, 0, 0))
		{
			m_internal->setUniform("in_LightDir", -_lightDir);
		}
	}

	void Shader::setLightCol(glm::vec3 _lightCol)
	{
		m_internal->setUniform("in_GlobalLightCol", _lightCol);
	}

	void Shader::setLightSpace(glm::mat4 _lightSpace)
	{
		m_internal->setUniform("in_GlobalLightSpace", _lightSpace);
	}

	void Shader::setLightSpace(std::vector<glm::mat4> _lightSpace)
	{
		m_internal->setUniform("in_LightSpace", _lightSpace);
	}

	void Shader::setPointLightCount(int _count)
	{
		m_internal->setUniform("in_PointTotal", _count);
	}

	void Shader::setDepthCubes(std::vector<std::shared_ptr<glwrap::DepthCube> > _depthCubes)
	{
		m_internal->setUniform("in_DepthMap", _depthCubes);
	}

	void Shader::setPointLightPositions(std::vector<glm::vec3> _pointLightPositions)
	{
		m_internal->setUniform("in_LightPos", _pointLightPositions);
	}

	void Shader::setPointLightColours(std::vector<glm::vec3> _pointColours)
	{
		m_internal->setUniform("in_LightCol", _pointColours);
	}

	void Shader::setFarPlanes(std::vector<float> _farPlanes)
	{
		m_internal->setUniform("in_FarPlane", _farPlanes);
	}

	bool Shader::getUniformCheck()
	{
		return m_uniformCheck;
	}

	void Shader::setUniformCheck(bool _switch)
	{
		m_uniformCheck = _switch;
	}

	void Shader::setCam(std::shared_ptr<Camera> _camera)
	{
		if (_camera != m_camSet)
		{
			glm::mat4 matrix = glm::inverse(_camera->getView());
			m_internal->setUniform("in_View", matrix);
			matrix = _camera->getProjection();
			m_internal->setUniform("in_Projection", matrix);
			m_camSet = _camera;
		}
	}

	void Shader::resetChecks()
	{
		if (m_uniformCheck)
		{
			setUniformCheck(false);

			m_camSet = NULL;
		}
	}

	void Shader::onLoad(const std::string& _path)
	{
		m_path = _path;
		m_internal = m_context.lock()->createShader(_path);
		m_uniformCheck = false;
		m_shadowCheck = false;
	}

	void ObjPartAnimation::onLoad(const std::string& _path)
	{
		m_path = _path;
	}
}