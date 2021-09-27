#include <GL/glew.h>
#include <glm/glm.hpp>

#include <string>
#include <vector>
#include <list>

namespace gltfparse
{
	/**
	* \brief Contains scene values (the nodes)
	*/
	struct Scene
	{
		std::string m_name; //!< Scene name
		std::vector<int> m_nodes; //!< Nodes in scene
	};

	/**
	* \brief Contains information on models in scene
	*/
	struct Node
	{
		std::string m_name; //!< Node name
		std::vector<int> m_children; //!< Child node IDs
		int m_mesh = -1; //!< Attached mesh ID if applicable
		int m_skin = -1; //!< Attached skin ID if applicable
		std::vector<float> m_translation; //!< Position values
		std::vector<float> m_scale; //!< Size values
		std::vector<float> m_rotation; //!< Rotation values
		std::vector<float> m_matrix; //!< Full transformation matrix
	};

	/**
	* \brief Contains external image values
	*/
	struct Image
	{
		std::string m_uri; //!< Contains local path to image
		int m_bufferView = -1; //!< BView ID
		std::string m_mimeType; //!< mimeType
	};

	/**
	* \brief Contains Texture values used in Material
	*/
	struct MatTex
	{
		int m_index = -1; //!< Texture ID
		int m_texCoord; //!< Attribute location
		float m_scale; //!< Multiplier for tex values
	};

	/**
	* \brief Physically-Based-Rendering Metallic Roughness values
	*/
	struct PBRMR
	{
		MatTex m_baseColour; //!< Base Metal Texture values
		glm::vec4 m_colourFactor; //!< Colour multiplier
		MatTex m_metallicRoughness; //!< MR Texture values
		float m_metallicFactor; //!< Metal value multiplier
		float m_roughnessFactor; //!< Roughness value multiplier
	};

	/**
	* \brief Contains information on material used
	*/
	struct Mat
	{
		std::string m_name; //!< Material name
		bool m_doubleSided; //!< Is the Texture culled from behind
		PBRMR m_pbrMetallicRoughness; //!< PBR values
		MatTex m_normalTexture; //!< Normal Texture values
		MatTex m_occlusionTexture; //!< Occlusion Texture values
		MatTex m_emissiveTexture; //!< Emission Texture values
		glm::vec3 m_emissiveFactor; //!< Emission multiplier
	};

	/**
	* \brief Texture Sampler values
	*/
	struct TexSampler
	{
		int m_magFilter;
		int m_minFilter;
		int m_wrapS;
		int m_wrapT;
	};

	/**
	* \brief Model Primitive values
	*/
	struct Prim
	{
		int m_positionId = -1;
		int m_normalId = -1;
		int m_colorId = -1;
		int m_texCoordId = -1;
		int m_jointsId = -1;
		int m_weightsId = -1;
		int m_tangentId = -1;
		int m_indices = -1;
		int m_material = -1;
		int m_mode = -1;
	};

	/**
	* \brief Model Mesh values
	*/
	struct Mesh
	{
		std::string m_name;
		std::list<Prim> m_prims;
	};

	/**
	* \brief Animation Skin values
	*/
	struct Skin
	{
		std::string m_name;
		int m_invBindMat;
		std::vector<int> m_joints;
	};

	/**
	* \brief Texture values
	*/
	struct Tex
	{
		int m_source; //!< Image source ID
		int m_sampler; //!< Texsampler ID
	};

	/**
	* \brief Connect AniSampler transformation to Node
	*/
	struct Channel
	{
		int m_sampler; //!< AniSampler ID
		int m_node; //!< Target Node ID
		char m_path; //!< Animated property (translation, rotation, scale, weights)
	};

	/**
	* \brief Contains keyframe graph information
	*/
	struct AniSampler
	{
		int m_input; //!< Keyframe input values ID (time)
		int m_output; //!< Keyframe output values
		char m_interpolate; //!< Method of Interpolation (Linear, Step, CubicSpline)
	};

	/**
	* \brief Contains relevant information to parse animation values
	*/
	struct AniParse
	{
		std::string m_name; //!< Animation name
		std::vector<Channel> m_channels; //!< Channels connecting samplers to nodes
		std::vector<AniSampler> m_samplers; //!< Samplers containing keyframe information
	};

	/**
	* \brief Guide to retrieving info in Buffers
	*/
	struct Accessor
	{
		int m_bufferView; //!< BView ID
		int m_byteOffset = 0; //!< Starting position of data in bytes
		int m_compType; //!< Data component type (int, float etc.)
		int m_count; //!< Element total
		std::vector<float> m_max; //!< The max value in data set
		std::vector<float> m_min; //!< The min value in data set
		int m_type; //!< Number of components (scalar, vec4, mat4 etc.)
	};

	/**
	* \brief Stores data from buffer for use in Model/Animation
	*/
	struct AccessData
	{
		std::vector<GLbyte> m_byte;
		std::vector<GLubyte> m_ubyte;
		std::vector<GLshort> m_short;
		std::vector<GLushort> m_ushort;
		std::vector<GLfloat> m_float;
	};

	/**
	* \brief Contains information on reading a buffer (or a subset of it)
	*/
	struct BufferView
	{
		int m_buffer; //!< Buffer ID
		int m_byteLength; //!< Total byte length
		int m_target; //!< GPU buffer target
		int m_byteOffset = 0; //!< Starting position of data in bytes
		int m_byteStride = 0; //!< Gap in bytes between relevant values
	};

	/**
	* \brief Binary file containing Model/Animation values
	*/
	struct Buffer
	{
		int m_byteLength; //!< total byte length
		std::string m_uri; //!< Contains local path to data
	};
}