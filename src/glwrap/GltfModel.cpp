#include <glwrap/GltfModel.h>
#include <glwrap/VertexBuffer.h>
#include <glwrap/FileManager.h>
#include <glwrap/ModelMesh.h>
#include <glwrap/TriFace.h>
#include <glwrap/Material.h>
#include <glwrap/ModelAnimation.h>
#include <glwrap/Context.h>
#include <glwrap/GltfParse.h>

#include <glm/ext.hpp>
#include <fstream>
#include <iostream>

namespace glwrap
{
	using namespace gltfparse;

	NodeTransform::~NodeTransform()
	{
		if (m_translate)
		{
			delete m_translate;
		}
		if (m_scale)
		{
			delete m_scale;
		}
		if (m_quat)
		{
			delete m_quat;
		}
		if (m_matrix)
		{
			delete m_matrix;
		}
	}

	void NodeTransform::translateTriPos(std::shared_ptr<TriFace> _face)
	{
		if (m_matrix)
		{
			_face->pa = glm::vec4(_face->pa, 1.0f) * (*m_matrix);
			_face->pb = glm::vec4(_face->pb, 1.0f) * (*m_matrix);
			_face->pc = glm::vec4(_face->pc, 1.0f) * (*m_matrix);
		}
		if (m_scale)
		{
			_face->pa *= (*m_scale);
			_face->pb *= (*m_scale);
			_face->pc *= (*m_scale);
		}
		if (m_quat)
		{
			_face->pa = _face->pa * *m_quat;
			_face->pb = _face->pb * *m_quat;
			_face->pc = _face->pc * *m_quat;
		}
		if (m_translate)
		{
			_face->pa += (*m_translate);
			_face->pb += (*m_translate);
			_face->pc += (*m_translate);
		}
	}

	void NodeTransform::translateTriNorm(std::shared_ptr<TriFace> _face)
	{
		if (m_matrix)
		{
			glm::mat3 matrix = *m_matrix;
			_face->na = glm::normalize(_face->na * matrix);
			_face->nb = glm::normalize(_face->nb * matrix);
			_face->nc = glm::normalize(_face->nc * matrix);
			return;
		}
		if (m_quat)
		{
			_face->na = glm::normalize(_face->na * *m_quat);
			_face->nb = glm::normalize(_face->nb * *m_quat);
			_face->nc = glm::normalize(_face->nc * *m_quat);
			return;
		}
	}

	void NodeTransform::getModelMat(glm::mat4& _idMatrix)
	{
		if (m_matrix)
		{
			_idMatrix = *m_matrix;
			return;
		}
		if (m_translate)
		{
			glm::translate(_idMatrix, *m_translate);
		}
		if (m_quat)
		{
			glm::quat quat = glm::quat(-m_quat->w, m_quat->x, m_quat->y, m_quat->z);
			_idMatrix = _idMatrix * glm::mat4_cast(quat);
		}
		if (m_scale)
		{
			glm::scale(_idMatrix, *m_scale);
		}
	}

	bool GltfModel::checkWhiteSpace(const char& _checkChar)
	{
		if (_checkChar == ' ') return true;
		if (_checkChar == '\r') return true;
		if (_checkChar == '\n') return true;
		if (_checkChar == '\t') return true;
		return false;
	}

	void GltfModel::parseScenes(std::list<std::string>& _splitLine, std::vector<gltfparse::Scene>& _scenes)
	{
		std::string tempStr;
		Scene newScene;
		int bracket = 1;
		int stack;
		std::list<std::string>::iterator itr = _splitLine.begin();
		itr++;
		itr = _splitLine.erase(itr);
		while (bracket > 0 && itr != _splitLine.end())
		{
			tempStr = *itr;
			if (tempStr == "{" || tempStr == "[")
			{
				bracket++;
			}
			else if (tempStr == "}" || tempStr == "]")
			{
				bracket--;
				if (bracket == 1)
				{
					_scenes.push_back(newScene);
				}
			}
			else if (tempStr == "name")
			{
				itr = _splitLine.erase(itr);
				tempStr = *itr;
				newScene.m_name = tempStr;
			}
			else if (tempStr == "nodes")
			{
				itr++;
				stack = bracket;
				bracket++;
				itr = _splitLine.erase(itr);
				while (bracket > stack && itr != _splitLine.end())
				{
					tempStr = *itr;
					if (tempStr == "]")
					{
						bracket--;
					}
					else
					{
						newScene.m_nodes.push_back(atoi(tempStr.c_str()));
					}
					itr = _splitLine.erase(itr);
				}
				itr--;
			}
			itr = _splitLine.erase(itr);
		}
	}

	void GltfModel::parseNodes(std::list<std::string>& _splitLine, std::vector<gltfparse::Node>& _nodes)
	{
		std::string tempStr;
		Node newNode;
		int bracket = 1;
		int stack;
		std::list<std::string>::iterator itr = _splitLine.begin();
		itr++;
		itr = _splitLine.erase(itr);
		while (bracket > 0 && itr != _splitLine.end())
		{
			tempStr = *itr;
			if (tempStr == "{" || tempStr == "[")
			{
				bracket++;
			}
			else if (tempStr == "}" || tempStr == "]")
			{
				bracket--;
				if (bracket == 1)
				{
					_nodes.push_back(newNode);
					newNode = Node();
				}
			}
			else if (tempStr == "name")
			{
				itr = _splitLine.erase(itr);
				tempStr = *itr;
				newNode.m_name = tempStr;
			}
			else if (tempStr == "children")
			{
				stack = bracket;
				bracket++;
				itr++;
				itr = _splitLine.erase(itr);
				while (bracket > stack && itr != _splitLine.end())
				{
					tempStr = *itr;
					if (tempStr == "]")
					{
						bracket--;
					}
					else
					{
						newNode.m_children.push_back(atoi(tempStr.c_str()));
					}
					itr = _splitLine.erase(itr);
				}
				itr--;
			}
			else if (tempStr == "mesh")
			{
				itr = _splitLine.erase(itr);
				tempStr = *itr;
				newNode.m_mesh = atoi(tempStr.c_str());
			}
			else if (tempStr == "skin")
			{
				itr = _splitLine.erase(itr);
				tempStr = *itr;
				newNode.m_skin = atoi(tempStr.c_str());
			}
			else if (tempStr == "translation")
			{
				itr = _splitLine.erase(itr);
				itr = _splitLine.erase(itr);
				for (int i = 0; i < 3; i++)
				{
					tempStr = *itr;
					newNode.m_translation.push_back(atof(tempStr.c_str()));
					itr = _splitLine.erase(itr);
				}
			}
			else if (tempStr == "scale")
			{
				itr = _splitLine.erase(itr);
				itr = _splitLine.erase(itr);
				for (int i = 0; i < 3; i++)
				{
					tempStr = *itr;
					newNode.m_scale.push_back(atof(tempStr.c_str()));
					itr = _splitLine.erase(itr);
				}
			}
			else if (tempStr == "rotation")
			{
				itr = _splitLine.erase(itr);
				itr = _splitLine.erase(itr);
				for (int i = 0; i < 4; i++)
				{
					tempStr = *itr;
					newNode.m_rotation.push_back(atof(tempStr.c_str()));
					itr = _splitLine.erase(itr);
				}
			}
			else if (tempStr == "matrix")
			{
				itr = _splitLine.erase(itr);
				itr = _splitLine.erase(itr);
				for (int i = 0; i < 16; i++)
				{
					tempStr = *itr;
					newNode.m_matrix.push_back(atof(tempStr.c_str()));
					itr = _splitLine.erase(itr);
				}
			}
			itr = _splitLine.erase(itr);
		}
	}

	void GltfModel::parseSamplers(std::list<std::string>& _splitLine, std::vector<gltfparse::Sampler>& _samplers)
	{
		std::string tempStr;
		Sampler newSampler;
		int bracket = 1;
		std::list<std::string>::iterator itr = _splitLine.begin();
		itr++;
		itr = _splitLine.erase(itr);
		while (bracket > 0 && itr != _splitLine.end())
		{
			tempStr = *itr;
			if (tempStr == "{" || tempStr == "[")
			{
				bracket++;
			}
			else if (tempStr == "}" || tempStr == "]")
			{
				bracket--;
				if (bracket == 1)
				{
					_samplers.push_back(newSampler);
					newSampler = Sampler();
				}
			}
			else if (tempStr == "magFilter")
			{
				itr = _splitLine.erase(itr);
				tempStr = *itr;
				newSampler.m_magFilter = atoi(tempStr.c_str());
			}
			else if (tempStr == "minFilter")
			{
				itr = _splitLine.erase(itr);
				tempStr = *itr;
				newSampler.m_minFilter = atoi(tempStr.c_str());
			}
			else if (tempStr == "wrapS")
			{
				itr = _splitLine.erase(itr);
				tempStr = *itr;
				newSampler.m_wrapS = atoi(tempStr.c_str());
			}
			else if (tempStr == "wrapT")
			{
				itr = _splitLine.erase(itr);
				tempStr = *itr;
				newSampler.m_wrapT = atoi(tempStr.c_str());
			}
			itr = _splitLine.erase(itr);
		}
	}

	void GltfModel::parseSkins(std::list<std::string>& _splitLine, std::vector<gltfparse::Skin>& _skins)
	{
		std::string tempStr;
		Skin newSkin;
		int bracket = 1;
		int stack;
		std::list<std::string>::iterator itr = _splitLine.begin();
		itr++;
		itr = _splitLine.erase(itr);
		while (bracket > 0 && itr != _splitLine.end())
		{
			tempStr = *itr;
			if (tempStr == "{" || tempStr == "[")
			{
				bracket++;
			}
			else if (tempStr == "}" || tempStr == "]")
			{
				bracket--;
				if (bracket == 1)
				{
					_skins.push_back(newSkin);
					newSkin = Skin();
				}
			}
			else if (tempStr == "name")
			{
				itr = _splitLine.erase(itr);
				tempStr = *itr;
				newSkin.m_name = tempStr;
			}
			else if (tempStr == "joints")
			{
				stack = bracket;
				bracket++;
				itr++;
				itr = _splitLine.erase(itr);
				while (bracket > stack && itr != _splitLine.end())
				{
					tempStr = *itr;
					if (tempStr == "]")
					{
						bracket--;
					}
					else
					{
						newSkin.m_joints.push_back(atoi(tempStr.c_str()));
					}
					itr = _splitLine.erase(itr);
				}
				itr--;
			}
			else if (tempStr == "inverseBindMatrices")
			{
				itr = _splitLine.erase(itr);
				tempStr = *itr;
				newSkin.m_invBindMat = atoi(tempStr.c_str());
			}
			itr = _splitLine.erase(itr);
		}
	}

	void GltfModel::parseImages(std::list<std::string>& _splitLine, std::vector<gltfparse::Image>& _images)
	{
		std::string tempStr;
		Image newImage;
		int bracket = 1;
		int stack;
		std::list<std::string>::iterator itr = _splitLine.begin();
		itr++;
		itr = _splitLine.erase(itr);
		while (bracket > 0 && itr != _splitLine.end())
		{
			tempStr = *itr;
			if (tempStr == "{" || tempStr == "[")
			{
				bracket++;
			}
			else if (tempStr == "}" || tempStr == "]")
			{
				bracket--;
				if (bracket == 1)
				{
					_images.push_back(newImage);
					newImage = Image();
				}
			}
			else if (tempStr == "uri")
			{
				itr = _splitLine.erase(itr);
				tempStr = *itr;
				newImage.m_uri = tempStr;
			}
			else if (tempStr == "bufferView")
			{
				itr = _splitLine.erase(itr);
				tempStr = *itr;
				newImage.m_bufferView = atoi(tempStr.c_str());
			}
			else if (tempStr == "mimeType")
			{
				itr = _splitLine.erase(itr);
				tempStr = *itr;
				newImage.m_mimeType = tempStr;
			}
			itr = _splitLine.erase(itr);
		}
	}

	void GltfModel::parseTextures(std::list<std::string>& _splitLine, std::vector<gltfparse::Tex>& _textures)
	{
		std::string tempStr;
		Tex newTex;
		int bracket = 1;
		int stack;
		std::list<std::string>::iterator itr = _splitLine.begin();
		itr++;
		itr = _splitLine.erase(itr);
		while (bracket > 0 && itr != _splitLine.end())
		{
			tempStr = *itr;
			if (tempStr == "{" || tempStr == "[")
			{
				bracket++;
			}
			else if (tempStr == "}" || tempStr == "]")
			{
				bracket--;
				if (bracket == 1)
				{
					_textures.push_back(newTex);
					newTex = Tex();
				}
			}
			else if (tempStr == "sampler")
			{
				itr = _splitLine.erase(itr);
				tempStr = *itr;
				newTex.m_sampler = atoi(tempStr.c_str());
			}
			else if (tempStr == "source")
			{
				itr = _splitLine.erase(itr);
				tempStr = *itr;
				newTex.m_source = atoi(tempStr.c_str());
			}
			itr = _splitLine.erase(itr);
		}
	}

	void GltfModel::parseMatTex(std::list<std::string>& _splitLine, std::list<std::string>::iterator& _itr, gltfparse::MatTex& _tex)
	{
		std::string tempStr;
		MatTex newMatTex;
		int bracket = 1;
		_itr++;
		_itr = _splitLine.erase(_itr);
		while (bracket > 0 && _itr != _splitLine.end())
		{
			tempStr = *_itr;
			if (tempStr == "}" || tempStr == "]")
			{
				bracket--;
			}
			else if (tempStr == "index")
			{
				_itr = _splitLine.erase(_itr);
				tempStr = *_itr;
				_tex.m_index = atoi(tempStr.c_str());
			}
			else if (tempStr == "texCoord")
			{
				_itr = _splitLine.erase(_itr);
				tempStr = *_itr;
				_tex.m_texCoord = tempStr.c_str()[0];
			}
			else if (tempStr == "scale")
			{
				_itr = _splitLine.erase(_itr);
				tempStr = *_itr;
				_tex.m_scale = atof(tempStr.c_str());
			}
			else if (tempStr == "strength")
			{
				_itr = _splitLine.erase(_itr);
				tempStr = *_itr;
				_tex.m_scale = atof(tempStr.c_str());
			}
			_itr = _splitLine.erase(_itr);
		}
		_itr--;
	}

	void GltfModel::parseMaterials(std::list<std::string>& _splitLine, std::vector<Mat>& _materials)
	{
		std::string tempStr;
		Mat newMaterial;
		MatTex newMatTex;
		int bracket = 1;
		int stack;
		std::list<std::string>::iterator itr = _splitLine.begin();
		itr++;
		itr = _splitLine.erase(itr);
		while (bracket > 0 && itr != _splitLine.end())
		{
			tempStr = *itr;
			if (tempStr == "{" || tempStr == "[")
			{
				bracket++;
			}
			else if (tempStr == "}" || tempStr == "]")
			{
				bracket--;
				if (bracket == 1)
				{
					_materials.push_back(newMaterial);
					newMaterial = Mat();
				}
			}
			else if (tempStr == "name")
			{
				itr = _splitLine.erase(itr);
				tempStr = *itr;
				newMaterial.m_name = tempStr;
			}
			else if (tempStr == "pbrMetallicRoughness")
			{
				stack = bracket;
				bracket++;
				itr++;
				itr = _splitLine.erase(itr);
				while (bracket > stack && itr != _splitLine.end())
				{
					tempStr = *itr;

					if (tempStr == "{" || tempStr == "[")
					{
						bracket++;
					}
					else if (tempStr == "}" || tempStr == "]")
					{
						bracket--;
					}
					else if (tempStr == "baseColorTexture")
					{
						parseMatTex(_splitLine, itr, newMatTex);
						newMaterial.m_pbrMetallicRoughness.m_baseColour = newMatTex;
						newMatTex = MatTex();
					}
					else if (tempStr == "baseColorFactor")
					{
						itr = _splitLine.erase(itr);
						itr = _splitLine.erase(itr);
						tempStr = *itr;
						newMaterial.m_pbrMetallicRoughness.m_colourFactor.x
							= atof(tempStr.c_str());
						itr = _splitLine.erase(itr);
						tempStr = *itr;
						newMaterial.m_pbrMetallicRoughness.m_colourFactor.y
							= atof(tempStr.c_str());
						itr = _splitLine.erase(itr);
						tempStr = *itr;
						newMaterial.m_pbrMetallicRoughness.m_colourFactor.z
							= atof(tempStr.c_str());
						itr = _splitLine.erase(itr);
						tempStr = *itr;
						newMaterial.m_pbrMetallicRoughness.m_colourFactor.w
							= atof(tempStr.c_str());
						itr = _splitLine.erase(itr);
					}
					else if (tempStr == "metallicRoughnessTexture")
					{
						parseMatTex(_splitLine, itr, newMatTex);
						newMaterial.m_pbrMetallicRoughness.m_metallicRoughness = newMatTex;
						newMatTex = MatTex();
					}
					else if (tempStr == "metallicFactor")
					{
						itr = _splitLine.erase(itr);
						tempStr = *itr;
						newMaterial.m_pbrMetallicRoughness.m_metallicFactor = atof(tempStr.c_str());
					}
					else if (tempStr == "roughnessFactor")
					{
						itr = _splitLine.erase(itr);
						tempStr = *itr;
						newMaterial.m_pbrMetallicRoughness.m_roughnessFactor = atof(tempStr.c_str());

					}
					itr = _splitLine.erase(itr);
				}
				itr--;
			}
			else if (tempStr == "normalTexture")
			{
				parseMatTex(_splitLine, itr, newMatTex);
				newMaterial.m_normalTexture = newMatTex;
				newMatTex = MatTex();
			}
			else if (tempStr == "occlusionTexture")
			{
				parseMatTex(_splitLine, itr, newMatTex);
				newMaterial.m_occlusionTexture = newMatTex;
				newMatTex = MatTex();
			}
			else if (tempStr == "emissiveTexture")
			{
				parseMatTex(_splitLine, itr, newMatTex);
				newMaterial.m_emissiveTexture = newMatTex;
				newMatTex = MatTex();
			}
			else if (tempStr == "emissiveFactor")
			{
				itr = _splitLine.erase(itr);
				itr = _splitLine.erase(itr);
				tempStr = *itr;
				newMaterial.m_emissiveFactor.x
					= atof(tempStr.c_str());
				itr = _splitLine.erase(itr);
				tempStr = *itr;
				newMaterial.m_emissiveFactor.y
					= atof(tempStr.c_str());
				itr = _splitLine.erase(itr);
				tempStr = *itr;
				newMaterial.m_emissiveFactor.z
					= atof(tempStr.c_str());
				itr = _splitLine.erase(itr);
			}
			itr = _splitLine.erase(itr);
		}
	}

	void GltfModel::parseMeshes(std::list<std::string>& _splitLine, std::vector<gltfparse::Mesh>& _meshes)
	{
		std::string tempStr;
		Mesh newMesh;
		Prim newPrims;
		int bracket = 1;
		int stack;
		std::list<std::string>::iterator itr = _splitLine.begin();
		itr++;
		itr = _splitLine.erase(itr);
		while (bracket > 0 && itr != _splitLine.end())
		{
			tempStr = *itr;
			if (tempStr == "{" || tempStr == "[")
			{
				bracket++;
			}
			else if (tempStr == "}" || tempStr == "]")
			{
				bracket--;
				if (bracket == 1)
				{
					_meshes.push_back(newMesh);
					newMesh = gltfparse::Mesh();
				}
			}
			else if (tempStr == "name")
			{
				itr = _splitLine.erase(itr);
				tempStr = *itr;
				newMesh.m_name = tempStr;
			}
			else if (tempStr == "primitives")
			{
				stack = bracket;
				bracket++;
				itr++;
				itr = _splitLine.erase(itr);
				while (bracket > stack && itr != _splitLine.end())
				{
					tempStr = *itr;

					if (tempStr == "{" || tempStr == "[")
					{
						bracket++;
					}
					else if (tempStr == "}" || tempStr == "]")
					{
						bracket--;
						if (bracket == stack + 1)
						{
							newMesh.m_prims.push_back(newPrims);
							newPrims = Prim();
						}
					}
					else if (tempStr == "attributes")
					{
						itr = _splitLine.erase(itr);
						bracket++;
					}
					else if (tempStr == "POSITION")
					{
						itr = _splitLine.erase(itr);
						tempStr = *itr;
						newPrims.m_positionId = atoi(tempStr.c_str());
					}
					else if (tempStr == "NORMAL")
					{
						itr = _splitLine.erase(itr);
						tempStr = *itr;
						newPrims.m_normalId = atoi(tempStr.c_str());
					}
					else if (tempStr == "COLOR_0")
					{
						itr = _splitLine.erase(itr);
						tempStr = *itr;
						newPrims.m_colorId = atoi(tempStr.c_str());
					}
					else if (tempStr == "TEXCOORD_0")
					{
						itr = _splitLine.erase(itr);
						tempStr = *itr;
						newPrims.m_texCoordId = atoi(tempStr.c_str());
					}
					else if (tempStr == "JOINTS_0")
					{
						itr = _splitLine.erase(itr);
						tempStr = *itr;
						newPrims.m_jointsId = atoi(tempStr.c_str());
					}
					else if (tempStr == "WEIGHTS_0")
					{
						itr = _splitLine.erase(itr);
						tempStr = *itr;
						newPrims.m_weightsId = atoi(tempStr.c_str());
					}
					else if (tempStr == "TANGENT")
					{
						itr = _splitLine.erase(itr);
						tempStr = *itr;
						newPrims.m_tangentId = atoi(tempStr.c_str());
					}
					else if (tempStr == "indices")
					{
						itr = _splitLine.erase(itr);
						tempStr = *itr;
						newPrims.m_indices = atoi(tempStr.c_str());
					}
					else if (tempStr == "material")
					{
						itr = _splitLine.erase(itr);
						tempStr = *itr;
						newPrims.m_material = atoi(tempStr.c_str());
					}
					else if (tempStr == "mode")
					{
						itr = _splitLine.erase(itr);
						tempStr = *itr;
						newPrims.m_mode = atoi(tempStr.c_str());
					}
					itr = _splitLine.erase(itr);
				}
				itr--;
			}
			itr = _splitLine.erase(itr);
		}
	}

	void GltfModel::parseAnimations(std::list<std::string>& _splitLine, std::vector<gltfparse::AniParse>& _animations)
	{
		std::string tempStr;
		AniParse newAnimation;
		Channel newChannel;
		AniSampler newSampler;
		int bracket = 1;
		int stack;
		std::list<std::string>::iterator itr = _splitLine.begin();
		itr++;
		itr = _splitLine.erase(itr);
		while (bracket > 0 && itr != _splitLine.end())
		{
			tempStr = *itr;
			if (tempStr == "{" || tempStr == "[")
			{
				bracket++;
			}
			else if (tempStr == "}" || tempStr == "]")
			{
				bracket--;
				if (bracket == 1)
				{
					_animations.push_back(newAnimation);
					newAnimation = gltfparse::AniParse();
				}
			}
			else if (tempStr == "name")
			{
				itr = _splitLine.erase(itr);
				tempStr = *itr;
				newAnimation.m_name = tempStr;
			}
			else if (tempStr == "channels")
			{
				stack = bracket;
				bracket++;
				itr++;
				itr = _splitLine.erase(itr);
				while (bracket > stack && itr != _splitLine.end())
				{
					tempStr = *itr;

					if (tempStr == "{" || tempStr == "[")
					{
						bracket++;
					}
					else if (tempStr == "}" || tempStr == "]")
					{
						bracket--;
						if (bracket == stack + 1)
						{
							newAnimation.m_channels.push_back(newChannel);
							newChannel = Channel();
						}
					}
					else if (tempStr == "sampler")
					{
						itr = _splitLine.erase(itr);
						tempStr = *itr;
						newChannel.m_sampler = atoi(tempStr.c_str());
					}
					else if (tempStr == "target")
					{
						itr = _splitLine.erase(itr);
						bracket++;
					}
					else if (tempStr == "node")
					{
						itr = _splitLine.erase(itr);
						tempStr = *itr;
						newChannel.m_node = atoi(tempStr.c_str());
					}
					else if (tempStr == "path")
					{
						itr = _splitLine.erase(itr);
						tempStr = *itr;
						if (tempStr == "translation")
						{
							newChannel.m_path = 't';
						}
						else if (tempStr == "rotation")
						{
							newChannel.m_path = 'r';
						}
						else if (tempStr == "scale")
						{
							newChannel.m_path = 's';
						}
						else if (tempStr == "weights")
						{
							newChannel.m_path = 'w';
						}
					}
					itr = _splitLine.erase(itr);
				}
				itr--;
			}
			else if (tempStr == "samplers")
			{
				stack = bracket;
				bracket++;
				itr++;
				itr = _splitLine.erase(itr);
				while (bracket > stack && itr != _splitLine.end())
				{
					tempStr = *itr;

					if (tempStr == "{" || tempStr == "[")
					{
						bracket++;
					}
					else if (tempStr == "}" || tempStr == "]")
					{
						bracket--;
						if (bracket == stack + 1)
						{
							newAnimation.m_samplers.push_back(newSampler);
							newSampler = AniSampler();
						}
					}
					else if (tempStr == "input")
					{
						itr = _splitLine.erase(itr);
						tempStr = *itr;
						newSampler.m_input = atoi(tempStr.c_str());
					}
					else if (tempStr == "output")
					{
						itr = _splitLine.erase(itr);
						tempStr = *itr;
						newSampler.m_output = atoi(tempStr.c_str());
					}
					else if (tempStr == "interpolation")
					{
						itr = _splitLine.erase(itr);
						tempStr = *itr;
						if (tempStr == "LINEAR")
						{
							newSampler.m_interpolate = 'l';
						}
						else if (tempStr == "STEP")
						{
							newSampler.m_interpolate = 's';
						}
						else if (tempStr == "CUBICSPLINE")
						{
							newSampler.m_interpolate = 'c';
						}
					}
					itr = _splitLine.erase(itr);
				}
				itr--;
			}
			itr = _splitLine.erase(itr);
		}
	}

	void GltfModel::parseAccessors(std::list<std::string>& _splitLine, std::vector<gltfparse::Accessor>& _accessors)
	{
		std::string tempStr;
		Accessor newAccessor;
		int bracket = 1;
		int stack;
		std::list<std::string>::iterator itr = _splitLine.begin();
		itr++;
		itr = _splitLine.erase(itr);
		while (bracket > 0 && itr != _splitLine.end())
		{
			tempStr = *itr;
			if (tempStr == "{" || tempStr == "[")
			{
				bracket++;
			}
			else if (tempStr == "}" || tempStr == "]")
			{
				bracket--;
				if (bracket == 1)
				{
					_accessors.push_back(newAccessor);
					newAccessor = Accessor();
				}
			}
			else if (tempStr == "bufferView")
			{
				itr = _splitLine.erase(itr);
				tempStr = *itr;
				newAccessor.m_bufferView = atoi(tempStr.c_str());
			}
			else if (tempStr == "byteOffset")
			{
				itr = _splitLine.erase(itr);
				tempStr = *itr;
				newAccessor.m_byteOffset = atoi(tempStr.c_str());
			}
			else if (tempStr == "componentType")
			{
				itr = _splitLine.erase(itr);
				tempStr = *itr;
				newAccessor.m_compType = atoi(tempStr.c_str());
			}
			else if (tempStr == "count")
			{
				itr = _splitLine.erase(itr);
				tempStr = *itr;
				newAccessor.m_count = atoi(tempStr.c_str());
			}
			else if (tempStr == "max")
			{
				stack = bracket;
				bracket++;
				itr++;
				itr = _splitLine.erase(itr);
				while (bracket > stack && itr != _splitLine.end())
				{
					tempStr = *itr;
					if (tempStr == "]")
					{
						bracket--;
					}
					else
					{
						newAccessor.m_max.push_back(atof(tempStr.c_str()));
					}
					itr = _splitLine.erase(itr);
				}
				itr--;
			}
			else if (tempStr == "min")
			{
				stack = bracket;
				bracket++;
				itr++;
				itr = _splitLine.erase(itr);
				while (bracket > stack && itr != _splitLine.end())
				{
					tempStr = *itr;
					if (tempStr == "]")
					{
						bracket--;
					}
					else
					{
						newAccessor.m_min.push_back(atof(tempStr.c_str()));
					}
					itr = _splitLine.erase(itr);
				}
				itr--;
			}
			else if (tempStr == "type")
			{
				itr = _splitLine.erase(itr);
				tempStr = *itr;
				if (tempStr == "VEC2")
				{
					newAccessor.m_type = 2;
				}
				else if (tempStr == "VEC3")
				{
					newAccessor.m_type = 3;
				}
				else if (tempStr == "VEC4" || tempStr == "MAT2")
				{
					newAccessor.m_type = 4;
				}
				else if (tempStr == "MAT3")
				{
					newAccessor.m_type = 9;
				}
				else if (tempStr == "MAT4")
				{
					newAccessor.m_type = 16;
				}
				else
				{
					newAccessor.m_type = 1;
				}
			}
			itr = _splitLine.erase(itr);
		}
	}

	void GltfModel::parseBufferViews(std::list<std::string>& _splitLine, std::vector<gltfparse::BufferView>& _bufferViews)
	{
		std::string tempStr;
		BufferView newView;
		int bracket = 1;
		int stack;
		std::list<std::string>::iterator itr = _splitLine.begin();
		itr++;
		itr = _splitLine.erase(itr);
		while (bracket > 0 && itr != _splitLine.end())
		{
			tempStr = *itr;
			if (tempStr == "{" || tempStr == "[")
			{
				bracket++;
			}
			else if (tempStr == "}" || tempStr == "]")
			{
				bracket--;
				if (bracket == 1)
				{
					_bufferViews.push_back(newView);
					newView = BufferView();
				}
			}
			else if (tempStr == "buffer")
			{
				itr = _splitLine.erase(itr);
				tempStr = *itr;
				newView.m_buffer = atoi(tempStr.c_str());
			}
			else if (tempStr == "byteLength")
			{
				itr = _splitLine.erase(itr);
				tempStr = *itr;
				newView.m_byteLength = atoi(tempStr.c_str());
			}
			else if (tempStr == "target")
			{
				itr = _splitLine.erase(itr);
				tempStr = *itr;
				newView.m_target = atoi(tempStr.c_str());
			}
			else if (tempStr == "byteStride")
			{
				itr = _splitLine.erase(itr);
				tempStr = *itr;
				newView.m_byteStride = atoi(tempStr.c_str());
			}
			else if (tempStr == "byteOffset")
			{
				itr = _splitLine.erase(itr);
				tempStr = *itr;
				newView.m_byteOffset = atoi(tempStr.c_str());
			}
			itr = _splitLine.erase(itr);
		}
	}

	void GltfModel::parseBuffers(std::list<std::string>& _splitLine, std::vector<gltfparse::Buffer>& _buffers)
	{
		std::string tempStr;
		gltfparse::Buffer newBuffer;
		int bracket = 1;
		std::list<std::string>::iterator itr = _splitLine.begin();
		itr++;
		itr = _splitLine.erase(itr);
		while (bracket > 0 && itr != _splitLine.end())
		{
			tempStr = *itr;
			if (tempStr == "{" || tempStr == "[")
			{
				bracket++;
			}
			else if (tempStr == "}" || tempStr == "]")
			{
				bracket--;
				if (bracket == 1)
				{
					_buffers.push_back(newBuffer);
					newBuffer = gltfparse::Buffer();
				}
			}
			else if (tempStr == "byteLength")
			{
				itr = _splitLine.erase(itr);
				tempStr = *itr;
				newBuffer.m_byteLength = atoi(tempStr.c_str());
			}
			else if (tempStr == "uri")
			{
				itr = _splitLine.erase(itr);
				tempStr = *itr;
				newBuffer.m_uri = tempStr;
			}
			itr = _splitLine.erase(itr);
		}
	}

	void GltfModel::assembleModelMaterials(std::vector<std::shared_ptr<Material>>& _glMatList, std::string _path,
		std::vector<gltfparse::Mat>& _materials, std::vector<gltfparse::Tex>& _textures,
		std::vector<gltfparse::Image>& _images)
	{
		int id;

		std::shared_ptr<Material> currentMaterial;

		_glMatList.resize(_materials.size());
		MatTex* matTex;
		PBRMR* pbr;
		std::vector<Mat>::iterator matItr = _materials.begin();
		std::vector<std::shared_ptr<Material>>::iterator
			glMatItr = _glMatList.begin();

		while (matItr != _materials.end())
		{
			currentMaterial = std::make_shared<Material>();

			currentMaterial->m_name = matItr->m_name;
			pbr = &matItr->m_pbrMetallicRoughness;

			matTex = &pbr->m_baseColour;
			if (matTex->m_index > -1)
			{
				currentMaterial->m_colourPath = _path +
					_images.at(_textures.at(matTex->m_index).m_source).m_uri;
				currentMaterial->m_colourAttrib = matTex->m_texCoord;
			}
			currentMaterial->m_colourFactor = pbr->m_colourFactor;

			matTex = &pbr->m_metallicRoughness;
			if (matTex->m_index > -1)
			{
				currentMaterial->m_metalRoughPath = _path +
					_images.at(_textures.at(matTex->m_index).m_source).m_uri;
				currentMaterial->m_metalRoughAttrib = matTex->m_texCoord;
			}
			currentMaterial->m_metalRoughFactor = glm::vec2(pbr->m_metallicFactor, pbr->m_roughnessFactor);

			matTex = &matItr->m_normalTexture;
			if (matTex->m_index > -1)
			{
				currentMaterial->m_normalPath = _path +
					_images.at(_textures.at(matTex->m_index).m_source).m_uri;
				currentMaterial->m_normalAttrib = matTex->m_texCoord;
			}
			currentMaterial->m_normalFactor = matTex->m_scale;

			matTex = &matItr->m_occlusionTexture;
			if (matTex->m_index > -1)
			{
				currentMaterial->m_occlusionPath = _path +
					_images.at(_textures.at(matTex->m_index).m_source).m_uri;
				currentMaterial->m_occlusionAttrib = matTex->m_texCoord;
			}
			currentMaterial->m_occlusionFactor = matTex->m_scale;

			matTex = &matItr->m_emissiveTexture;
			if (matTex->m_index > -1)
			{
				currentMaterial->m_emissivePath = _path +
					_images.at(_textures.at(matTex->m_index).m_source).m_uri;
				currentMaterial->m_emissiveAttrib = matTex->m_texCoord;
			}
			currentMaterial->m_emissiveFactor = matItr->m_emissiveFactor;

			*glMatItr = currentMaterial;
			matItr++;
			glMatItr++;
		}
	}

	void GltfModel::assembleModelMesh(std::shared_ptr<ModelMesh> _part, std::shared_ptr<ModelNode> _modelNode,
		gltfparse::Mesh* _currentMesh, std::vector<gltfparse::Accessor>& _accessors,
		std::vector<gltfparse::AccessData>& _data, std::vector<gltfparse::Mesh>& _meshes,
		std::vector<std::shared_ptr<Material>>& _materials)
	{
		std::shared_ptr<VertexBuffer> positionBuffer;
		std::shared_ptr<VertexBuffer> colourbuffer;
		std::shared_ptr<VertexBuffer> texCoordBuffer;
		std::shared_ptr<VertexBuffer> normalBuffer;
		std::shared_ptr<VertexBuffer> jointsBuffer;
		std::shared_ptr<VertexBuffer> weightsBuffer;
		std::shared_ptr<VertexBuffer> tangentBuffer;
		std::shared_ptr<VertexBuffer> bitangentBuffer;

		glm::vec3 vertexPosition, normal;
		glm::vec2 deltaUV1;
		glm::vec4 colour;
		glm::ivec4 joints;
		float factor;

		Accessor* accPointer;
		std::shared_ptr<Material> currentMaterial;
		int matCount = 0;
		bool checkRotation, checkMat;
		std::vector<GLushort>* indicesData;
		std::vector<GLbyte>* byteList;
		std::vector<GLubyte>* ubyteList;
		std::vector<GLshort>* shortList;
		std::vector<GLushort>* ushortList;
		std::vector<GLfloat>* floatList;
		std::shared_ptr<TriFace> f;
		std::vector<std::shared_ptr<TriFace>> partFaces;
		for (std::list<Prim>::iterator primItr = _currentMesh->m_prims.begin();
			primItr != _currentMesh->m_prims.end(); primItr++)
		{
			_part->generateArrays();
			indicesData = &_data.at(primItr->m_indices).m_ushort;

			positionBuffer = std::make_shared<VertexBuffer>();
			{
				accPointer = &_accessors.at(primItr->m_positionId);
				if ((accPointer->m_max.size() == 3) &&
					(accPointer->m_min.size() == 3))
				{
					f = std::make_shared<TriFace>();
					f->na = glm::vec3(1, 0, 0);
					f->nb = glm::vec3(0, 1, 0);
					f->nc = glm::vec3(0, 0, 1);
					_modelNode->m_translation.translateTriNorm(f);
					if (abs(f->na.x) == 1 || abs(f->na.y) == 1 || abs(f->na.z) == 1)
					{
						if (abs(f->nb.x) == 1 || abs(f->nb.y) == 1 || abs(f->nb.z) == 1)
						{
							checkRotation = false;
							vertexPosition.x = accPointer->m_max.at(0);
							vertexPosition.y = accPointer->m_max.at(1);
							vertexPosition.z = accPointer->m_max.at(2);
							f->pa = vertexPosition;
							vertexPosition.x = accPointer->m_min.at(0);
							vertexPosition.y = accPointer->m_min.at(1);
							vertexPosition.z = accPointer->m_min.at(2);
							f->pb = vertexPosition;
							f->pc = glm::vec3(1);
							_modelNode->m_translation.translateTriPos(f);

							if (f->pa.x < f->pb.x)
							{
								factor = f->pa.x;
								f->pa.x = f->pb.x;
								f->pb.x = factor;
							}
							if (f->pa.y < f->pb.y)
							{
								factor = f->pa.y;
								f->pa.y = f->pb.y;
								f->pb.y = factor;
							}
							if (f->pa.z < f->pb.z)
							{
								factor = f->pa.z;
								f->pa.z = f->pb.z;
								f->pb.z = factor;
							}

							_part->checkMax(f->pa);
							_part->checkMin(f->pb);
							checkMax(f->pa);
							checkMin(f->pb);
						}
						else
						{
							checkRotation = true;
						}
					}
					else
					{
						checkRotation = true;
					}
				}
				floatList = &_data.at(primItr->m_positionId).m_float;
				for (int i = 0; i < indicesData->size(); )
				{
					f = std::make_shared<TriFace>();
					vertexPosition.x = floatList->at(indicesData->at(i) * 3);
					vertexPosition.y = floatList->at(indicesData->at(i) * 3 + 1);
					vertexPosition.z = floatList->at(indicesData->at(i) * 3 + 2);
					i++;
					f->pa = vertexPosition;
					vertexPosition.x = floatList->at(indicesData->at(i) * 3);
					vertexPosition.y = floatList->at(indicesData->at(i) * 3 + 1);
					vertexPosition.z = floatList->at(indicesData->at(i) * 3 + 2);
					i++;
					f->pb = vertexPosition;
					vertexPosition.x = floatList->at(indicesData->at(i) * 3);
					vertexPosition.y = floatList->at(indicesData->at(i) * 3 + 1);
					vertexPosition.z = floatList->at(indicesData->at(i) * 3 + 2);
					i++;
					f->pc = vertexPosition;
					_modelNode->m_translation.translateTriPos(f);
					if (checkRotation)
					{
						_part->checkMinMax(f->pa);
						_part->checkMinMax(f->pb);
						_part->checkMinMax(f->pc);
						checkMinMax(f->pa);
						checkMinMax(f->pb);
						checkMinMax(f->pc);
					}
					positionBuffer->add(f->pa);
					positionBuffer->add(f->pb);
					positionBuffer->add(f->pc);
					m_faces.push_back(f);
					_part->addFace(f);
				}
				_part->setBuffer("in_Position", positionBuffer, matCount);
			}

			partFaces = _part->getFaces();

			if (primItr->m_normalId > -1)
			{
				normalBuffer = std::make_shared<VertexBuffer>();
				floatList = &_data.at(primItr->m_normalId).m_float;
				for (int i = 0; i < indicesData->size(); )
				{
					f = partFaces.at(i / 3);
					normal.x = floatList->at(indicesData->at(i) * 3);
					normal.y = floatList->at(indicesData->at(i) * 3 + 1);
					normal.z = floatList->at(indicesData->at(i) * 3 + 2);
					i++;
					f->na = normal;
					normal.x = floatList->at(indicesData->at(i) * 3);
					normal.y = floatList->at(indicesData->at(i) * 3 + 1);
					normal.z = floatList->at(indicesData->at(i) * 3 + 2);
					i++;
					f->nb = normal;
					normal.x = floatList->at(indicesData->at(i) * 3);
					normal.y = floatList->at(indicesData->at(i) * 3 + 1);
					normal.z = floatList->at(indicesData->at(i) * 3 + 2);
					i++;
					f->nc = normal;
					_modelNode->m_translation.translateTriNorm(f);
					normalBuffer->add(f->na);
					normalBuffer->add(f->nb);
					normalBuffer->add(f->nc);
				}
				_part->setBuffer("in_Normal", normalBuffer, matCount);
			}
			if (primItr->m_texCoordId > -1)
			{
				texCoordBuffer = std::make_shared<VertexBuffer>();
				floatList = &_data.at(primItr->m_texCoordId).m_float;
				for (int i = 0; i < indicesData->size(); )
				{
					f = partFaces.at(i / 6);
					deltaUV1.x = floatList->at(indicesData->at(i) * 2);
					deltaUV1.y = floatList->at(indicesData->at(i) * 2 + 1);
					i++;
					f->tca = deltaUV1;
					deltaUV1.x = floatList->at(indicesData->at(i) * 2);
					deltaUV1.y = floatList->at(indicesData->at(i) * 2 + 1);
					i++;
					f->tcb = deltaUV1;
					deltaUV1.x = floatList->at(indicesData->at(i) * 2);
					deltaUV1.y = floatList->at(indicesData->at(i) * 2 + 1);
					i++;
					f->tcc = deltaUV1;
					texCoordBuffer->add(f->tca);
					texCoordBuffer->add(f->tcb);
					texCoordBuffer->add(f->tcc);
				}
				_part->setBuffer("in_TexCoord", texCoordBuffer, matCount);
			}
			if (primItr->m_jointsId > -1)
			{
				jointsBuffer = std::make_shared<VertexBuffer>();
				accPointer = &_accessors.at(primItr->m_jointsId);
				if (accPointer->m_compType == 5121)
				{
					ubyteList = &_data.at(primItr->m_jointsId).m_ubyte;
					for (int i = 0; i < indicesData->size(); )
					{
						//f = partFaces.at(i / 12);
						joints.x = ubyteList->at(indicesData->at(i) * 4);
						joints.y = ubyteList->at(indicesData->at(i) * 4 + 1);
						joints.z = ubyteList->at(indicesData->at(i) * 4 + 2);
						joints.w = ubyteList->at(indicesData->at(i) * 4 + 3);
						jointsBuffer->add(joints);
						i++;
						//f-> = colour;
						//joints.x = floatList->at(indicesData->at(i) * 4);
						//joints.y = floatList->at(indicesData->at(i) * 4 + 1);
						//joints.z = floatList->at(indicesData->at(i) * 4 + 2);
						//joints.w = floatList->at(indicesData->at(i) * 4 + 3);
						//i++;
						//f-> = joints;
						//colour.x = floatList->at(indicesData->at(i) * 4);
						//colour.y = floatList->at(indicesData->at(i) * 4 + 1);
						//colour.z = floatList->at(indicesData->at(i) * 4 + 2);
						//colour.w = floatList->at(indicesData->at(i) * 4 + 3);
						//i++;
						//f-> = colour;
						//jointsBuffer->add();
						//jointsBuffer->add();
						//jointsBuffer->add();
					}
				}
				else if (accPointer->m_compType == 5123)
				{
					ushortList = &_data.at(primItr->m_jointsId).m_ushort;
					for (int i = 0; i < indicesData->size(); )
					{
						//f = partFaces.at(i / 12);
						joints.x = ushortList->at(indicesData->at(i) * 4);
						joints.y = ushortList->at(indicesData->at(i) * 4 + 1);
						joints.z = ushortList->at(indicesData->at(i) * 4 + 2);
						joints.w = ushortList->at(indicesData->at(i) * 4 + 3);
						jointsBuffer->add(joints);
						i++;
					}
				}

				_part->setBuffer("in_JointIDs", jointsBuffer, matCount);
			}
			if (primItr->m_weightsId > -1)
			{
				weightsBuffer = std::make_shared<VertexBuffer>();
				floatList = &_data.at(primItr->m_weightsId).m_float;
				for (int i = 0; i < indicesData->size(); )
				{
					//f = partFaces.at(i / 12);
					colour.x = floatList->at(indicesData->at(i) * 4);
					colour.y = floatList->at(indicesData->at(i) * 4 + 1);
					colour.z = floatList->at(indicesData->at(i) * 4 + 2);
					colour.w = floatList->at(indicesData->at(i) * 4 + 3);
					weightsBuffer->add(colour);
					i++;
				}
				_part->setBuffer("in_Weights", weightsBuffer, matCount);
			}

			if (primItr->m_material > -1)
			{
				checkMat = false;
				currentMaterial = _materials.at(primItr->m_material);
				for (std::list<std::shared_ptr<Material>>::iterator itr = m_materialList.begin();
					itr != m_materialList.end(); itr++)
				{
					if (*itr == currentMaterial)
					{
						checkMat = true;
					}
				}
				if (!checkMat)
				{
					m_materialList.push_back(currentMaterial);
				}
				_part->m_materials.push_back(currentMaterial);
			}
			else
			{
				_part->m_materials.push_back(nullptr);
			}
			matCount++;
		}
		_part->m_size = _part->m_maxPoint - _part->m_minPoint;
		m_parts.push_back(_part);
	}

	void GltfModel::assembleChildren(std::shared_ptr<ModelNode> _parentModelNode)
	{
		Node* parentNode = &m_parseNodes->at(_parentModelNode->m_id);
		_parentModelNode->m_name = parentNode->m_name;
		std::shared_ptr<ModelNode> child;
		for (std::vector<int>::iterator itr = parentNode->m_children.begin();
			itr != parentNode->m_children.end(); itr++)
		{
			if (m_checkNodes.at(*itr))
			{
				throw std::exception();
			}
			else
			{
				m_checkNodes.at(*itr) = true;
			}
			child = std::make_shared<ModelNode>();
			child->m_id = *itr;
			child->m_parent = _parentModelNode;
			_parentModelNode->m_children.push_back(child);
			m_allNodes.push_back(child);
			assembleChildren(child);
		}
	}

	void GltfModel::assembleModelNodes(gltfparse::Scene& _scene,
		std::vector<gltfparse::Accessor>& _accessors, std::vector<gltfparse::AccessData>& _data,
		std::vector<gltfparse::Mesh>& _meshes, std::vector<gltfparse::Skin>& _skins,
		std::vector<std::shared_ptr<Material>>& _materials)
	{
		int id;

		std::shared_ptr<ModelNode> currentModelNode;
		std::shared_ptr<ModelMesh> currentPart;

		Node* currentNode;
		ModelSkin* currentModelSkin;
		Skin* currentSkin;
		Mesh* currentMesh;
		glm::vec3* vec3Ptr;
		glm::quat* quatPtr;
		glm::mat4* mat4Ptr;
		std::vector<int>::iterator nodeItr = _scene.m_nodes.begin();
		std::vector<GLfloat>* floatList;

		m_checkNodes.resize(m_parseNodes->size());
		for (std::vector<bool>::iterator itr = m_checkNodes.begin();
			itr != m_checkNodes.end(); itr++)
		{
			*itr = false;
		}

		while (nodeItr != _scene.m_nodes.end())
		{
			if (m_checkNodes.at(*nodeItr))
			{
				throw std::exception();
			}
			else
			{
				m_checkNodes.at(*nodeItr) = true;
			}
			currentModelNode = std::make_shared<ModelNode>();
			m_sceneNodes.push_back(currentModelNode);
			currentModelNode->m_id = *nodeItr;
			m_allNodes.push_back(currentModelNode);
			assembleChildren(currentModelNode);
			nodeItr++;
		}

		m_checkNodes.clear();

		m_minPoint = glm::vec3(0);
		m_maxPoint = glm::vec3(0);

		for (std::vector<std::shared_ptr<ModelNode>>::iterator itr = m_allNodes.begin();
			itr != m_allNodes.end(); itr++)
		{
			currentModelNode = *itr;
			currentNode = &m_parseNodes->at((*itr)->m_id);
			{
				if (currentNode->m_translation.size() == 3)
				{
					vec3Ptr = new glm::vec3();
					vec3Ptr->x = currentNode->m_translation.at(0);
					vec3Ptr->y = currentNode->m_translation.at(1);
					vec3Ptr->z = currentNode->m_translation.at(2);
					currentModelNode->m_translation.m_translate = vec3Ptr;
				}
				if (currentNode->m_scale.size() == 3)
				{
					vec3Ptr = new glm::vec3();
					vec3Ptr->x = currentNode->m_scale.at(0);
					vec3Ptr->y = currentNode->m_scale.at(1);
					vec3Ptr->z = currentNode->m_scale.at(2);
					currentModelNode->m_translation.m_scale = vec3Ptr;
				}
				if (currentNode->m_rotation.size() == 4)
				{
					quatPtr = new glm::quat();
					quatPtr->x = currentNode->m_rotation.at(0);
					quatPtr->y = currentNode->m_rotation.at(1);
					quatPtr->z = currentNode->m_rotation.at(2);
					quatPtr->w = -currentNode->m_rotation.at(3);
					currentModelNode->m_translation.m_quat = quatPtr;
				}
				if (currentNode->m_matrix.size() == 16)
				{
					mat4Ptr = new glm::mat4();
					for (int i = 0; i < 4; i++)
					{
						for (int j = 0; j < 4; j++)
						{
							(*mat4Ptr)[i][j] = currentNode->m_rotation.at(4 * i + j);
						}
					}
					currentModelNode->m_translation.m_matrix = mat4Ptr;
				}
			}

			id = currentNode->m_skin;
			if (id > -1)
			{
				m_skins.push_back(ModelSkin());
				currentModelSkin = &m_skins.back();
				currentSkin = &_skins.at(id);

				floatList = &_data.at(currentSkin->m_invBindMat).m_float;

				currentModelSkin->m_invBindMats.resize(currentSkin->m_joints.size());
				for (int i = 0; i < currentSkin->m_joints.size(); i++)
				{
					mat4Ptr = &currentModelSkin->m_invBindMats.at(i);
					for (int x = 0; x < 4; x++)
					{
						for (int y = 0; y < 4; y++)
						{
							(*mat4Ptr)[x][y] =
								floatList->at((16 * i) + (4 * x) + y);
						}
					}
				}
			}

			id = currentNode->m_mesh;
			if (id > -1)
			{
				currentMesh = &_meshes.at(id);
				currentPart = getMesh(currentMesh->m_name);
				if (!currentPart)
				{
					currentPart = m_context.lock()->createModelMesh(m_self.lock(), currentMesh->m_name);
					assembleModelMesh(currentPart, currentModelNode,
						currentMesh, _accessors, _data,
						_meshes, _materials);
				}
				currentModelNode->m_mesh = currentPart;
			}
		}

		m_parseNodes = nullptr;
	}

	void GltfModel::checkMinMax(glm::vec3& _vertexPosition)
	{
		if (m_minPoint.x > m_maxPoint.x)
		{
			m_minPoint = _vertexPosition;
			m_maxPoint = _vertexPosition;
			return;
		}
		if (_vertexPosition.x < m_minPoint.x)
		{
			m_minPoint.x = _vertexPosition.x;
		}
		else if (_vertexPosition.x > m_maxPoint.x)
		{
			m_maxPoint.x = _vertexPosition.x;
		}
		if (_vertexPosition.y < m_minPoint.y)
		{
			m_minPoint.y = _vertexPosition.y;
		}
		else if (_vertexPosition.y > m_maxPoint.y)
		{
			m_maxPoint.y = _vertexPosition.y;
		}
		if (_vertexPosition.z < m_minPoint.z)
		{
			m_minPoint.z = _vertexPosition.z;
		}
		else if (_vertexPosition.z > m_maxPoint.z)
		{
			m_maxPoint.z = _vertexPosition.z;
		}
	}

	void GltfModel::checkMin(glm::vec3& _vertexPosition)
	{
		if (_vertexPosition.x < m_minPoint.x)
		{
			m_minPoint.x = _vertexPosition.x;
		}
		if (_vertexPosition.y < m_minPoint.y)
		{
			m_minPoint.y = _vertexPosition.y;
		}
		if (_vertexPosition.z < m_minPoint.z)
		{
			m_minPoint.z = _vertexPosition.z;
		}
	}

	void GltfModel::checkMax(glm::vec3& _vertexPosition)
	{
		if (_vertexPosition.x > m_maxPoint.x)
		{
			m_maxPoint.x = _vertexPosition.x;
		}
		if (_vertexPosition.y > m_maxPoint.y)
		{
			m_maxPoint.y = _vertexPosition.y;
		}
		if (_vertexPosition.z > m_maxPoint.z)
		{
			m_maxPoint.z = _vertexPosition.z;
		}
	}

	GltfModel::GltfModel()
	{
		m_dirty = false;
		m_minPoint = glm::vec3(std::numeric_limits<float>::max());
		m_maxPoint = glm::vec3(std::numeric_limits<float>::min());
		m_cullAnimated = false;
	}

	GltfModel::GltfModel(std::string _path)
	{
		m_dirty = false;
		m_minPoint = glm::vec3(std::numeric_limits<float>::max());
		m_maxPoint = glm::vec3(std::numeric_limits<float>::min());
		m_cullAnimated = false;
		parse(_path);
	}

	void GltfModel::parse(std::string _path)
	{
		parse(_path, false);
	}

	void GltfModel::parse(std::string _path, bool _tanBitan)
	{
		std::string filePath = FileManager::returnPath(_path);
		std::ifstream file(filePath.c_str());

		if (!file.is_open())
		{
			throw std::exception();
		}

		std::string tempStr = "";
		int start = -1, end;
		std::list<std::string> splitLine;

		{
			std::string line;
			int bracket = 0;
			bool inQuotes = false;
			char checkChar;

			while (!file.eof() && bracket != -1)
			{
				std::getline(file, line);
				if (line.length() < 1) continue;
				if (bracket == 0)
				{
					start = line.find_first_of('{');

					if (start >= 0)
					{
						bracket = 1;
					}
				}
				else
				{
					start = 0;
				}
				end = line.length();
				if (bracket > 0)
				{
					for (int i = start; i < end; i++)
					{
						checkChar = line.at(i);
						if (inQuotes)
						{
							if (checkChar == '\"')
							{
								if (tempStr != "") splitLine.push_back(tempStr);
								tempStr = "";
								inQuotes = false;
							}
							else
							{
								tempStr += checkChar;
							}
						}
						else if (checkChar == '{')
						{
							bracket++;
							if (tempStr != "") splitLine.push_back(tempStr);
							tempStr = checkChar;
							splitLine.push_back(tempStr);
							tempStr = "";
						}
						else if (checkChar == '}')
						{
							bracket--;
							if (tempStr != "") splitLine.push_back(tempStr);
							tempStr = checkChar;
							splitLine.push_back(tempStr);
							tempStr = "";
							if (bracket == 0)
							{
								bracket = -1;
								break;
							}
						}
						else if (checkChar == '[' ||
							checkChar == ']')
						{
							if (tempStr != "") splitLine.push_back(tempStr);
							tempStr = checkChar;
							splitLine.push_back(tempStr);
							tempStr = "";
						}
						else if (checkChar == ',' ||
							checkChar == ':')
						{
							if (tempStr != "") splitLine.push_back(tempStr);
							tempStr = "";
						}
						else if (checkChar == '\"')
						{
							if (tempStr != "") splitLine.push_back(tempStr);
							tempStr = "";
							inQuotes = true;
						}
						else if (!checkWhiteSpace(checkChar))
						{
							tempStr += line.at(i);
						}
					}
				}
			}
		}

		file.close();

		int currentScene;
		std::vector<Scene> scenes;
		std::vector<Node> nodes;
		std::vector<Sampler> samplers;
		std::vector<Skin> skins;
		std::vector<Image> images;
		std::vector<Tex> textures;
		std::vector<Mat> materials;
		std::vector<Mesh> meshes;
		std::vector<Accessor> accessors;
		std::vector<AniParse> animations;
		std::vector<BufferView> views;
		std::vector<Buffer> buffers;

		std::list<std::string>::iterator itr = splitLine.begin();

		while (itr != splitLine.end())
		{
			tempStr = *itr;
			if (tempStr == "scene")
			{
				itr = splitLine.erase(itr);
				tempStr = *itr;
				currentScene = atoi(tempStr.c_str());
			}
			else if (tempStr == "scenes")
			{
				parseScenes(splitLine, scenes);
			}
			else if (tempStr == "nodes")
			{
				parseNodes(splitLine, nodes);
			}
			else if (tempStr == "samplers")
			{
				parseSamplers(splitLine, samplers);
			}
			else if (tempStr == "skins")
			{
				parseSkins(splitLine, skins);
			}
			else if (tempStr == "images")
			{
				parseImages(splitLine, images);
			}
			else if (tempStr == "textures")
			{
				parseTextures(splitLine, textures);
			}
			else if (tempStr == "materials")
			{
				parseMaterials(splitLine, materials);
			}
			else if (tempStr == "meshes")
			{
				parseMeshes(splitLine, meshes);
			}
			else if (tempStr == "accessors")
			{
				parseAccessors(splitLine, accessors);
			}
			else if (tempStr == "animations")
			{
				parseAnimations(splitLine, animations);
			}
			else if (tempStr == "bufferViews")
			{
				parseBufferViews(splitLine, views);
			}
			else if (tempStr == "buffers")
			{
				parseBuffers(splitLine, buffers);
			}
			itr = splitLine.erase(itr);
		}

		std::vector<AccessData> data;
		Accessor* accPointer;
		data.resize(accessors.size());

		{
			std::vector<char> readBin;
			readBin.resize(buffers.at(0).m_byteLength);

			int identifier = filePath.find_last_of("\\");
			filePath = filePath.substr(0, identifier + 1);
			filePath += buffers.at(0).m_uri;

			file.open(filePath, std::ios::out | std::ios::binary);
			if (!file.is_open())
			{
				throw std::exception();
			}
			file.read((char*)&readBin[0], buffers.at(0).m_byteLength);
			file.close();

			filePath = filePath.substr(0, identifier + 1);

			AccessData* dataPointer;
			BufferView* viewPointer;
			int stride, dataItr, count;
			identifier = accessors.size();
			for (int accItr = 0; accItr < identifier; accItr++)
			{
				dataPointer = &data.at(accItr);
				accPointer = &accessors.at(accItr);
				viewPointer = &views.at(accPointer->m_bufferView);

				start = accPointer->m_byteOffset + viewPointer->m_byteOffset;
				end = start + viewPointer->m_byteLength;
				dataItr = 0;
				count = accPointer->m_count;
				count *= accPointer->m_type;
				if (accPointer->m_compType == 5126)
				{
					dataPointer->m_float.resize(count);
					stride = 4 + viewPointer->m_byteStride;
					for (int i = start; i < end && dataItr < count; i += stride)
					{
						dataPointer->m_float.at(dataItr) = *(GLfloat*)&readBin.at(i);
						dataItr++;
					}
				}
				else if (accPointer->m_compType == 5123)
				{
					dataPointer->m_ushort.resize(count);
					stride = 2 + viewPointer->m_byteStride;
					for (int i = start; i < end && dataItr < count; i += stride)
					{
						dataPointer->m_ushort.at(dataItr) = *(GLushort*)&readBin.at(i);
						dataItr++;
					}
				}
				else if (accPointer->m_compType == 5122)
				{
					dataPointer->m_short.resize(count);
					stride = 2 + viewPointer->m_byteStride;
					for (int i = start; i < end && dataItr < count; i += stride)
					{
						dataPointer->m_short.at(dataItr) = *(GLshort*)&readBin.at(i);
						dataItr++;
					}
				}
				else if (accPointer->m_compType == 5121)
				{
					dataPointer->m_ubyte.resize(count);
					stride = 1 + viewPointer->m_byteStride;
					for (int i = start; i < end && dataItr < count; i += stride)
					{
						dataPointer->m_ubyte.at(dataItr) = *(GLubyte*)&readBin.at(i);
						dataItr++;
					}
				}
				else if (accPointer->m_compType == 5120)
				{
					dataPointer->m_byte.resize(count);
					stride = 2 + viewPointer->m_byteStride;
					for (int i = start; i < end && dataItr < count; i += stride)
					{
						dataPointer->m_byte.at(dataItr) = *(GLbyte*)&readBin.at(i);
						dataItr++;
					}
				}
			}
		}

		std::vector<std::shared_ptr<Material>> glMatList;
		tempStr = _path.substr(0, _path.find_last_of('\\') + 1);

		assembleModelMaterials(glMatList, tempStr, materials, textures, images);
		m_parseNodes = &nodes;
		assembleModelNodes(scenes.at(currentScene), accessors, data,
			meshes, skins, glMatList);

		{
			std::shared_ptr<ModelAnimation> currentAnimation;
		}

		m_size = m_maxPoint - m_minPoint;
	}

	void GltfModel::draw()
	{
		for (std::vector<std::shared_ptr<ModelMesh> >::iterator itr = m_parts.begin();
			itr != m_parts.end(); itr++)
		{
			(*itr)->draw();
		}
	}

	void GltfModel::cullAndDraw()
	{
		for (std::vector<std::shared_ptr<ModelMesh> >::iterator itr = m_parts.begin();
			itr != m_parts.end(); itr++)
		{
			(*itr)->cullAndDraw();
		}
	}

	//std::shared_ptr<ModelAnimation> GltfModel::addAnimation(std::string _path)
	//{
	//	std::shared_ptr<ObjAnimation> anim = m_context.lock()->createAnimation(
	//		m_self.lock(), _path);
	//	m_animations.push_back(anim);
	//	return anim;
	//	return std::make_shared<ModelAnimation>();
	//}

	int GltfModel::playAnimationOnce(std::string _name)
	{
		//bool found = false;

		//for (int index = 0; index < m_animations.size(); index++)
		//{
		//	if (m_animations.at(index)->getName() == _name)
		//	{
		//		m_animations.at(index)->setRepeating(false);
		//		m_animations.at(index)->setEnabled(true);
		//		return index;
		//	}
		//}

		//throw std::exception();
		return -1;
	}

	void GltfModel::playAnimationOnce(int _index)
	{
		//if (_index < m_animations.size())
		//{
		//	m_animations.at(_index)->setRepeating(false);
		//	m_animations.at(_index)->setEnabled(true);
		//}
	}

	int GltfModel::enableAnimation(std::string _name)
	{
		//bool found = false;

		//for (int index = 0; index < m_animations.size(); index++)
		//{
		//	if (m_animations.at(index)->getName() == _name)
		//	{
		//		m_animations.at(index)->setRepeating(true);
		//		m_animations.at(index)->setEnabled(true);
		//		return index;
		//	}
		//}

		//throw std::exception();
		return -1;
	}

	void GltfModel::enableAnimation(int _index)
	{
		//if (_index < m_animations.size())
		//{
		//	m_animations.at(_index)->setRepeating(true);
		//	m_animations.at(_index)->setEnabled(true);
		//}
	}

	int GltfModel::enableOnlyAnimation(std::string _name)
	{
		//bool found = false;

		//for (int index = 0; index < m_animations.size(); index++)
		//{
		//	if (m_animations.at(index)->getName() == _name)
		//	{
		//		m_animations.at(index)->setEnabled(true);
		//		return index;
		//	}
		//	else
		//	{
		//		m_animations.at(index)->setEnabled(false);
		//	}
		//}

		//throw std::exception();
		return -1;
	}

	void GltfModel::enableOnlyAnimation(int _index)
	{
		//for (int index = 0; index < m_animations.size(); index++)
		//{
		//	if (index == _index)
		//	{
		//		m_animations.at(index)->setEnabled(true);
		//	}
		//	else
		//	{
		//		m_animations.at(index)->setEnabled(false);
		//	}
		//}
	}

	int GltfModel::disableAnimation(std::string _name)
	{
		//bool found = false;

		//for (int index = 0; index < m_animations.size(); index++)
		//{
		//	if (m_animations.at(index)->getName() == _name)
		//	{
		//		m_animations.at(index)->setEnabled(false);
		//		return index;
		//	}
		//}

		//throw std::exception();
		return -1;
	}

	void GltfModel::disableAnimation(int _index)
	{
		//if (_index < m_animations.size())
		//{
		//	m_animations.at(_index)->setEnabled(false);
		//}
	}

	void GltfModel::disableAllAnimations()
	{
		//for (int index = 0; index < m_animations.size(); index++)
		//{
		//	m_animations.at(index)->setEnabled(false);
		//}
	}

	std::vector<std::shared_ptr<ModelMesh> > GltfModel::getMeshes()
	{
		return m_parts;
	}

	std::shared_ptr<ModelMesh> GltfModel::getMesh(std::string _name)
	{
		for (int partIndex = 0; partIndex < m_parts.size(); partIndex++)
		{
			if (m_parts.at(partIndex)->getName() == _name)
			{
				return m_parts.at(partIndex);
			}
		}
		return nullptr;
	}

	std::vector<std::shared_ptr<ModelAnimation> >& GltfModel::getAnimations()
	{
		return m_animations;
	}

	std::list<std::shared_ptr<Material> >& GltfModel::getMatList()
	{
		return m_materialList;
	}
}
