cmake_minimum_required(VERSION 3.13.0)

project("Verbio")

# system vars
include("${CMAKE_SOURCE_DIR}/SetupConfig.cmake")

set(SRC_DIR "${CMAKE_SOURCE_DIR}/src")
set(TEST_DIR "${CMAKE_SOURCE_DIR}/test")

set(TARGET_DIR "${CMAKE_SOURCE_DIR}/build")
set(OUTPUT_DIR "${CMAKE_SOURCE_DIR}/bin")

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

###	SETTING INSTALLED LIBRARIES	###

add_subdirectory("${SRC_DIR}")