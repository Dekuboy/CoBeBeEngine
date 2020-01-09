cmake_minimum_required(VERSION 2.6)
project(COBEBE)

include_directories(
	src
)

add_library(glwrap
	src/glwrap/glwrap.h
	src/glwrap/FileManager.h
	src/glwrap/FileManager.cpp
	src/glwrap/Context.h
	src/glwrap/Context.cpp
	src/glwrap/DepthBuffer.h
	src/glwrap/DepthBuffer.cpp
	src/glwrap/DepthCube.h
	src/glwrap/DepthCube.cpp
	src/glwrap/RenderTexture.h
	src/glwrap/RenderTexture.cpp
	src/glwrap/ShaderProgram.h
	src/glwrap/ShaderProgram.cpp
	src/glwrap/Texture.h
	src/glwrap/Texture.cpp
	src/glwrap/VertexArray.h
	src/glwrap/VertexArray.cpp
	src/glwrap/VertexBuffer.h
	src/glwrap/VertexBuffer.cpp
	src/glwrap/stb_image.h
)
if(MSVC)
	target_link_libraries(glwrap glew32 opengl32)
else()
	target_link_libraries(glwrap GLEW GL)
endif()

add_library(cobebe
	src/cobebe/Core/Core.h
	src/cobebe/Core/Core.cpp

	src/cobebe/NonCopyable.h
	src/cobebe/Exception.h
	src/cobebe/Exception.cpp

	src/cobebe/Core/Entity.h
	src/cobebe/Core/Entity.cpp
	src/cobebe/Core/Component.h
	src/cobebe/Core/Component.cpp

	src/cobebe/Core/Transform.h
	src/cobebe/Core/Transform.cpp

	src/cobebe/Collider/tribox.cpp
	src/cobebe/Collider/Collider.h
	src/cobebe/Collider/Collider.cpp
	src/cobebe/Collider/BoxCollider.h
	src/cobebe/Collider/BoxCollider.cpp
	src/cobebe/Collider/StaticModelCollider.h
	src/cobebe/Collider/StaticModelCollider.cpp

	src/cobebe/Core/Environment.h
	src/cobebe/Core/Environment.cpp
	src/cobebe/Core/Keyboard.h
	src/cobebe/Core/Keyboard.cpp
	src/cobebe/Core/Mouse.h
	src/cobebe/Core/Mouse.cpp
	src/cobebe/Core/Gamepad.h
	src/cobebe/Core/Gamepad.cpp

	src/cobebe/Core/Camera.h
	src/cobebe/Core/Camera.cpp

	src/cobebe/Resources/Asset.h
	src/cobebe/Resources/Asset.cpp
	src/cobebe/Resources/Resources.h
	src/cobebe/Resources/Resources.cpp

	src/cobebe/Resources/RendAssets.h
	src/cobebe/Resources/RendAssets.cpp
	src/cobebe/Resources/Sound.h
	src/cobebe/Resources/Sound.cpp

	src/cobebe/Renderer/Renderer.h
	src/cobebe/Renderer/Renderer.cpp
	src/cobebe/Renderer/ShadowRenderer.h
	src/cobebe/Renderer/ShadowRenderer.cpp
	src/cobebe/Renderer/Lighting.h
	src/cobebe/Renderer/Lighting.cpp
	src/cobebe/Renderer/PointLight.h
	src/cobebe/Renderer/PointLight.cpp

	src/cobebe/Speaker/Speaker.h
	src/cobebe/Speaker/Speaker.cpp

	src/cobebe/Cobebe.h
)

target_link_libraries(cobebe 
	SDL2 glwrap OpenAL32
)

add_executable(dungeon
	src/dungeon/PlayerController.h
	src/dungeon/PlayerController.cpp
	src/dungeon/main.cpp
)

target_link_libraries(dungeon 
	cobebe
)
