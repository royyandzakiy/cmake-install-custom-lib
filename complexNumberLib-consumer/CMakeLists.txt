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
  # First check if the DLL exists
  # Get the directory where the library was found
  get_target_property(COMPLEX_LIB_TYPE complexNumbers::complexNumbers TYPE)
  
  if(COMPLEX_LIB_TYPE STREQUAL "SHARED_LIBRARY")
    # Get the imported location of the library - use the appropriate one based on configuration
    # We'll use generator expressions to handle configuration-specific copying
    
    # Get the imported location for the current configuration
    get_target_property(IMPORTED_LOCATION complexNumbers::complexNumbers IMPORTED_LOCATION)
    
    if(IMPORTED_LOCATION)
      # Extract the directory from the imported location
      get_filename_component(LIB_DIR "${IMPORTED_LOCATION}" DIRECTORY)
      
      # Use generator expressions to copy the appropriate DLL based on configuration
      add_custom_command(
        TARGET ${CMAKE_PROJECT_NAME}
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "$<IF:$<CONFIG:Debug>,${LIB_DIR}/complexNumbersd.dll,${LIB_DIR}/complexNumbers.dll>"
        "$<TARGET_FILE_DIR:${CMAKE_PROJECT_NAME}>/$<IF:$<CONFIG:Debug>,complexNumbersd.dll,complexNumbers.dll>"
        COMMENT "Copying complexNumbers DLL"
      )
      
      # Debug message
      message(STATUS "Will copy DLL from: ${LIB_DIR}")
      message(STATUS "Debug DLL path: ${LIB_DIR}/complexNumbersd.dll")
      message(STATUS "Release DLL path: ${LIB_DIR}/complexNumbers.dll")
      
    else()
      # Try to get configuration-specific locations if IMPORTED_LOCATION is not set
      get_target_property(IMPORTED_LOCATION_DEBUG complexNumbers::complexNumbers IMPORTED_LOCATION_DEBUG)
      get_target_property(IMPORTED_LOCATION_RELEASE complexNumbers::complexNumbers IMPORTED_LOCATION_RELEASE)
      
      if(IMPORTED_LOCATION_DEBUG OR IMPORTED_LOCATION_RELEASE)
        # Copy DLLs using configuration-specific logic with generator expressions
        add_custom_command(
          TARGET ${CMAKE_PROJECT_NAME}
          POST_BUILD
          COMMAND ${CMAKE_COMMAND} -E copy_if_different
          "$<IF:$<CONFIG:Debug>,$<IF:$<BOOL:${IMPORTED_LOCATION_DEBUG}>,${IMPORTED_LOCATION_DEBUG},>,${IMPORTED_LOCATION_RELEASE}>"
          "$<TARGET_FILE_DIR:${CMAKE_PROJECT_NAME}>/$<IF:$<CONFIG:Debug>,complexNumbersd.dll,complexNumbers.dll>"
          COMMENT "Copying complexNumbers DLL"
        )
      else()
        message(WARNING "Could not determine DLL location for complexNumbers library")
      endif()
    endif()
    
  else()
    message(STATUS "complexNumbers::complexNumbers is not a shared library (type: ${COMPLEX_LIB_TYPE})")
  endif()
endif()