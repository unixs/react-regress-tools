# set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib/${CMAKE_BUILD_TYPE})
message(STATUS "Node build architecture: " ${CMAKE_SYSTEM_PROCESSOR})

include(NodeJS)
include(NodeModule)

include_directories(include)

add_subdirectory(utils)

link_libraries(utils)

set(NAPI_MODULES
	deps_parser
	example)

foreach(MOD IN LISTS NAPI_MODULES)
	set(NAPI_MODULE ${MOD})
	add_subdirectory(${MOD})
endforeach()

