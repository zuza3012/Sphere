cmake_minimum_required (VERSION 3.5)
project (spheres)

set(glfw3_DIR "/usr/local/include/GLFW")
find_package(PkgConfig REQUIRED)
find_package(X11 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(GLUT REQUIRED)
find_package(glfw3 REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)

set(CMAKE_CXX_FLAGS_DEBUG_INIT "-Wall")
set(CMAKE_CXX_FLAGS_RELEASE_INIT "-Wall")
set(CMAKE_CXX_FLAGS "-std=c++0x")

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

include_directories(
	external/glfw-3.1.2/include/
	external/glm-0.9.7.1/
	external/glew/
	external/assimp-3.0.1270/include/ .
)

include_directories(${X11_INCLUDE_DIR})

set(ALL_LIBS 
	${GLFW_LIBRARIES}
	${GL_LIBRARY}
	${OPENGL_LIBRARY}
	${GLFW3_LIBRARY} 
	#${GLUT_LIBRARY}
	GLEW
	GLEW m dl Xinerama Xrandr Xi Xcursor pthread
	/usr/lib/x86_64-linux-gnu/libX11.so
	/usr/lib/x86_64-linux-gnu/libXxf86vm.so.1
	${X11_LIBRARIES}
)

add_definitions(
	-DTW_STATIC
	-DTW_NO_LIB_PRAGMA
	-DTW_NO_DIRECT3D
	-DGLEW_STATIC
	-D_CRT_SECURE_NO_WARNINGS
)

#include_directories(usr/include/GLFW) # bo nie moze mi znalezc sam glefa :(
#include_directories(${OPENGL_INCLUDE_DIR} ${GLEW_INCLUDE_DIRS} )

add_executable(spheres
    src/main.cpp
)

target_link_libraries(spheres ${ALL_LIBS} )