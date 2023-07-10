include_directories(include)

add_library(utils
	OBJECT
	utils.c)

target_include_directories(utils INTERFACE include)
