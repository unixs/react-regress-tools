include_directories(include)
link_libraries(utils)

add_library(test OBJECT test.c)
add_library(exports OBJECT exports.c)


message(STATUS "	Configured N-API module: " ${NAPI_MODULE})
add_napi_module(${NAPI_MODULE})
target_link_libraries(${NAPI_MODULE} exports)
