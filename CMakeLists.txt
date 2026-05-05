cmake_minimum_required (VERSION 3.13 FATAL_ERROR) 
set(PROJ BattleCity)
project(${PROJ})	
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_executable(${PROJ} src/main.cpp
	src/renderer/ShaderProgram.cpp
	src/renderer/ShaderProgram.h
	src/resources/ResourceManager.cpp
	src/resources/ResourceManager.h

)
 
target_compile_features(${PROJ} PUBLIC cxx_std_17)


set (GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set (GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set (GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set (GLFW_BUILD_INSTALL OFF CACHE BOOL "" FORCE)

add_subdirectory(external/glfw)
target_link_libraries(${PROJ} glfw)
add_subdirectory(external/glad)
target_link_libraries(${PROJ} glad)

#find_package(OpenGL REQUIRED)
#target_link_libraries(${PROJ} OpenGL::GL)



set_target_properties(${PROJ} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/")
add_custom_command(TARGET ${PROJ} POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory
	${CMAKE_SOURCE_DIR}/res  $<TARGET_FILE_DIR:${PROJ}>/res
)
