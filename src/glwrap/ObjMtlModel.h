#include <glwrap/VertexArray.h>
#include <list>

namespace glwrap
{
	class Material;
	class Texture;

	/**
	* \brief Model class which utilises a .mtl file to find textures
	*/
	class ObjMtlModel : public VertexArray
	{
	public:
		ObjMtlModel();
		ObjMtlModel(std::string _path);

		/**
		* \brief Parse .obj file alongside its .mtl file
		*/
		void parse(std::string _path);
		/**
		* \brief Parse .obj file alongside its .mtl file
		* -precalculate tangentBitangentNormal matrix if _tanBitan
		*/
		void parse(std::string _path, bool _tanBitan);

		/**
		* \brief Retrieve of Material of input name
		*/
		std::shared_ptr<Material> getMaterial(std::string _material);
		/**
		* \brief Retrieve the list of Material types
		*/
		std::list<std::shared_ptr<Material> >& getMatList();

	private:
		friend class Context;
		friend class ShaderProgram;

		std::list<std::shared_ptr<Material> > m_materialList;

		void parseMtl(std::string _path);

		/**
		* \brief Calls upon the part list and draws vertex arrays
		* -to be called by ShaderProgram
		*/
		void draw();
		/**
		* \brief Calls upon the part list and draws vertex arrays if in view
		* -to be called by ShaderProgram
		* -uses values from current active ShaderProgram to cull
		*/
		void cullAndDraw();
		/**
		* \brief Draws individual part of object by name
		*/
		void drawPart(std::string _partName);

	};
}