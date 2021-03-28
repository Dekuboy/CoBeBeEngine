#include <glwrap/TextureUniforms.h>

namespace glwrap
{
	enum PBRTexture
	{
		colour,
		metalRough,
		normal,
		occlusion,
		emissive,
		colourFactor,
		metalRoughFactor,
		normalFactor,
		occlusionFactor,
		emissiveFactor
	};

	class SingleUniform : public TextureUniforms
	{
	public:
		void getUniformName(int _enumType, std::string& _target);
		bool setUniformName(int _enumType, std::string& _name);

	private:
		std::string m_textureName;

	};

	class PBRUniforms : public TextureUniforms
	{
	public:
		PBRUniforms();

		void getUniformName(int _enumType, std::string& _target);
		bool setUniformName(int _enumType, std::string& _name);

	private:
		std::vector<std::string> m_pbrTextureNames;

	};
}