if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

if(APPLE)
	string(APPEND CMAKE_C_FLAGS_DEBUG " -Wno-compound-token-split-by-macro")
	set(CMAKE_FIND_FRAMEWORK LAST)
	message(STATUS "CMAKE_FIND_FRAMEWORK='${CMAKE_FIND_FRAMEWORK}'")
  	add_link_options(-undefined dynamic_lookup)
endif()

set(CMAKE_C_FLAGS_DEBUG "-O0 -ggdb3 -Wall -Wextra -Wno-unused-parameter")
set(CMAKE_C_FLAGS_RELEASE "-O3")

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
	add_compile_definitions(DEBUG_BUILD)
endif()

if (CMAKE_BUILD_TYPE STREQUAL "Release")
	add_compile_definitions(RELEASE_BUILD)
endif()
