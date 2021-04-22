#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glwrap/Model3D.h>

#include <vector>
#include <list>
#include <string>

namespace gltfparse
{
	struct Scene;
	struct Node;
	struct Image;
	struct MatTex;
	struct PBRMR;
	struct Mat;
	struct TexSampler;
	struct Prim;
	struct Mesh;
	struct Skin;
	struct Tex;
	struct Channel;
	struct AniSampler;
	struct AniParse;
	struct Accessor;
	struct AccessData;
	struct BufferView;
	struct Buffer;
}

namespace glwrap
{
	struct TriFace;

	class Context;
	class VertexBuffer;
	class ModelMesh;
	class ModelAnimation;
	class ShaderProgram;
	class Material;

	/**
	* \brief Contains Joint space values
	*/
	struct ModelSkin
	{
		std::string m_name;
		std::vector<glm::mat4> m_invBindMats;
		std::vector<int> m_nodeIds;

		glm::mat4 rootNodeTransform;

		int checkSkin(int _id);
	};

	/**
	* \brief Contains node space values
	*/
	struct NodeTransform
	{
		NodeTransform();
		~NodeTransform();

		glm::vec3* m_translate;
		glm::vec3* m_scale;
		glm::quat* m_quat;
		glm::mat4* m_matrix;

		void translateTriPos(std::shared_ptr<TriFace> _face);
		void translateTriNorm(std::shared_ptr<TriFace> _face);
	};

	/**
	* \brief Stores info on node hierarchy
	*/
	struct ModelNode
	{
		std::string m_name;
		int m_id = -1;
		std::weak_ptr<ModelMesh> m_mesh;
		std::weak_ptr<ModelNode> m_parent;
		std::vector<std::shared_ptr<ModelNode>> m_children;

		NodeTransform m_translation;

		void getModelMat(glm::mat4& _matrix);
	};

	/**
	* \brief Used to combine transformations from Animations
	*/
	struct AnimationTransform
	{
		AnimationTransform();
		glm::vec3 m_translate;
		glm::quat m_quat;
		glm::vec3 m_scale;

		void getModelMatRevQuat(glm::mat4& _matrix);
	};

	/**
	* \brief Holds information on a model loaded into GL (glTF)
	*/
	class GltfModel : public Model3D
	{
	public:
		GltfModel();
		GltfModel(std::string _path);

		/**
		* \brief Parse file and read into GL
		*/
		void parse(std::string _path);
		/**
		* \brief Parse glTF file and read into Gl
		* -if(_tanBitan) calculate tangent bitangent attributes for TBN matrix
		*/
		virtual void parse(std::string, bool _tanBitan);

		/**
		* \brief Attach Animation to object from file path
		*/
		//std::shared_ptr<ModelAnimation> addAnimation(std::string _path);
		int playAnimationOnce(std::string _name);
		void playAnimationOnce(int _index);
		int enableAnimation(std::string _name);
		void enableAnimation(int _index);
		int enableOnlyAnimation(std::string _name);
		void enableOnlyAnimation(int _index);
		int setAnimationTime(std::string _name, double _time);
		void setAnimationTime(int _index, double _time);
		int disableAnimation(std::string _name);
		void disableAnimation(int _index);
		void disableAllAnimations();

		/**
		* \brief Update Animation values
		*/
		void updateAnimationValues(std::vector<glm::vec4>& _translations, 
			std::vector<glm::vec4>& _rotations);

		/**
		* \brief Retrieve all the joints that make up the model
		*/
		std::vector<std::shared_ptr<ModelMesh> > getMeshes();
		/**
		* \brief Retrieve mesh that is called _name
		*/
		std::shared_ptr<ModelMesh> getMesh(std::string _name);
		/**
		* Retrieve list of attached animations
		*/
		std::vector<std::shared_ptr<ModelAnimation> >& getAnimations();

		/**
		* \brief Retrieve the list of Material types
		*/
		std::list<std::shared_ptr<Material> >& getMatList();

	protected:
		friend class Context;
		friend class ShaderProgram;

		std::vector<std::shared_ptr<ModelMesh> > m_parts; //!< Information on individual meshes of the model
		std::list<std::shared_ptr<Material> > m_materialList; //!< Material objects used in parts
		std::vector<std::shared_ptr<ModelNode>> m_allNodes; //!< All nodes in Model
		std::vector<std::shared_ptr<ModelNode>> m_sceneNodes; //!< Retains node hierarchy of the model
		std::vector<ModelSkin> m_skins; //!< Skins contain inverse bind matrices
		std::vector<std::shared_ptr<ModelAnimation> > m_animations; //!< List of animations attached to the model
		std::weak_ptr<GltfModel> m_self; //!< Pointer to self to set in individual joints

		std::vector<gltfparse::Node>* m_parseNodes; //!< Parse nodes required for recursive function

		/**
		* \brief Checks if character is white space
		*/
		bool checkWhiteSpace(const char& _checkChar);

		/**
		* \brief Prepare scenes from gltf
		*/
		void parseScenes(std::list<std::string>& _splitLine, std::vector<gltfparse::Scene>& _scenes);
		/**
		* \brief Prepare nodes for model to use
		*/
		void parseNodes(std::list<std::string>& _splitLine, std::vector<gltfparse::Node>& _nodes);
		/**
		* \brief Prepare samplers for model to use
		*/
		void parseSamplers(std::list<std::string>& _splitLine, std::vector<gltfparse::TexSampler>& _samplers);
		/**
		* \brief Prepare skins for model to use
		*/
		void parseSkins(std::list<std::string>& _splitLine, std::vector<gltfparse::Skin>& _skins);
		/**
		* \brief Prepare images for model to use
		*/
		void parseImages(std::list<std::string>& _splitLine, std::vector<gltfparse::Image>& _images);
		/**
		* \brief Prepare textures for model to use
		*/
		void parseTextures(std::list<std::string>& _splitLine, std::vector<gltfparse::Tex>& _textures);
		/**
		* \brief Prepare mattex for mat to use
		*/
		void parseMatTex(std::list<std::string>& _splitLine, std::list<std::string>::iterator& _itr, gltfparse::MatTex& _tex);
		/**
		* \brief Prepare materials for model to use
		*/
		void parseMaterials(std::list<std::string>& _splitLine, std::vector<gltfparse::Mat>& _materials);
		/**
		* \brief Prepare meshes for model to use
		*/
		void parseMeshes(std::list<std::string>& _splitLine, std::vector<gltfparse::Mesh>& _meshes);
		/**
		* \brief Prepare Animations for model to use
		*/
		void parseAnimations(std::list<std::string>& _splitLine, std::vector<gltfparse::AniParse>& _animations);
		/**
		* \brief Prepare accessors for parsing .bin
		*/
		void parseAccessors(std::list<std::string>& _splitLine, std::vector<gltfparse::Accessor>& _accessors);
		/**
		* \brief Prepare bufferviews for parsing .bin
		*/
		void parseBufferViews(std::list<std::string>& _splitLine, std::vector<gltfparse::BufferView>& _bufferViews);
		/**
		* \brief Prepare buffers for parsing .bin
		*/
		void parseBuffers(std::list<std::string>& _splitLine, std::vector<gltfparse::Buffer>& _buffers);

		/**
		* /brief Assemble GL Material list for Model to use
		*/
		void assembleModelMaterials(std::vector<std::shared_ptr<Material>>& _glMatList, std::string _path,
			std::vector<gltfparse::Mat>& _materials, std::vector<gltfparse::Tex>& _textures,
			std::vector<gltfparse::Image>& _images);

		/**
		* \brief Assemble a GL ModelMesh for ModelNode to use
		*/
		void assembleModelMesh(std::shared_ptr<ModelMesh> _part, std::shared_ptr<ModelNode> _modelNode,
			gltfparse::Mesh* _currentMesh, std::vector<gltfparse::Accessor>& _accessors,
			std::vector<gltfparse::AccessData>& _data, std::vector<gltfparse::Mesh>& _meshes,
			std::vector<std::shared_ptr<Material>>& _materials);

		/**
		* \brief Assemble a Node (Recursive function asssembles children)
		*/
		void assembleChildren(std::shared_ptr<ModelNode> _parentModelNode);

		/**
		* /brief Assemble GL Model for drawing
		*/
		void assembleModelNodes(gltfparse::Scene& _scene,
			std::vector<gltfparse::Accessor>& _accessors, std::vector<gltfparse::AccessData>& _data,
			std::vector<gltfparse::Mesh>& _meshes, std::vector<gltfparse::Skin>& _skins,
			std::vector<std::shared_ptr<Material>>& _materials);
		
		/**
		* \brief Checks if vertex values are the minimum or maximum of the model
		*/
		void checkMinMax(glm::vec3& _vertexPosition);
		/**
		* \brief Checks if vertex values are the minimum or maximum of the model
		*/
		void checkMin(glm::vec3& _vertexPosition);
		/**
		* \brief Checks if vertex values are the minimum or maximum of the model
		*/
		void checkMax(glm::vec3& _vertexPosition);

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

	};
}