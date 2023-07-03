if(NOT DEFINED CMAKE_JS_INC)
	message(STATUS "CMAKE_JS_INC is not direct defined.")
	if(DEFINED ENV{CMAKE_JS_INC})
		message(STATUS "Pass CMAKE_JS_INC from env.")
		set(CMAKE_JS_INC $ENV{CMAKE_JS_INC})
	endif()

	if(NOT CMAKE_JS_INC)
		message(
			FATAL_ERROR
			"CMAKE_JS_INC is not defined. Try checking your CMake.js configuration.")
	endif()
endif()
message(STATUS "CMAKE_JS_INC: ${CMAKE_JS_INC}")

include_directories(${CMAKE_JS_INC})
link_libraries(${CMAKE_JS_LIB})
