cmake_minimum_required(VERSION 2.6)
project(COBEBE)

add_library(cobebe
	src/cobebe/dummy.cpp
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
