#include <glwrap/PBRUniforms.h>

namespace glwrap
{
	void SingleUniform::getUniformName(int _enumType, std::string& _target)
	{
		if (_enumType == 0)
		{
			_target = "in_Texture";
		}
		else
		{
			_target = "";
		}
	}

	bool SingleUniform::setUniformName(int _enumType, std::string& _name)
	{
		if (_enumType == 0)
		{
			m_textureName = _name;
			return true;
		}
		else
		{
			return false;
		}
	}

	PBRUniforms::PBRUniforms()
	{
		m_pbrTextureNames.resize(10);
		m_pbrTextureNames.at(0) = "in_Texture";
		m_pbrTextureNames.at(1) = "in_MetalMap";
		m_pbrTextureNames.at(2) = "in_NormalMap";
		m_pbrTextureNames.at(3) = "in_AoMap";
		m_pbrTextureNames.at(4) = "in_EmissiveMap";
		m_pbrTextureNames.at(5) = "in_ColourFactor";
		m_pbrTextureNames.at(6) = "in_MetalFactor";
		m_pbrTextureNames.at(7) = "in_NormalFactor";
		m_pbrTextureNames.at(8) = "in_AoFactor";
		m_pbrTextureNames.at(9) = "in_EmissiveFactor";
	}

	void PBRUniforms::getUniformName(int _enumType, std::string& _target)
	{
		if (_enumType < 0 || _enumType > 9)
		{
			_target = "";
		}
		else
		{
			_target = m_pbrTextureNames.at(_enumType);
		}
	}

	bool PBRUniforms::setUniformName(int _enumType, std::string& _name)
	{
		if (_enumType < 0 || _enumType > 9)
		{
			return false;
		}
		else
		{
			m_pbrTextureNames.at(_enumType) = _name;
			return true;
		}
	}
}