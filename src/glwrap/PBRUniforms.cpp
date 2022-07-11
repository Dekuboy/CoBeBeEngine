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
		m_pbrTextureNames[0] = "in_Texture";
		m_pbrTextureNames[1] = "in_MetalMap";
		m_pbrTextureNames[2] = "in_NormalMap";
		m_pbrTextureNames[3] = "in_AoMap";
		m_pbrTextureNames[4] = "in_EmissiveMap";
		m_pbrTextureNames[5] = "in_ColourFactor";
		m_pbrTextureNames[6] = "in_MetalFactor";
		m_pbrTextureNames[7] = "in_NormalFactor";
		m_pbrTextureNames[8] = "in_AoFactor";
		m_pbrTextureNames[9] = "in_EmissiveFactor";
	}

	void PBRUniforms::getUniformName(int _enumType, std::string& _target)
	{
		if (_enumType < 0 || _enumType > 9)
		{
			_target = "";
		}
		else
		{
			_target = m_pbrTextureNames[_enumType];
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
			m_pbrTextureNames[_enumType] = _name;
			return true;
		}
	}
}