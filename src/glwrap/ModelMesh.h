#include <GL/glew.h>
#include <glm/glm.hpp>

#include <memory>
#include <vector>
#include <list>
#include <string>

namespace glwrap
{
	struct TriFace;

	class Context;
	class GltfModel;
	class VertexBuffer;
	class Material;

	/**
	* \brief Stores information on individual joints of a model
	*/
	class ModelMesh
	{
	public:
		ModelMesh(std::shared_ptr<GltfModel> _mesh, std::string _name);
		~ModelMesh();

		/**
		* \brief Retrieve name of joint
		*/
		std::string getName();
		/**
		* \brief Retrieve list of tri faces
		*/
		std::vector<std::shared_ptr<TriFace> >& getFaces();
		/**
		* \brief Add tri face to list
		*/
		void addFace(std::shared_ptr<TriFace> _face);

		/**
		* \brief Set buffer of name _attribute and add to list
		*/
		void setBuffer(std::string _attribute, std::shared_ptr<VertexBuffer> _buffer, int _materialId);
		/**
		* \brief Retrieve vertex total which use the same Material within part
		*/
		int getVertexCount(int _materialId);

		/**
		* \brief Retrieve GL Id of the vertex array which uses input Material
		*/
		GLuint getId(int _materialId);

		/**
		* \brief Retrieve the size of ModelJoint based on xyz values
		*/
		glm::vec3 getSize();

	private:
		friend class Context;
		friend class GltfModel;

		std::string m_name; //!< Name of ObjPart
		std::vector<GLuint> m_idList; //!< List of vertex array GL Ids

		bool m_dirty; //!< If a buffer has been added, buffer information must be sent to the GPU
		std::weak_ptr<GltfModel> m_model; //!< Pointer to model that mesh is attached to
		std::vector<std::shared_ptr<TriFace> > m_faces; //!< List of tris in part
		std::vector<std::vector<std::shared_ptr<VertexBuffer> > > 
			m_buffers; //!< List of different buffers in mesh, separated by Primitives ([prims][])
		glm::mat4 m_animationUniform; //!< Transformation matrix based on animated movement

		std::list<std::shared_ptr<Material> > m_materials; //!< List of Material used in part

		std::weak_ptr<ModelMesh> m_self; //!< Pointer to self to find Translation referring to this part
		std::weak_ptr<Context> m_context; //!< Pointer to glwrap context

		float m_offsetX; //!< x Offset from obj centre
		float m_offsetY; //!< y Offset from obj centre
		float m_offsetZ; //!< z Offset from obj centre

		float m_maxX; //!< Max x value in part
		float m_maxY; //!< Max y value in part
		float m_maxZ; //!< Max z value in part
		float m_minX; //!< Min x value in part
		float m_minY; //!< Min y value in part
		float m_minZ; //!< Min z value in part

		/**
		* \brief Translate mesh by base models animation
		*/
		void translate();
		/**
		* \brief Draws vertex arrays
		*/
		void drawArrays();

		/**
		* \brief Generates a vertex array Id in GL
		*/
		void generateArrays();

		/**
		* \brief Draw all vertex arrays represented within this joint
		*/
		void draw();
		/**
		* \brief Draw all vertex arrays represented within this mesh that appear in view
		* -useful for large models where meshes are too distant to always be in view
		*/
		void cullAndDraw();

	};
}