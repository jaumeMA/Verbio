include(WhiteList.cmake)
include(CompilerFlags.cmake)

project(Verbio)

add_executable(Verbio ${SOURCES} ${HEADERS})

target_include_directories(Verbio PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_include_directories(Verbio PUBLIC ${EXTERNAL_DIR})

target_link_libraries(Verbio
	${LOCAL_MODULE_DEPENDENCIES}
	${THIRD_PARTY_DEPENDENCIES})

set_target_properties(Verbio PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${OUTPUT_DIR}")
set_target_properties(Verbio PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(Verbio PROPERTIES FOLDER "Verbio")