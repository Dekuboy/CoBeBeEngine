cmake_minimum_required(VERSION 2.6)
project(COBEBE)

include_directories(
	src
)

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

	src/cobebe/TriangleRenderer.h
	src/cobebe/TriangleRenderer.cpp

	src/cobebe/Cobebe.h
)

target_link_libraries(cobebe 
	SDL2 opengl32 glew32
)

add_executable(dungeon
	src/dungeon/main.cpp
)

target_link_libraries(dungeon 
	cobebe
)
