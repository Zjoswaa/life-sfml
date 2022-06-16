cmake_minimum_required(VERSION 3.22)
project(life_sfml)

set(CMAKE_CXX_STANDARD 23)

add_executable(life_sfml main.cpp Game.cpp Game.h constants.h)

set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR C:/SFML/lib/cmake/SFML)
find_package(SFML COMPONENTS system window graphics network audio REQUIRED)

include_directories(C:/SFML/include)
target_link_libraries(life_sfml sfml-system sfml-window sfml-graphics sfml-audio sfml-network)