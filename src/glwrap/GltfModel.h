#include <GL/glew.h>
#include <glm/glm.hpp>

#include <vector>
#include <list>
#include <string>
namespace glwrap
{
	struct TriFace;

	class Context;
	class VertexBuffer;
	class ModelJoint;
	class ModelAnimation;
	class ShaderProgram;

	namespace gltfparse
	{
		struct Scene
		{
			std::string m_name;
			std::list<int> m_nodes;
		};

		struct Node
		{
			std::string m_name;
			std::list<int> m_children;
			int m_mesh;
			int m_skin;
			glm::vec3 m_translation;
			glm::vec3 m_scale;
			glm::vec4 m_rotation;
			glm::mat4 m_matrix;
		};

		struct Image
		{
			std::string m_uri;
			int m_bufferView;
			std::string m_mimeType;
		};

		struct MatTex
		{
			int m_index;
			int m_texCoord;
			float m_scale;
			float m_strength;
		};

		struct PBRMR
		{
			MatTex m_baseColour;
			glm::vec4 m_colourFactor;
			MatTex m_metallicRoughness;
			float m_metallicFactor;
			float m_roughnessFactor;
		};

		struct Mat
		{
			std::string m_name;
			bool m_doubleSided;
			PBRMR m_pbrMetallicRoughness;
			MatTex m_normalTexture;
			MatTex m_occlusionTexture;
			MatTex m_emissiveTexture;
			glm::vec3 m_emissiveFactor;
		};

		struct Sampler
		{
			int m_magFilter;
			int m_minFilter;
			int m_wrapS;
			int m_wrapT;
		};

		struct Prim
		{
			int m_positionId;
			int m_normalId;
			int m_colorId;
			int m_texCoordId;
			int m_jointsId;
			int m_weightsId;
			int m_tangentId;
			int m_indices;
			int m_material;
			int m_mode;
		};

		struct Mesh
		{
			std::string m_name;
			std::list<Prim> m_prims;
		};

		struct Skin
		{
			std::string m_name;
			int m_invBindMat;
			std::list<int> m_joints;
		};

		struct Tex
		{
			int m_source;
			int m_sampler;
		};

		struct Accessor
		{
			int m_bufferView;
			int m_byteOffset;
			int m_compType;
			int m_count;
			std::list<float> m_max;
			std::list<float> m_min;
			std::string m_type;
		};

		struct BufferView
		{
			int m_buffer;
			int m_byteLength;
			int m_target;
			int m_byteOffset;
			int m_byteStride;
		};

		struct Buffer
		{
			int m_byteLength;
			std::string m_uri;
		};
	}

	/**
	* \brief Holds information on a model loaded into GL (glTF)
	*/
	class GltfModel
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
		* \brief Retrieve the size of model based on xyz values
		*/
		glm::vec3 getSize();
		/**
		* \brief Set cull animation
		* -if(true) when ShaderProgram calls cullAndDraw() then
		*    ModelJoint will assume non-moving parts are within the view if the
		*    model is in view
		* -useful for smaller objects with moving parts with a larger reach
		*/
		void setCullAnimation(bool _switch);
		/**
		* \brief Get cull animation
		*/
		bool getCullAnimation();

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
		int disableAnimation(std::string _name);
		void disableAnimation(int _index);
		void disableAllAnimations();

		/**
		* \brief Retrieve all the tri information of the model
		*/
		std::vector<std::shared_ptr<TriFace> > getFaces();
		/**
		* \brief Retrieve all the joints that make up the model
		*/
		std::vector<std::shared_ptr<ModelJoint> > getJoints();
		/**
		* \brief Retrieve joint that is called _name
		*/
		std::shared_ptr<ModelJoint> getJoint(std::string _name);
		/**
		* Retrieve list of attached animations
		*/
		//std::vector<std::shared_ptr<ModelAnimation> > getAnimations();

	protected:
		friend class Context;
		friend class ShaderProgram;

		bool m_dirty; //!< If the buffers have been altered, update in GL
		std::vector<std::shared_ptr<TriFace> > m_faces; //!< Retains information on all tris in the model
		std::vector<std::shared_ptr<ModelJoint> > m_parts; //!< Information on individual joints of the model
		//std::vector<std::shared_ptr<ModelAnimation> > m_animations; //!< List of animations attached to the model
		std::weak_ptr<GltfModel> m_self; //!< Pointer to self to set in individual joints
		std::weak_ptr<Context> m_context; //!< Pointer to glwrap context

		glm::vec3 m_minPoint; //!< Minimum xyz values
		glm::vec3 m_maxPoint; //!< Maximum xyz values
		glm::vec3 m_size; //!< total size of the model

		bool m_cullAnimated; //!< Set to cull parts individually and assume part is on screen if model is

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
		void parseSamplers(std::list<std::string>& _splitLine, std::vector<gltfparse::Sampler>& _samplers);
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
		* \brief Checks if vertex values are the minimum or maximum of the model
		*/
		void checkMinMax(glm::vec3& _vertexPosition);

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