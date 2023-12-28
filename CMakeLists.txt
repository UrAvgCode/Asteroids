cmake_minimum_required(VERSION 3.11)

project(Asteroids)
set(CMAKE_CXX_STANDARD 17)

set(RAYLIB_VERSION 4.5.0)
find_package(raylib ${RAYLIB_VERSION} QUIET) # QUIET or REQUIRED
if (NOT raylib_FOUND) # If there's none, fetch and build raylib
  include(FetchContent)
  FetchContent_Declare(
    raylib
    DOWNLOAD_EXTRACT_TIMESTAMP OFF
    URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
  )
  FetchContent_GetProperties(raylib)
  if (NOT raylib_POPULATED) # Have we downloaded raylib yet?
    set(FETCHCONTENT_QUIET NO)
    FetchContent_Populate(raylib)
    set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
    add_subdirectory(${raylib_SOURCE_DIR} ${raylib_BINARY_DIR})
  endif()
endif()

set(EXECUTABLE_NAME Asteroids)

set(SRC_FILES
    ${CMAKE_CURRENT_LIST_DIR}/src/main.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/Player.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/Bullet.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/Asteroid.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/Entity.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/Entity.hpp
        src/PhysicsObject.cpp
        src/PhysicsObject.hpp
        src/GameManager.cpp
        src/GameManager.hpp)

set(INCLUDE_DIRS
    ${CMAKE_CURRENT_LIST_DIR}/raylib-cpp/v451
    include)

add_executable(${EXECUTABLE_NAME} ${SRC_FILES})
target_include_directories(${EXECUTABLE_NAME} PRIVATE ${INCLUDE_DIRS})
target_link_libraries(${EXECUTABLE_NAME} raylib)

# Checks if OSX and links appropriate frameworks (only required on MacOS)
if (APPLE)
    target_link_libraries(${EXECUTABLE_NAME} "-framework IOKit")
    target_link_libraries(${EXECUTABLE_NAME} "-framework Cocoa")
    target_link_libraries(${EXECUTABLE_NAME} "-framework OpenGL")
endif()

# Copy resources to target directory
file(COPY ${CMAKE_CURRENT_LIST_DIR}/resources
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
