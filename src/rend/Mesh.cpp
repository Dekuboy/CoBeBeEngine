#include "Mesh.h"
#include "Util.h"
#include "mathutil.h"
#include "Context.h"
#include "Buffer.h"
#include "Exception.h"

namespace rend
{

struct Face
{
  vec3 pa;
  vec3 pb;
  vec3 pc;

  vec2 tca;
  vec2 tcb;
  vec2 tcc;

  vec3 na;
  vec3 nb;
  vec3 nc;

  vec2 lmca;
  vec2 lmcb;
  vec2 lmcc;
};

void Mesh::setBuffer(const std::string& name, const std::sr1::shared_ptr<Buffer>& buffer)
{
  for(std::sr1::vector<std::sr1::shared_ptr<BufferData> >::iterator it =
    buffers.begin(); it != buffers.end(); it++)
  {
    if((*it)->name == name)
    {
      (*it)->buffer = buffer;

      return;
    }
  }

  std::sr1::shared_ptr<BufferData> bd = std::sr1::make_shared<BufferData>();
  bd->name = name;
  bd->buffer = buffer;
  buffers.push_back(bd);
}

void Mesh::setTexture(const std::string& name, const std::sr1::shared_ptr<TextureAdapter>& texture)
{
  for(std::sr1::vector<std::sr1::shared_ptr<TextureData> >::iterator it =
    textures.begin(); it != textures.end(); it++)
  {
    if((*it)->name == name)
    {
      (*it)->texture = texture;

      return;
    }
  }

  std::sr1::shared_ptr<TextureData> td = std::sr1::make_shared<TextureData>();
  td->name = name;
  td->texture = texture;
  textures.push_back(td);
}

void Mesh::parse(const std::string& data)
{
  std::string currentLine;

  try
  {
    safeParse(data, currentLine);
  }
  catch(std::exception& e)
  {
    throw Exception("Failed to parse model data [" + currentLine + "]");
  }
}

void Mesh::safeParse(const std::string& data, std::string& currentLine)
{
  std::sr1::vector<std::string> lines;
  Util::splitStringLineEnding(data, lines);

  std::sr1::vector<vec3> positions;
  std::sr1::vector<vec2> tcs;
  std::sr1::vector<vec3> normals;
  std::sr1::vector<vec2> lmcs;
  std::sr1::vector<Face> faces;

  for(std::sr1::vector<std::string>::iterator lit = lines.begin();
    lit != lines.end(); lit++)
  {
    currentLine = *lit;
    if(lit->length() < 1) continue;
    //std::cout << "Line [" << *lit << "]" << std::endl;

    std::sr1::vector<std::string> tokens;
    Util::splitStringWhitespace(*lit, tokens);
    if(tokens.size() < 1) continue;

    if(tokens.at(0) == "v")
    {
      vec3 p(atof(tokens.at(1).c_str()),
        atof(tokens.at(2).c_str()),
        atof(tokens.at(3).c_str()));

      positions.push_back(p);
    }
    else if(tokens.at(0) == "vt")
    {
      vec2 tc(atof(tokens.at(1).c_str()),
        atof(tokens.at(2).c_str()));

      tcs.push_back(tc);
    }
    else if(tokens.at(0) == "vn")
    {
      vec3 n(atof(tokens.at(1).c_str()),
        atof(tokens.at(2).c_str()),
        atof(tokens.at(3).c_str()));

      normals.push_back(n);
    }
    else if(tokens.at(0) == "f")
    {
      if(tokens.size() < 4) continue;

      Face f;
      std::sr1::vector<std::string> sub;
      Util::splitString(tokens.at(1), '/', sub);
      if(sub.size() >= 1) f.pa = positions.at(atoi(sub.at(0).c_str()) - 1);
      if(sub.size() >= 2) f.tca = tcs.at(atoi(sub.at(1).c_str()) - 1);
      if(sub.size() >= 3) f.na = normals.at(atoi(sub.at(2).c_str()) - 1);
      if(sub.size() >= 4) f.lmca = lmcs.at(atoi(sub.at(3).c_str()) - 1);

      Util::splitString(tokens.at(2), '/', sub);
      if(sub.size() >= 1) f.pb = positions.at(atoi(sub.at(0).c_str()) - 1);
      if(sub.size() >= 2) f.tcb = tcs.at(atoi(sub.at(1).c_str()) - 1);
      if(sub.size() >= 3) f.nb = normals.at(atoi(sub.at(2).c_str()) - 1);
      if(sub.size() >= 4) f.lmcb = lmcs.at(atoi(sub.at(3).c_str()) - 1);

      Util::splitString(tokens.at(3), '/', sub);
      if(sub.size() >= 1) f.pc = positions.at(atoi(sub.at(0).c_str()) - 1);
      if(sub.size() >= 2) f.tcc = tcs.at(atoi(sub.at(1).c_str()) - 1);
      if(sub.size() >= 3) f.nc = normals.at(atoi(sub.at(2).c_str()) - 1);
      if(sub.size() >= 4) f.lmcc = lmcs.at(atoi(sub.at(3).c_str()) - 1);

      faces.push_back(f);
      if(tokens.size() < 5) continue;

      Face fq;
      fq.pa = f.pc;
      fq.tca = f.tcc;
      fq.na = f.nc;
      fq.lmca = f.lmcc;

      Util::splitString(tokens.at(4), '/', sub);
      if(sub.size() >= 1) fq.pb = positions.at(atoi(sub.at(0).c_str()) - 1);
      if(sub.size() >= 2) fq.tcb = tcs.at(atoi(sub.at(1).c_str()) - 1);
      if(sub.size() >= 3) fq.nb = normals.at(atoi(sub.at(2).c_str()) - 1);
      if(sub.size() >= 4) fq.lmcb = lmcs.at(atoi(sub.at(3).c_str()) - 1);

      fq.pc = f.pa;
      fq.tcc = f.tca;
      fq.nc = f.na;
      fq.lmcc = f.lmca;

      faces.push_back(fq);
    }
  }

  if(positions.size() > 0)
  {
    std::sr1::shared_ptr<Buffer> b = context->createBuffer();

    for(std::sr1::vector<Face>::iterator fit = faces.begin();
      fit != faces.end(); fit++)
    {
      b->add(fit->pa);
      b->add(fit->pb);
      b->add(fit->pc);
    }

    setBuffer("a_Position", b);
  }

  if(tcs.size() > 0)
  {
    std::sr1::shared_ptr<Buffer> b = context->createBuffer();

    for(std::sr1::vector<Face>::iterator fit = faces.begin();
      fit != faces.end(); fit++)
    {
      b->add(fit->tca);
      b->add(fit->tcb);
      b->add(fit->tcc);
    }

    setBuffer("a_TexCoord", b);
  }

  if(normals.size() > 0)
  {
    std::sr1::shared_ptr<Buffer> b = context->createBuffer();

    for(std::sr1::vector<Face>::iterator fit = faces.begin();
      fit != faces.end(); fit++)
    {
      b->add(fit->na);
      b->add(fit->nb);
      b->add(fit->nc);
    }

    setBuffer("a_Normal", b);
  }

  if(lmcs.size() > 0)
  {
    std::sr1::shared_ptr<Buffer> b = context->createBuffer();

    for(std::sr1::vector<Face>::iterator fit = faces.begin();
      fit != faces.end(); fit++)
    {
      b->add(fit->lmca);
      b->add(fit->lmcb);
      b->add(fit->lmcc);
    }

    setBuffer("a_LightMapCoord", b);
  }
}

}
