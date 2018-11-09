SET(_PF86 "PROGRAMFILES(X86)")
set( GLEW_SEARCH_PATHS
  ${GLEW_ROOT_DIR}
  ${CMAKE_SOURCE_DIR}/contrib/glew # Project root
  $ENV{PROGRAMFILES}/glew # WINDOWS
  "$ENV{_PF86}/GLEW"	# WINDOWS
  ~/Library/Frameworks # MAC
  /Library/Frameworks # MAC
  /usr/local # LINUX/MAC/UNIX
  /usr # LINUX/MAC/UNIX
  /opt # LINUX/MAC/UNIX
  /sw # Fink
  /opt/local # DarwinPorts
  /opt/csw # Blastwave
)

find_path( GLEW_INCLUDE_DIR
  NAMES
    glew.h
  PATHS
    ${GLEW_SEARCH_PATHS}
  PATH_SUFFIXES
    include/GL
  DOC
    "The directory where glew.h resides"
)

find_library( GLEW_LIBRARIES 
  NAMES
    glew32s
  PATHS
    ${GLEW_SEARCH_PATHS}
  PATH_SUFFIXES
    lib/${CMAKE_BUILD_TYPE}/x64
  DOC
    "The glew static lib files"
)

# Check if we found it!
if ( GLEW_INCLUDE_DIR AND GLEW_LIBRARIES )
  set( GLEW_FOUND TRUE )
  message( STATUS "Looking for GLEW - found include : ${GLEW_INCLUDE_DIR} and lib : ${GLEW_LIBRARIES}" )
else ()
  set( GLEW_FOUND FALSE )
  message( FATAL_ERROR "Looking for GLEW - not found" )
endif ()