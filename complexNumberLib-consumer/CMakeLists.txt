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
    # Get the imported location of the library
    get_target_property(IMPORTED_LOCATION_DEBUG complexNumbers::complexNumbers IMPORTED_LOCATION_DEBUG)
    get_target_property(IMPORTED_LOCATION_RELEASE complexNumbers::complexNumbers IMPORTED_LOCATION_RELEASE)
    get_target_property(IMPORTED_LOCATION_RELWITHDEBINFO complexNumbers::complexNumbers IMPORTED_LOCATION_RELWITHDEBINFO)
    get_target_property(IMPORTED_LOCATION_MINSIZEREL complexNumbers::complexNumbers IMPORTED_LOCATION_MINSIZEREL)
    
    # Get the DLL location from the imported library location
    if(IMPORTED_LOCATION_DEBUG)
      get_filename_component(DLL_DIR_DEBUG "${IMPORTED_LOCATION_DEBUG}" DIRECTORY)
      set(DLL_PATH_DEBUG "${DLL_DIR_DEBUG}/complexNumbersd.dll")
    endif()
    
    if(IMPORTED_LOCATION_RELEASE)
      get_filename_component(DLL_DIR_RELEASE "${IMPORTED_LOCATION_RELEASE}" DIRECTORY)
      set(DLL_PATH_RELEASE "${DLL_DIR_RELEASE}/complexNumbers.dll")
    endif()
    
    if(IMPORTED_LOCATION_RELWITHDEBINFO)
      get_filename_component(DLL_DIR_RELWITHDEBINFO "${IMPORTED_LOCATION_RELWITHDEBINFO}" DIRECTORY)
      set(DLL_PATH_RELWITHDEBINFO "${DLL_DIR_RELWITHDEBINFO}/complexNumbers.dll")
    endif()
    
    if(IMPORTED_LOCATION_MINSIZEREL)
      get_filename_component(DLL_DIR_MINSIZEREL "${IMPORTED_LOCATION_MINSIZEREL}" DIRECTORY)
      set(DLL_PATH_MINSIZEREL "${DLL_DIR_MINSIZEREL}/complexNumbers.dll")
    endif()
    
    # Function to copy DLL for a specific configuration
    function(copy_complex_dll config_name dll_path dll_name)
      if(EXISTS "${dll_path}")
        add_custom_command(
          TARGET ${CMAKE_PROJECT_NAME}
          POST_BUILD
          COMMAND ${CMAKE_COMMAND} -E copy_if_different
          "${dll_path}"
          "$<TARGET_FILE_DIR:${CMAKE_PROJECT_NAME}>/${dll_name}"
          COMMENT "Copying ${dll_name} for ${config_name} configuration"
        )
        message(STATUS "Found ${dll_name} at ${dll_path}")
      else()
        message(WARNING "${dll_name} not found at ${dll_path} for ${config_name} configuration")
      endif()
    endfunction()
    
    # Copy DLLs for each configuration if they exist
    if(DLL_PATH_DEBUG)
      copy_complex_dll(Debug "${DLL_PATH_DEBUG}" "complexNumbersd.dll")
    endif()
    
    if(DLL_PATH_RELEASE)
      copy_complex_dll(Release "${DLL_PATH_RELEASE}" "complexNumbers.dll")
    endif()
    
    if(DLL_PATH_RELWITHDEBINFO)
      copy_complex_dll(RelWithDebInfo "${DLL_PATH_RELWITHDEBINFO}" "complexNumbers.dll")
    endif()
    
    if(DLL_PATH_MINSIZEREL)
      copy_complex_dll(MinSizeRel "${DLL_PATH_MINSIZEREL}" "complexNumbers.dll")
    endif()
    
  else()
    message(STATUS "complexNumbers::complexNumbers is not a shared library (type: ${COMPLEX_LIB_TYPE})")
  endif()
endif()