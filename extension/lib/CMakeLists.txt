find_package(CURL REQUIRED)
find_package(Threads REQUIRED)

link_libraries(${GLIB2_LDFLAGS})

if (NOT CMAKE_USE_PTHREADS_INIT)
	message(
		FATAL_ERROR
		"POSIX threads is not found.")
endif()

add_library(parse_thread STATIC parse_thread.c)
target_link_libraries(parse_thread Threads::Threads)
target_include_directories(parse_thread PUBLIC include)
