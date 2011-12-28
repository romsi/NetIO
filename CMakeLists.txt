cmake_minimum_required(VERSION 2.8)

#Configuration du projet
project(NetIO)
set(EXECUTABLE_OUTPUT_PATH ../bin)

include_directories(../source)

#Configuration de l'exécutable
file(
	GLOB_RECURSE
	source_files
	source/*.cpp
)
add_executable(
	server
	${source_files}
)