cmake_minimum_required(VERSION 2.6)
project(COBEBE)

include_directories(
	src
)

add_library(cobebe
	src/cobebe/Core.h
	src/cobebe/Core.cpp
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
