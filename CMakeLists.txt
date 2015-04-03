cmake_minimum_required(VERSION 3.1)
project(Ball)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
# Enable debug symbols by default
if(CMAKE_BUILD_TYPE STREQUAL "")
    set(CMAKE_BUILD_TYPE Debug)
endif()

set(STATE_SOURCE_FILES states/triangle_state.cpp states/cube_state.cpp)
set(UTIL_SOURCE_FILES util/shader_loader.cpp)
set(SOURCE_FILES main.cpp game.cpp ${STATE_SOURCE_FILES} ${UTIL_SOURCE_FILES})
set(EXECUTABLE_NAME Ball)
add_executable(${EXECUTABLE_NAME} ${SOURCE_FILES})

file(COPY shaders DESTINATION .)
file(MAKE_DIRECTORY models)
set(MODELS models/cow.obj)
file(COPY ${MODELS} DESTINATION models)

# Set version information in a config.h file
set(ball_VERSION_MAJOR 1)
set(ball_VERSION_MINOR 0)
configure_file(
  "${PROJECT_SOURCE_DIR}/config.h.in"
  "${PROJECT_BINARY_DIR}/config.h"
  )
include_directories("${PROJECT_BINARY_DIR}")

if(MSVC)
	add_subdirectory(lib/glfw)
	include_directories(lib/glfw/include)
	target_link_libraries(${EXECUTABLE_NAME} glfw ${GLFW_LIBRARIES})
else()
	# GLFW
	find_package(PkgConfig REQUIRED)
	pkg_search_module(GLFW REQUIRED glfw3)
	if(GLFW_FOUND)
	    message(STATUS "Found GLFW libraries:")
	    message(STATUS ${GLFW_LIBRARIES})
	    include_directories(${GLFW_INCLUDE_DIRS})
	    target_link_libraries(${EXECUTABLE_NAME} ${GLFW_LIBRARIES})
	endif(GLFW_FOUND)
endif()

# GLEW
find_package(GLEW REQUIRED)
if(GLEW_FOUND)
    message(STATUS "Found GLEW libraries:")
    message(STATUS ${GLEW_LIBRARIES})
    include_directories(${GLEW_INCLUDE_PATH})
    target_link_libraries(${EXECUTABLE_NAME} ${GLEW_LIBRARIES})
endif(GLEW_FOUND)

# OpenGL
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})
if (OPENGL_FOUND)
  target_link_libraries(${EXECUTABLE_NAME} ${OPENGL_LIBRARIES})
  # or: target_link_libraries(${EXECUTABLE_NAME} ${OPENGL_gl_LIBRARY})
  target_link_libraries(${EXECUTABLE_NAME} m)  # if you use maths.h
endif()

# boost::filesystem
#set(Boost_ADDITIONAL_VERSIONS "1.78" "1.78.0" "1.79" "1.79.0")
#find_package(Boost REQUIRED system filesystem)
#if(Boost_FOUND)
#  include_directories(${Boost_INCLUDE_DIRS})
#  target_link_libraries(${EXECUTABLE_NAME} ${Boost_LIBRARIES})
#endif()

# GLM
find_package(GLM REQUIRED)
if(GLM_FOUND)
    include_directories(${GLM_INCLUDE_DIRS})
endif(GLM_FOUND)


IF(APPLE)
    SET(EXTRA_LIBS "-framework Cocoa -framework OpenGL")
ELSEIF(MSVC)
	SET(EXTRA_LIBS "glu32.lib" "opengl32.lib")
ELSE(APPLE)
    SET(EXTRA_LIBS ${GLFW_LDFLAGS_OTHER})
ENDIF(APPLE)


# Install target
install(TARGETS ${EXECUTABLE_NAME} DESTINATION bin)


# CPack packaging
include(InstallRequiredSystemLibraries)
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/COPYING")
set(CPACK_PACKAGE_VERSION_MAJOR "${myproject_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${myproject_VERSION_MINOR}")
include(CPack)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

