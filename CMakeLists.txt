cmake_minimum_required(VERSION 3.22)
cmake_policy(SET CMP0042 NEW)
cmake_policy(SET CMP0091 NEW)

project(regress-tools-node
	VERSION 0.1.0
	LANGUAGES C)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_EXTENSIONS ON)
set(CMAKE_C_STANDARD_REQUIRED ON)

include(CheckCPUFlags)
include(BuildConfig)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/build/${CMAKE_BUILD_TYPE})

add_subdirectory(extension)

# enable_testing()

# set(COVERAGE_LINES_PERCENT 90)

# add_test(
#	 NAME coverage
#	 COMMAND "gcovr" "-sp" "-r" ".." "--print-summary" "--fail-under-line" ${COVERAGE_LINES_PERCENT} ".")
