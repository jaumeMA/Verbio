file(GLOB SOURCES_CPP RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "*.cpp")
file(GLOB_RECURSE HEADERS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "*.h")
file(GLOB_RECURSE HEADERS_INL RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "*.inl")

set(SOURCES ${SOURCES_CPP} ${SOURCES_ASM})