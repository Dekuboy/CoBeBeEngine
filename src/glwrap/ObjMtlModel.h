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
		* \brief Refer to each part and draw arrays
		* -to be called by ShaderProgram to ensure that the shader is approriately set
		* -applies material texture to input uniform name
		*/
		void draw(std::string _textureUniform);
		/**
		* \brief Refer to each part and draw arrays if the part is in view
		* -to be called by ShaderProgram to ensure that the shader is approriately set
		* -applies material texture to input uniform name
		* -useful for large objects where parts are too distant to always be in view
		*/
		void cullAndDraw(std::string _textureUniform);
		/**
		* \brief Draw an individual part from the model
		*/
		void drawPart(std::string _partName, std::string _textureUniform);

	};
}