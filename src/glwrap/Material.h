#include <memory>
#include <string>

namespace glwrap
{
	class ObjMtlModel;
	class ObjPart;
	class Texture;

	class Material
	{
	public:
		std::string getTexturePath();
		void setTexture(std::shared_ptr<Texture> _texture);

	private:
		friend class ObjMtlModel;
		friend class ObjPart;

		std::string m_name;
		std::string m_mapPath;
		std::weak_ptr<Texture> m_textureMap;

	};
}