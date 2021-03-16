#include <glwrap/GltfModel.h>
#include <glwrap/VertexBuffer.h>
#include <glwrap/FileManager.h>
#include <glwrap/ModelJoint.h>
#include <glwrap/TriFace.h>
#include <glwrap/Material.h>
//#include <glwrap/ModelAnimation.h>
#include <glwrap/Context.h>

#include <fstream>
#include <iostream>

namespace glwrap
{
	using namespace gltfparse;

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
					tempStr == *itr;
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
		glm::vec4 tempVec;
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
				newNode.m_name = atoi(tempStr.c_str());
			}
			else if ("children")
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
			else if ("mesh")
			{
				itr = _splitLine.erase(itr);
				tempStr = *itr;
				newNode.m_mesh = atoi(tempStr.c_str());
			}
			else if ("skin")
			{
				itr = _splitLine.erase(itr);
				tempStr = *itr;
				newNode.m_skin = atoi(tempStr.c_str());
			}
			else if ("translation")
			{
				itr = _splitLine.erase(itr);
				itr = _splitLine.erase(itr);
				tempStr = *itr;
				newNode.m_translation.x = atof(tempStr.c_str());
				itr = _splitLine.erase(itr);
				tempStr = *itr;
				newNode.m_translation.y = atof(tempStr.c_str());
				itr = _splitLine.erase(itr);
				tempStr = *itr;
				newNode.m_translation.z = atof(tempStr.c_str());
				itr = _splitLine.erase(itr);
			}
			else if ("scale")
			{
				itr = _splitLine.erase(itr);
				itr = _splitLine.erase(itr);
				tempStr = *itr;
				newNode.m_scale.x = atof(tempStr.c_str());
				itr = _splitLine.erase(itr);
				tempStr = *itr;
				newNode.m_scale.y = atof(tempStr.c_str());
				itr = _splitLine.erase(itr);
				tempStr = *itr;
				newNode.m_scale.z = atof(tempStr.c_str());
				itr = _splitLine.erase(itr);
			}
			else if ("rotation")
			{
				itr = _splitLine.erase(itr);
				itr = _splitLine.erase(itr);
				tempStr = *itr;
				newNode.m_rotation.x = atof(tempStr.c_str());
				itr = _splitLine.erase(itr);
				tempStr = *itr;
				newNode.m_rotation.y = atof(tempStr.c_str());
				itr = _splitLine.erase(itr);
				tempStr = *itr;
				newNode.m_rotation.z = atof(tempStr.c_str());
				itr = _splitLine.erase(itr);
				tempStr = *itr;
				newNode.m_rotation.w = atof(tempStr.c_str());
				itr = _splitLine.erase(itr);
			}
			else if ("matrix")
			{
				itr = _splitLine.erase(itr);
				itr = _splitLine.erase(itr);
				for (int i = 0; i > 4; i++)
				{
					tempStr = *itr;
					tempVec.x = atof(tempStr.c_str());
					itr = _splitLine.erase(itr);
					tempStr = *itr;
					tempVec.y = atof(tempStr.c_str());
					itr = _splitLine.erase(itr);
					tempStr = *itr;
					tempVec.z = atof(tempStr.c_str());
					itr = _splitLine.erase(itr);
					tempStr = *itr;
					tempVec.w = atof(tempStr.c_str());
					itr = _splitLine.erase(itr);

					newNode.m_matrix[i] = tempVec;
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
		while (itr != _splitLine.end())
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
				_tex.m_texCoord = atoi(tempStr.c_str());
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
				_tex.m_strength = atof(tempStr.c_str());
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
				newAccessor.m_type = tempStr;
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
		while (itr != _splitLine.end())
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

	void GltfModel::checkMinMax(glm::vec3& _vertexPosition)
	{
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

	GltfModel::GltfModel() : m_dirty(false)
	{
		m_minPoint = glm::vec3(0);
		m_maxPoint = glm::vec3(0);
		m_cullAnimated = false;
	}

	GltfModel::GltfModel(std::string _path) : m_dirty(false)
	{
		m_minPoint = glm::vec3(0);
		m_maxPoint = glm::vec3(0);
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
		std::list<std::string> splitLine;

		{
			std::string line;
			int start = -1, end, bracket = 0;
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
			file.close();
		}

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

		std::shared_ptr<ModelJoint> currentPart;

		std::shared_ptr<VertexBuffer> positionBuffer;
		std::shared_ptr<VertexBuffer> texCoordBuffer;
		std::shared_ptr<VertexBuffer> normalBuffer;
		std::shared_ptr<VertexBuffer> tangentBuffer;
		std::shared_ptr<VertexBuffer> bitangentBuffer;

		TriFace f;

		glm::vec3 vertexPosition, edge1, edge2, normal;
		glm::vec2 deltaUV1, deltaUV2;
		float factor;

		Scene* sceneContext = &scenes.at(currentScene);

		//if (positionBuffer) currentPart->setBuffer("in_Position", positionBuffer, 0);
		//if (texCoordBuffer) currentPart->setBuffer("in_TexCoord", texCoordBuffer, 0);
		//if (normalBuffer)
		//{
		//	currentPart->setBuffer("in_Normal", normalBuffer, 0);
		//	if (_tanBitan)
		//	{
		//		currentPart->setBuffer("in_Tangent", tangentBuffer, 0);
		//		currentPart->setBuffer("in_Bitangent", bitangentBuffer, 0);
		//	}
		//}
		//if (currentPart) m_parts.push_back(currentPart);

		m_size = m_maxPoint - m_minPoint;
	}

	void GltfModel::draw()
	{
		for (std::vector<std::shared_ptr<ModelJoint> >::iterator itr = m_parts.begin();
			itr != m_parts.end(); itr++)
		{
			(*itr)->draw();
		}
	}

	void GltfModel::cullAndDraw()
	{
		for (std::vector<std::shared_ptr<ModelJoint> >::iterator itr = m_parts.begin();
			itr != m_parts.end(); itr++)
		{
			(*itr)->cullAndDraw();
		}
	}

	void GltfModel::drawPart(std::string _partName)
	{
		for (std::vector<std::shared_ptr<ModelJoint> >::iterator itr = m_parts.begin();
			itr != m_parts.end(); itr++)
		{
			if ((*itr)->getName() == _partName)
			{
				(*itr)->draw();
				return;
			}
		}
	}

	glm::vec3 GltfModel::getSize()
	{
		return m_size;
	}

	void GltfModel::setCullAnimation(bool _switch)
	{
		m_cullAnimated = _switch;
	}

	bool GltfModel::getCullAnimation()
	{
		return m_cullAnimated;
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

	std::vector<std::shared_ptr<TriFace> > GltfModel::getFaces()
	{
		return m_faces;
	}

	std::vector<std::shared_ptr<ModelJoint> > GltfModel::getJoints()
	{
		return m_parts;
	}

	std::shared_ptr<ModelJoint> GltfModel::getJoint(std::string _name)
	{
		for (int partIndex = 0; partIndex < m_parts.size(); partIndex++)
		{
			if (m_parts.at(partIndex)->getName() == _name)
			{
				return m_parts.at(partIndex);
			}
		}

		throw std::exception();
	}

	//std::vector<std::shared_ptr<ModelAnimation> > GltfModel::getAnimations()
	//{
	//	return m_animations;
	//}
}
