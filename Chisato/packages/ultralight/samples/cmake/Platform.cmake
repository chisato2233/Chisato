if (NOT UL_PLATFORM)
    if(CMAKE_SYSTEM_NAME MATCHES "Windows")
        set(UL_PLATFORM "windows")
    elseif (CMAKE_SYSTEM_NAME MATCHES "Darwin")
        set(UL_PLATFORM "macos")
    elseif (CMAKE_SYSTEM_NAME MATCHES "Linux")
        set(UL_PLATFORM "linux")  
    else ()
        message(FATAL_ERROR "Unable to detect target platform. Please manually specify UL_PLATFORM when running CMake.")
    endif ()
endif ()

if (UL_PLATFORM MATCHES "macos")
    SET(CMAKE_SKIP_BUILD_RPATH  FALSE)
    SET(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)
    SET(CMAKE_INSTALL_RPATH "@executable_path/")
elseif (UL_PLATFORM MATCHES "linux")
    SET(CMAKE_SKIP_BUILD_RPATH  FALSE)
    SET(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)
    SET(CMAKE_INSTALL_RPATH "$\{ORIGIN\}")
endif ()
