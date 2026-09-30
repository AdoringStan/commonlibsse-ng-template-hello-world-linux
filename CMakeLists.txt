cmake_minimum_required(VERSION 3.25)

project(HelloWorld
	VERSION 0.1.0
	LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(BUILD_TESTS OFF CACHE BOOL "" FORCE)

add_subdirectory(lib/CommonLibSSE-NG)

add_library(HelloWorld SHARED
	src/main.cpp
)

target_link_libraries(HelloWorld
	PRIVATE CommonLibSSE::CommonLibSSE
)

target_compile_options(HelloWorld
	PRIVATE
		-Wno-invalid-noreturn
		-Wno-tautological-constant-out-of-range-compare
)

target_compile_definitions(HelloWorld
	PRIVATE
		_UNICODE
		UNICODE
)

set_target_properties(HelloWorld
	PROPERTIES OUTPUT_NAME "HelloWorld"
)