set( VULKAN_SEARCH_PATHS
  ${CMAKE_SOURCE_DIR}/contrib/vulkan # Project root
  $ENV{VULKAN_SDK} # WINDOWS
  $ENV{VK_SDK_PATH} # WINDOWS
  ~/Library/Frameworks # MAC
  /Library/Frameworks # MAC
  /usr/local # LINUX/MAC/UNIX
  /usr # LINUX/MAC/UNIX
  /opt # LINUX/MAC/UNIX
  /sw # Fink
  /opt/local # DarwinPorts
  /opt/csw # Blastwave
)

find_path( VULKAN_INCLUDE_DIR
  NAMES
    vulkan.h
  PATHS
    ${VULKAN_SEARCH_PATHS}
  PATH_SUFFIXES
    include/vulkan
    Include/vulkan
  DOC
    "The directory where vulkan.h resides"
)

find_library( VULKAN_LIBRARIES 
  NAMES
    vulkan-1
  PATHS
    ${VULKAN_SEARCH_PATHS}
  PATH_SUFFIXES
    Lib
    lib
  DOC
    "The vulkan lib files"
)

# Check if we found it!
if ( VULKAN_INCLUDE_DIR AND VULKAN_LIBRARIES )
  set( VULKAN_FOUND TRUE )
  message( STATUS "Looking for Vulkan - found include : ${VULKAN_INCLUDE_DIR} and lib : ${VULKAN_LIBRARIES}" )
else ()
  set( VULKAN_FOUND FALSE )
  message( FATAL_ERROR "Looking for Vulkan - not found" )
endif ()