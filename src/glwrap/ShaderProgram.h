#include <GL/glew.h>
#include <glm/glm.hpp>
#include <fstream>
#include <string>
#include <vector>
#include <memory>

namespace glwrap
{
	class Context;
	class VertexArray;
	class Texture;
	class RenderTexture;
	class DepthBuffer;
	class DepthCube;

	struct Sampler
	{
		GLint m_id;
		std::shared_ptr<Texture> m_texture;
	};

	class ShaderProgram
	{
	public:
		ShaderProgram();
		ShaderProgram(std::string _path);

		void draw();
		void draw(std::shared_ptr<RenderTexture> _renderTexture);
		void draw(std::shared_ptr<VertexArray> _vertexArray);
		void draw(std::shared_ptr<RenderTexture> _renderTexture, std::shared_ptr<VertexArray> _vertexArray);

		void setUniform(std::string _uniform, int _value);
		void setUniform(std::string _uniform, glm::vec4 _value);
		void setUniform(std::string _uniform, glm::vec3 _value);
		void setUniform(std::string _uniform, std::vector<glm::vec3> _vectors);
		void setUniform(std::string _uniform, float _value);
		void setUniform(std::string _uniform, std::vector<float> _floats);
		void setUniform(std::string _uniform, std::shared_ptr<Texture> _texture);
		void setUniform(std::string _uniform, glm::mat4 _matrix);
		void setUniform(std::string _uniform, std::vector<glm::mat4> _matrices);
		void setUniform(std::string _uniform, std::shared_ptr<DepthBuffer> _depth);
		void setUniform(std::string _uniform, std::vector<std::shared_ptr<DepthCube>> _cubes);

		GLuint getId();
		void setViewport(glm::vec4 _viewport);

	private:
		friend class Context;

		GLuint m_id;
		std::vector <Sampler> m_samplers;
		glm::vec4 m_viewport;
		std::shared_ptr<VertexArray> m_simpleShape;
		std::weak_ptr<Context> m_context;

	};
}