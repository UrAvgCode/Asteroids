cmake_minimum_required(VERSION 3.27)
project(Asteroids)

set(CMAKE_CXX_STANDARD 23)

# raylib
find_package(raylib QUIET)
if (NOT raylib_FOUND)
    include(FetchContent)
    FetchContent_Declare(
        raylib
        GIT_REPOSITORY https://github.com/raysan5/raylib.git
        GIT_TAG 5.0
        GIT_SHALLOW 1
    )
    FetchContent_MakeAvailable(raylib)
endif()

# raylib-cpp
find_package(raylib_cpp QUIET)
if (NOT raylib_cpp_FOUND)
    include(FetchContent)
    FetchContent_Declare(
        raylib_cpp
        GIT_REPOSITORY https://github.com/RobLoach/raylib-cpp.git
        GIT_TAG v5.0.1
    )
    FetchContent_MakeAvailable(raylib_cpp)
endif()

# This is the main part:
set(SOURCES 
    src/main.cpp 
    src/game_object.cpp 
    src/physics_object.cpp
    src/player.cpp 
    src/bullet.cpp 
    src/asteroid.cpp)

set(INCLUDE_DIRS ${CMAKE_CURRENT_LIST_DIR}/include)

add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC ${INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PUBLIC raylib raylib_cpp)

# Copy resources to target directory
file(COPY ${CMAKE_CURRENT_LIST_DIR}/res DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
