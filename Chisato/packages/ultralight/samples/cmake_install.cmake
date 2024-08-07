# Install script for directory: A:/Code/MyCode/Chisato/Chisato/packages/ultralight/samples

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/Samples")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("A:/Code/MyCode/Chisato/Chisato/packages/ultralight/samples/Sample 1 - Render to PNG/cmake_install.cmake")
  include("A:/Code/MyCode/Chisato/Chisato/packages/ultralight/samples/Sample 2 - Basic App/cmake_install.cmake")
  include("A:/Code/MyCode/Chisato/Chisato/packages/ultralight/samples/Sample 3 - Resizable App/cmake_install.cmake")
  include("A:/Code/MyCode/Chisato/Chisato/packages/ultralight/samples/Sample 4 - JavaScript/cmake_install.cmake")
  include("A:/Code/MyCode/Chisato/Chisato/packages/ultralight/samples/Sample 5 - File Loading/cmake_install.cmake")
  include("A:/Code/MyCode/Chisato/Chisato/packages/ultralight/samples/Sample 6 - Intro to C API/cmake_install.cmake")
  include("A:/Code/MyCode/Chisato/Chisato/packages/ultralight/samples/Sample 7 - OpenGL Integration/cmake_install.cmake")
  include("A:/Code/MyCode/Chisato/Chisato/packages/ultralight/samples/Sample 8 - Web Browser/cmake_install.cmake")
  include("A:/Code/MyCode/Chisato/Chisato/packages/ultralight/samples/Sample 9 - Multi Window/cmake_install.cmake")

endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "A:/Code/MyCode/Chisato/Chisato/packages/ultralight/samples/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
