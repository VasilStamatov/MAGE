SET(_PF86 "PROGRAMFILES(X86)")
set( GLFW_SEARCH_PATHS
  ${GLFW_ROOT_DIR}
  ${CMAKE_SOURCE_DIR}/contrib/glfw # Project root
  $ENV{PROGRAMFILES}/GLFW # WINDOWS
  "$ENV{_PF86}/GLFW"	# WINDOWS
  ~/Library/Frameworks # MAC
  /Library/Frameworks # MAC
  /usr/local # LINUX/MAC/UNIX
  /usr # LINUX/MAC/UNIX
  /opt # LINUX/MAC/UNIX
  /sw # Fink
  /opt/local # DarwinPorts
  /opt/csw # Blastwave
)

find_path( GLFW_INCLUDE_DIR
  NAMES
    glfw3.h
    glfw3native.h
  PATHS
    ${GLFW_SEARCH_PATHS}
  PATH_SUFFIXES
    include/GLFW
  DOC
    "The directory where glfw3.h and glfw3native.h resides"
)

find_library( GLFW_LIBRARIES 
  NAMES
    glfw3
  PATHS
    ${GLFW_SEARCH_PATHS}
  PATH_SUFFIXES
    lib
  DOC
    "The glfw3 lib files"
)

# Check if we found it!
if ( GLFW_INCLUDE_DIR AND GLFW_LIBRARIES )
  set( GLFW_FOUND TRUE )
  message( STATUS "Looking for GLFW - found include : ${GLFW_INCLUDE_DIR} and lib : ${GLFW_LIBRARIES}" )
else ()
  set( GLFW_FOUND FALSE )
  message( FATAL_ERROR "Looking for GLFW - not found" )
endif ()