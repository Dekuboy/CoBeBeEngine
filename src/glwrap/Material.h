#include <memory>
#include <string>

namespace glwrap
{
	class Model;
	class Part;
	class Texture;

	class Material
	{
	public:
		std::string getTexturePath();
		void setTexture(std::shared_ptr<Texture> _texture);

	private:
		friend class Model;
		friend class Part;

		std::string m_name;
		std::string m_mapPath;
		std::weak_ptr<Texture> m_textureMap;

	};
}