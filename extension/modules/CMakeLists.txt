set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)
message(STATUS "Node build architecture: " ${CMAKE_SYSTEM_PROCESSOR})

include_directories(include)

include(NodeJS)
include(NodeModule)

set(NAPI_MODULES
	deps_parser)

add_subdirectory(utils)

foreach(MOD IN LISTS NAPI_MODULES)
	set(NAPI_MODULE ${MOD})
	add_subdirectory(${MOD})
endforeach()

