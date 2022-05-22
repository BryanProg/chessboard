cmake_minimum_required(VERSION 3.16)
project(ChessBoard VERSION 0.0.1 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)

message(STATUS "Build Type: ${CMAKE_BUILD_TYPE}")
message(STATUS "CMAKE Generator: ${CMAKE_GENERATOR}")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# find glfw package
find_package(glfw3 CONFIG REQUIRED)

# find GLEW package
find_package(GLEW REQUIRED)

# find GLM package
find_package(glm REQUIRED)

# find opengl package
find_package(OpenGL REQUIRED)

file(GLOB_RECURSE CBL_SOURCES RELATIVE ${PROJECT_SOURCE_DIR} "src/*.cpp")
file(GLOB_RECURSE CHESSBOARD_SOURCES RELATIVE ${PROJECT_SOURCE_DIR} "tests/main.cpp")

add_library(CBL STATIC ${CBL_SOURCES})

# create executable
add_executable(ChessBoard ${CHESSBOARD_SOURCES})

# link glfw3 library and opengl library
target_link_libraries(CBL PUBLIC ${OPENGL_LIBRARIES} glfw GLEW::GLEW glm::glm)

# link CBLibrary 
target_link_libraries(ChessBoard PUBLIC CBL)