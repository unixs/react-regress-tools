include(CheckSymbolExists)
find_package(PkgConfig REQUIRED)

pkg_check_modules(GLIB2 REQUIRED glib-2.0)

include_directories(${GLIB2_INCLUDE_DIRS})
link_libraries(${GLIB2_LDFLAGS})

list(APPEND CMAKE_REQUIRED_LIBRARIES ${GLIB2_LDFLAGS})
list(APPEND CMAKE_REQUIRED_INCLUDES ${GLIB2_INCLUDE_DIRS})
