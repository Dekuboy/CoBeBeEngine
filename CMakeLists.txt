cmake_minimum_required(VERSION 2.6)
project(COBEBE)

include_directories(
	src
)

add_library(rend
  src/rend/Exception.cpp
  src/rend/Context.cpp
  src/rend/Texture.cpp
  src/rend/RenderTexture.cpp
  src/rend/Shader.cpp
  src/rend/Buffer.cpp
  src/rend/Mesh.cpp
  src/rend/Util.cpp
)
if(MSVC)
  target_link_libraries(rend glew32 opengl32)
else()
  target_link_libraries(rend GLEW GL)
endif()

add_library(cobebe
	src/cobebe/Core.h
	src/cobebe/Core.cpp
	src/cobebe/NonCopyable.h
	src/cobebe/Entity.h
	src/cobebe/Entity.cpp
	src/cobebe/Component.h
	src/cobebe/Component.cpp
	src/cobebe/Environment.h
	src/cobebe/Environment.cpp
	src/cobebe/Keyboard.h
	src/cobebe/Keyboard.cpp
	src/cobebe/Mouse.h
	src/cobebe/Mouse.cpp
	src/cobebe/Exception.h
	src/cobebe/Exception.cpp
	src/cobebe/Renderer.h
	src/cobebe/Renderer.cpp

	src/cobebe/TriangleRenderer.h
	src/cobebe/TriangleRenderer.cpp

	src/cobebe/Cobebe.h
)

target_link_libraries(cobebe 
	SDL2 rend
)

add_executable(dungeon
	src/dungeon/main.cpp
)

target_link_libraries(dungeon 
	cobebe
)
