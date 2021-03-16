#include <memory>
#include <string>

namespace glwrap
{
	class VertexBuffer;
	class VertexArray;
	class ObjPart;
	class ObjAnimation;
	class Texture;
	class RenderTexture;
	class GBuffer;
	class DepthBuffer;
	class DepthCube;
	class ShaderProgram;
	class ObjMtlModel;
	class GltfModel;

	/**
	* \brief The OpenGL Context
	* -loads:   Obj models
	*             + mtl files optionally
	*           Obj Animation Files
	*           Textures
	*           Shaders
	* -creates: RenderTextures (fbo objects)
	*           DepthBuffer
	*/
	class Context
	{
	public:
		/**
		* \brief Initialise the OpenGL Context
		* -calls glewInit()
		*/
		static std::shared_ptr<Context> initialise();

		/**
		* \brief Create Texture within glwrap Context
		*/
		std::shared_ptr<Texture> createTexture(std::string _path);
		/**
		* \brief Create Shader within glwrap Context
		*/
		std::shared_ptr<ShaderProgram> createShader(std::string _path);
		/**
		* \brief Create Buffer within glwrap Context
		*/
		std::shared_ptr<VertexBuffer> createBuffer();
		/**
		* \brief Create Mesh within glwrap Context
		*/
		std::shared_ptr<VertexArray> createMesh();
		/**
		* \brief Create Mesh within glwrap Context
		* -parses as .obj
		*/
		std::shared_ptr<VertexArray> createMesh(std::string _path);
		/**
		* \brief Create Mesh within glwrap Context
		* -parses as .obj
		* -precalculate tangentBitangentNormal matrix if _calcTanBitan
		*/
		std::shared_ptr<VertexArray> createMesh(std::string _path, bool _calcTanBitan);
		/**
		* \brief Create WavefrontModel within glwrap Context
		*/
		std::shared_ptr<ObjMtlModel> createObjMtlMesh(std::string _path);
		/**
		* \brief Create WavefrontModel within glwrap Context
		* -precalculate tangentBitangentNormal matrix if _calcTanBitan
		*/
		std::shared_ptr<ObjMtlModel> createObjMtlMesh(std::string _path, bool _calcTanBitan);
		/**
		* \brief Create ObjPart within glwrap Context
		*/
		std::shared_ptr<ObjPart> createPart(std::shared_ptr<VertexArray> _mesh, std::string _name);
		/**
		* \brief Create Model within glwrap Context using .gltf
		*/
		std::shared_ptr<GltfModel> createModel(std::string _path);
		/**
		* \brief Create Model within glwrap Context using .gltf
		* -precalculate tangentBitangentNormal matrix if _calcTanBitan
		*/
		std::shared_ptr<GltfModel> createModel(std::string _path, bool _calcTanBitan);
		/**
		* \brief Create ObjAnimation within glwrap Context
		*/
		std::shared_ptr<ObjAnimation> createAnimation(std::shared_ptr<VertexArray> _model);
		/**
		* \brief Create ObjAnimation within glwrap Context
		*/
		std::shared_ptr<ObjAnimation> createAnimation(std::shared_ptr<VertexArray> _model, std::string _path);
		/**
		* \brief Create RenderTexture within glwrap Context
		*/
		std::shared_ptr<RenderTexture> createRenderTexture(int _width, int _height);
		/**
		* \brief Create Multisampling RenderTexture within glwrap Context
		* -_multiSamples = input numder of samples to generate
		*/
		std::shared_ptr<RenderTexture> createRenderTexture(int _width, int _height, int _multisamples);
		/**
		* \brief Create DepthBuffer within glwrap Context
		*/
		std::shared_ptr<DepthBuffer> createDepthBuffer(int _width, int _height);
		/**
		* \brief Create DepthCube within glwrap Context
		*/
		std::shared_ptr<DepthCube> createDepthCube(int _width, int _height);
		/**
		* \brief Create GBuffer within glwrap Context
		*/
		std::shared_ptr<GBuffer> createGBuffer(int _width, int _height);

		/**
		* \brief Gets ShaderProgram currently being used by Context
		*/
		std::shared_ptr<ShaderProgram> getCurrentShader();
		/**
		* \brief Sets new ShaderProgram to be used by Context
		*/
		void setCurrentShader(std::shared_ptr<ShaderProgram> _shader);

	private:
		std::weak_ptr<ShaderProgram> m_currentShader; //!< Stores ShaderProgram currently in use

		std::weak_ptr<Context> m_self; //!< Pointer to self to be passed into created object

	};
}