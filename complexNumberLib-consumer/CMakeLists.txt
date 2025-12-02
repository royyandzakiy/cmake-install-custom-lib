cmake_minimum_required(VERSION 3.23)

project(
  complexNumberTest
  VERSION 1.0
  LANGUAGES CXX
)

# include custom options
include(CMakeOptions.txt)

# Find packages will search for a specific library. CMake will fail if the package is REQUIRED but not found
find_package(complexNumbers REQUIRED)

# Add an executable and provide the source file directly.
add_executable(${CMAKE_PROJECT_NAME} main.cpp)

# Make sure you link your executable with your library. Notice the namespace that we defined earlier.
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE complexNumbers::complexNumbers)

if (MSVC)
  if(${ENABLE_SHARED})
    target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE COMPILEDLL)
    else()
    target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE COMPILELIB)
  endif()
endif()

# On Windows, we need the *.dll file in the same folder as the executable to be able to run it
if(WIN32)
  if(EXISTS "${CMAKE_PREFIX_PATH}/bin/complexNumbers.dll" OR EXISTS "${CMAKE_PREFIX_PATH}/bin/complexNumbersd.dll")
    add_custom_command(
      TARGET ${CMAKE_PROJECT_NAME}
      POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E copy_if_different
      "${CMAKE_SOURCE_DIR}/${CMAKE_PREFIX_PATH}/bin/$<IF:$<CONFIG:Debug>,complexNumbersd.dll,complexNumbers.dll>"
      "${CMAKE_BINARY_DIR}/$<IF:$<CONFIG:Debug>,Debug,Release>/$<IF:$<CONFIG:Debug>,complexNumbersd.dll,complexNumbers.dll>"
    )
    add_custom_command(
      TARGET ${CMAKE_PROJECT_NAME}
      POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E copy_if_different
      "${CMAKE_SOURCE_DIR}/${CMAKE_PREFIX_PATH}/bin/$<IF:$<CONFIG:Debug>,complexNumbersd.dll,complexNumbers.dll>"
      "${CMAKE_BINARY_DIR}/$<IF:$<CONFIG:Debug>,complexNumbersd.dll,complexNumbers.dll>"
    )
  endif()
endif()