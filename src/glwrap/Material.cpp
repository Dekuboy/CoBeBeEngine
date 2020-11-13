#include "Material.h"


namespace glwrap
{
	std::string Material::getTexturePath()
	{
		return m_mapPath;
	}

	void Material::setTexture(std::shared_ptr<Texture> _texture)
	{
		m_textureMap = _texture;
	}
}