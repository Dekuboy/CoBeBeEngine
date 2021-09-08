#include <GL/glew.h>
#include <glm/glm.hpp>

#include <string>
#include <vector>
#include <list>

namespace gltfparse
{
	struct Scene
	{
		std::string m_name;
		std::vector<int> m_nodes;
	};

	struct Node
	{
		std::string m_name;
		std::vector<int> m_children;
		int m_mesh = -1;
		int m_skin = -1;
		std::vector<float> m_translation;
		std::vector<float> m_scale;
		std::vector<float> m_rotation;
		std::vector<float> m_matrix;
	};

	struct Image
	{
		std::string m_uri;
		int m_bufferView;
		std::string m_mimeType;
	};

	struct MatTex
	{
		int m_index = -1;
		char m_texCoord;
		float m_scale;
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

	struct TexSampler
	{
		int m_magFilter;
		int m_minFilter;
		int m_wrapS;
		int m_wrapT;
	};

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

	struct Mesh
	{
		std::string m_name;
		std::list<Prim> m_prims;
	};

	struct Skin
	{
		std::string m_name;
		int m_invBindMat;
		std::vector<int> m_joints;
	};

	struct Tex
	{
		int m_source;
		int m_sampler;
	};

	struct Channel
	{
		int m_sampler;
		int m_node;
		char m_path;
	};

	struct AniSampler
	{
		int m_input;
		int m_output;
		char m_interpolate;
	};

	struct AniParse
	{
		std::string m_name;
		std::vector<Channel> m_channels;
		std::vector<AniSampler> m_samplers;
	};

	struct Accessor
	{
		int m_bufferView;
		int m_byteOffset = 0;
		int m_compType;
		int m_count;
		std::vector<float> m_max;
		std::vector<float> m_min;
		int m_type;
	};

	struct AccessData
	{
		std::vector<GLbyte> m_byte;
		std::vector<GLubyte> m_ubyte;
		std::vector<GLshort> m_short;
		std::vector<GLushort> m_ushort;
		std::vector<GLfloat> m_float;
	};

	struct BufferView
	{
		int m_buffer;
		int m_byteLength;
		int m_target;
		int m_byteOffset = 0;
		int m_byteStride = 0;
	};

	struct Buffer
	{
		int m_byteLength;
		std::string m_uri;
	};
}