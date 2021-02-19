cmake_minimum_required(VERSION 3.1)

project(blangs
	LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

find_package(Boost REQUIRED COMPONENTS system)
find_package(Threads REQUIRED)
find_package(spdlog REQUIRED)

file(GLOB_RECURSE sources
	"${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

add_executable(blangs "${sources}")
target_link_libraries(blangs
	PUBLIC
		Boost::boost
		Boost::system
		Threads::Threads
		spdlog::spdlog)
target_include_directories(blangs
	PUBLIC
		"${CMAKE_CURRENT_SOURCE_DIR}/3rd_party/CLI11/include"
		"${CMAKE_CURRENT_SOURCE_DIR}/3rd_party/json/include")
