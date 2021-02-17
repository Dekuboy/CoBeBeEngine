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
	class Model;
	class Texture;
	class RenderTexture;
	class GBuffer;
	class DepthBuffer;
	class DepthCube;
	class ViewingFrustum;

	enum gType
	{
		pos,
		norm,
		albed
	};

	struct Sampler
	{
		GLint m_id;
		std::shared_ptr<Texture> m_texture;
		std::shared_ptr<DepthCube> m_depthCube;
		std::shared_ptr<GBuffer> m_gBuffer;
		gType m_gType;
	};

	class ShaderProgram
	{
	public:
		ShaderProgram();
		ShaderProgram(std::string _path);

		void parse(std::string _path);

		void draw();
		void draw(std::shared_ptr<RenderTexture> _renderTexture);
		void draw(std::shared_ptr<VertexArray> _vertexArray);
		void draw(std::shared_ptr<RenderTexture> _renderTexture, std::shared_ptr<VertexArray> _vertexArray);
		void draw(std::shared_ptr<Model> _model, std::string _textureUniform);
		void draw(std::shared_ptr<RenderTexture> _renderTexture, std::shared_ptr<Model> _model, std::string _textureUniform);

		void cullAndDraw(std::shared_ptr<VertexArray> _vertexArray, 
			glm::vec3 &_centre, glm::vec3 &_size, glm::mat3 &_rotation);
		void cullAndDraw(std::shared_ptr<RenderTexture> _renderTexture, 
			std::shared_ptr<VertexArray> _vertexArray, 
			glm::vec3 &_centre, glm::vec3 &_size, glm::mat3 &_rotation);
		void cullAndDraw(std::shared_ptr<Model> _model, std::string _textureUniform, 
			glm::vec3 &_centre, glm::vec3 &_size, glm::mat3 &_rotation);
		void cullAndDraw(std::shared_ptr<RenderTexture> _renderTexture, 
			std::shared_ptr<Model> _model, std::string _textureUniform, 
			glm::vec3 &_centre, glm::vec3 &_size, glm::mat3 &_rotation);

		std::shared_ptr<ViewingFrustum> getViewingFrustum();
		void setViewingFrustum(std::shared_ptr<ViewingFrustum> _frustum);
		bool checkViewingFrustum(const glm::vec3 &_centre, const glm::vec3 &_size, const glm::mat3 &_rotation);

		void setUniform(std::string _uniform, int _value);
		void setUniform(std::string _uniform, glm::vec4 _value);
		void setUniform(std::string _uniform, glm::vec3 _value);
		void setUniform(std::string _uniform, glm::vec2 _value);
		void setUniform(std::string _uniform, std::vector<glm::vec3> &_vectors);
		void setUniform(std::string _uniform, float _value);
		void setUniform(std::string _uniform, std::vector<float> &_floats);
		void setUniform(std::string _uniform, std::shared_ptr<Texture> _texture);
		void setUniform(std::string _uniform, glm::mat4 &_matrix);
		void setUniform(std::string _uniform, std::vector<glm::mat4> &_matrices);
		void setUniform(std::string _uniform, std::shared_ptr<DepthBuffer> _depth);
		void setUniform(std::string _uniform, std::shared_ptr<DepthCube> _depthCube);
		void setUniform(std::string _uniform, std::vector<std::shared_ptr<DepthCube> > &_cubes);
		void setUniform(std::shared_ptr<GBuffer> _gBuffer);

		GLuint getId();

		void setViewport(glm::vec4 _viewport);

	private:
		friend class Context;

		GLuint m_id;
		std::vector <Sampler> m_samplers;
		bool m_isDrawing;
		glm::vec3 m_drawingCentre;
		glm::vec3 m_drawingSize;
		glm::mat3 m_drawingRotation;
		glm::vec4 m_viewport;
		std::shared_ptr<ViewingFrustum> m_viewingFrustum;
		std::shared_ptr<VertexArray> m_simpleShape;
		std::weak_ptr<ShaderProgram> m_self;
		std::weak_ptr<Context> m_context;

		void setSamplers();
		void resetSamplers();

	};
}