SET(_PF86 "PROGRAMFILES(X86)")
set( OPENAL_SOFT_SEARCH_PATHS
  ${OPENAL_SOFT_ROOT_DIR}
  ${CMAKE_SOURCE_DIR}/contrib/openal-soft # Project root
  $ENV{PROGRAMFILES}/openal-soft # WINDOWS
  "$ENV{_PF86}/openal-soft"	# WINDOWS
  ~/Library/Frameworks # MAC
  /Library/Frameworks # MAC
  /usr/local # LINUX/MAC/UNIX
  /usr # LINUX/MAC/UNIX
  /opt # LINUX/MAC/UNIX
  /sw # Fink
  /opt/local # DarwinPorts
  /opt/csw # Blastwave
)

find_path( OPENAL_SOFT_INCLUDE_DIR
  NAMES
    AL
  PATHS
    ${OPENAL_SOFT_SEARCH_PATHS}
  PATH_SUFFIXES
    include
  DOC
    "The directory where openal resides"
)

find_library( OPENAL_SOFT_LIBRARIES 
  NAMES
    OpenAL32
  PATHS
    ${OPENAL_SOFT_SEARCH_PATHS}
  PATH_SUFFIXES
    libs/${CMAKE_BUILD_TYPE}/x64
  DOC
    "The OpenAL32 static lib files"
)

# Check if we found it!
if ( OPENAL_SOFT_INCLUDE_DIR AND OPENAL_SOFT_LIBRARIES )
  set( OPENAL_SOFT_FOUND TRUE )
  message( STATUS "Looking for OPENAL-Soft - found include : ${OPENAL_SOFT_INCLUDE_DIR} and lib : ${OPENAL_SOFT_LIBRARIES}" )
else ()
  set( OPENAL_SOFT_FOUND FALSE )
  message( FATAL_ERROR "Looking for OPENAL - not found" )
endif ()