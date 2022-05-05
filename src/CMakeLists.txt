cmake_minimum_required(VERSION 3.12)
project (Terade VERSION 1.0 LANGUAGES CXX)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_executable(${PROJECT_NAME} main.cpp)

#All header files and source files go inside this block
add_library(LIBRARIES
	portfolio.cpp player.cpp api.cpp view_curses.cpp game.cpp utils.cpp
)

#set_target_properties(LIBRARIES PROPERTIES LINKER_LANGUAGE CXX)
include(FetchContent)

FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.10.5/json.tar.xz)
FetchContent_MakeAvailable(json)

target_link_libraries(${PROJECT_NAME} ${CURSES_LIBRARIES})
target_link_libraries(LIBRARIES nlohmann_json::nlohmann_json)
target_link_libraries(${PROJECT_NAME} LIBRARIES)

target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>		
)
