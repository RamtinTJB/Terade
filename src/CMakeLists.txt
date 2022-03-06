cmake_minimum_required(VERSION 3.12)
project (Terade VERSION 1.0 LANGUAGES CXX)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

add_executable(${PROJECT_NAME} main.cpp)

#All header files and source files go inside this block
#add_library(LIBRARIES
#	test.h		
#)

#set_target_properties(LIBRARIES PROPERTIES LINKER_LANGUAGE CXX)

#target_link_libraries(${PROJECT_NAME} LIBRARIES)
target_link_libraries(${PROJECT_NAME} ${CURSES_LIBRARIES})

target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>		
)
