#ifndef _GLWRAP_TEXTURE_UNIFORMS
#define _GLWRAP_TEXTURE_UNIFORMS
#include <string>
#include <vector>

namespace glwrap
{
	class ShaderProgram;

	class TextureUniforms
	{
	public:
		virtual void getUniformName(int _enumType, std::string& _target) {}
		virtual bool setUniformName(int _enumType, std::string& _name) { return false; }

	private:
		friend class ShaderProgram;
		std::vector<std::string> m_uniformNames;
		std::vector<int> m_uniformIds;

	};
}
#endif