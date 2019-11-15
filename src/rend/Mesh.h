#include <sr1/vector>
#include <sr1/memory>

#include <string>

namespace rend
{

struct Buffer;
struct Context;
struct Shader;
struct TextureAdapter;

struct BufferData
{
  std::string name;
  std::sr1::shared_ptr<Buffer> buffer;
};

struct TextureData
{
  std::string name;
  std::sr1::shared_ptr<TextureAdapter> texture;
};

struct Mesh
{
  void setBuffer(const std::string& name, const std::sr1::shared_ptr<Buffer>& buffer);
  void setTexture(const std::string& name, const std::sr1::shared_ptr<TextureAdapter>& texture);
  void parse(const std::string& data);

private:
  friend struct Context;
  friend struct Shader;

  std::sr1::shared_ptr<Context> context;
  std::sr1::vector<std::sr1::shared_ptr<BufferData> > buffers;
  std::sr1::vector<std::sr1::shared_ptr<TextureData> > textures;

  void safeParse(const std::string& data, std::string& currentLine);

};

}
