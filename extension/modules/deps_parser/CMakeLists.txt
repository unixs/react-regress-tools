include_directories(include)

link_libraries(parse_thread)

set(NAPI_MODULE_EXPORTS
	parser
	pthread_parser)

set(NAPI_MODULE_LINKS)

foreach(item IN LISTS NAPI_MODULE_EXPORTS)
	add_library(es_${item} OBJECT es_${item}.c)
	list(APPEND NAPI_MODULE_LINKS es_${item})
endforeach()

add_napi_module(${NAPI_MODULE})

target_link_libraries(${NAPI_MODULE}
	${NAPI_MODULE_LINKS})

list(JOIN NAPI_MODULE_EXPORTS ", " NAPI_MODULE_EXPORTS_LIST)
message(STATUS "\t\tExports: " ${NAPI_MODULE_EXPORTS_LIST})
