include_directories(include)

add_library(es_parser OBJECT es_parser.c)
target_link_libraries(es_parser
	parse_thread)

add_napi_module(${NAPI_MODULE})

target_link_libraries(${NAPI_MODULE}
	es_parser)
