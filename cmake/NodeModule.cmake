function(add_napi_module name)
	add_library(${name}
		SHARED
		module.c)

	set_target_properties(${name}
		PROPERTIES
		OUTPUT_NAME ${name}-${CMAKE_SYSTEM_PROCESSOR}
		PREFIX ""
		SUFFIX ".node")

	target_link_libraries(${name} utils)
endfunction()
