cmake_minimum_required(VERSION 3.10)

# Set the project name
project(BouncingBall)

# Generate compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Dependencies
set(RAYLIB_VERSION 5.5)
find_package(raylib ${RAYLIB_VERSION} REQUIRED) # QUIET or REQUIRED
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
    FetchContent_MakeAvailable(raylib)
  endif()
endif()

# Add the executable
add_executable(BouncingBall Source.cpp)
# Copy the file
file(COPY ${CMAKE_SOURCE_DIR}/resources/plastic-ball-bounce-14790.wav
     DESTINATION ${CMAKE_BINARY_DIR}/resources)

# Set the C++ standard
set_target_properties(BouncingBall PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED YES)



# Link the raylib library
target_link_libraries(BouncingBall PRIVATE raylib)

# Add additional compiler options if needed
if (MSVC)
    target_compile_options(BouncingBall PRIVATE /W4)
else()
    target_compile_options(BouncingBall PRIVATE -Wall -Wextra -pedantic)
endif()


# Copy resources to the build directory
add_custom_command(
    TARGET BouncingBall POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/resources $<TARGET_FILE_DIR:BouncingBall>/resources
)