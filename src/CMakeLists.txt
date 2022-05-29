cmake_minimum_required(VERSION 3.12)
project (Terade VERSION 1.0 LANGUAGES CXX)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(../HTTPRequest/include)

add_executable(${PROJECT_NAME} main.cpp)

#All header files and source files go inside this block
add_library(LIBRARIES
	portfolio.cpp player.cpp api.cpp view_curses.cpp game.cpp utils.cpp output.cpp
	file_manager.cpp options.cpp commands.cpp
)

#set_target_properties(LIBRARIES PROPERTIES LINKER_LANGUAGE CXX)
include(FetchContent)

FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.10.5/json.tar.xz)
FetchContent_MakeAvailable(json)

#FetchContent_Declare(cpr GIT_REPOSITORY https://github.com/libcpr/cpr.git GIT_TAG 6ea2dec23c3df14ac3b27b7d2d6bbff0cb7ba1b0)
#FetchContent_MakeAvailable(cpr)

target_link_libraries(LIBRARIES ${CURSES_LIBRARIES})
target_link_libraries(LIBRARIES nlohmann_json::nlohmann_json)
#target_link_libraries(LIBRARIES cpr::cpr)
target_link_libraries(${PROJECT_NAME} LIBRARIES)

target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>		
)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/data/all_coins.json
	${CMAKE_CURRENT_SOURCE_DIR}/data/bitcoin.json
	${CMAKE_CURRENT_SOURCE_DIR}/data/ethereum.json
	${CMAKE_CURRENT_SOURCE_DIR}/data/cardano.json
	${CMAKE_CURRENT_SOURCE_DIR}/data/dogecoin.json
	${CMAKE_CURRENT_SOURCE_DIR}/data/binancecoin.json
	${CMAKE_CURRENT_SOURCE_DIR}/data/stellar.json
	${CMAKE_CURRENT_SOURCE_DIR}/data/maker.json
	DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
