#include <glwrap/VertexArray.h>
#include <list>

namespace glwrap
{
	class Material;
	class Texture;

	/**
	* \brief Model class which utilises a .mtl file to find textures
	*/
	class Model : public VertexArray
	{
	public:
		Model();
		Model(std::string _path);

		void parse(std::string _path);

		void draw(std::string _textureUniform);
		void drawPart(std::string _partName, std::string _textureUniform);

		std::shared_ptr<Material> getMaterial(std::string _material);
		std::list<std::shared_ptr<Material> >& getMatList();

	private:
		friend class Context;

		void parseMtl(std::string _path);

		std::list<std::shared_ptr<Material> > m_materialList;

	};
}