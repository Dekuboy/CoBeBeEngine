#include "Material.h"


namespace glwrap
{
	std::string Material::getTexturePath()
	{
		return m_colourPath;
	}

	void Material::setTexture(std::shared_ptr<Texture> _texture)
	{
		m_colourMap = _texture;
	}

	std::string Material::getMdetalRoughPath()
	{
		return m_metalRoughPath;
	}

	void Material::setMetalRough(std::shared_ptr<Texture> _texture)
	{
		m_metalRoughMap = _texture;
	}

	std::string Material::getNormalPath()
	{
		return m_normalPath;
	}
	void Material::setNormal(std::shared_ptr<Texture> _texture)
	{
		m_normalMap = _texture;
	}

	std::string Material::getOcclusionPath()
	{
		return m_occlusionPath;
	}

	void Material::setOcclusion(std::shared_ptr<Texture> _texture)
	{
		m_occlusionMap = _texture;
	}

	std::string Material::getEmissivePath()
	{
		return m_emissivePath;
	}

	void Material::setEmissive(std::shared_ptr<Texture> _texture)
	{
		m_emissiveMap = _texture;
	}
}