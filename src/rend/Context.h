#include <sr1/memory>

namespace rend
{

struct Texture;
struct Shader;
struct Buffer;
struct RenderTexture;
struct Mesh;

struct Context
{
  static std::sr1::shared_ptr<Context> initialize();

  std::sr1::shared_ptr<Texture> createTexture();
  std::sr1::shared_ptr<Shader> createShader();
  std::sr1::shared_ptr<Buffer> createBuffer();
  std::sr1::shared_ptr<Mesh> createMesh();
  std::sr1::shared_ptr<RenderTexture> createRenderTexture();

private:
  std::sr1::weak_ptr<Context> self;

};

}
