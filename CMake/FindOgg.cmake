SET(_PF86 "PROGRAMFILES(X86)")
set( OGG_SEARCH_PATHS
  ${OGG_ROOT_DIR}
  ${CMAKE_SOURCE_DIR}/contrib/ogg # Project root
  $ENV{PROGRAMFILES}/ogg # WINDOWS
  "$ENV{_PF86}/ogg"	# WINDOWS
  ~/Library/Frameworks # MAC
  /Library/Frameworks # MAC
  /usr/local # LINUX/MAC/UNIX
  /usr # LINUX/MAC/UNIX
  /opt # LINUX/MAC/UNIX
  /sw # Fink
  /opt/local # DarwinPorts
  /opt/csw # Blastwave
)

find_path( OGG_INCLUDE_DIR
  NAMES
    ogg
  PATHS
    ${OGG_SEARCH_PATHS}
  PATH_SUFFIXES
    include
  DOC
    "The ogg include directory"
)

find_library( OGG_LIBRARIES 
  NAMES
    ogg
  PATHS
    ${OGG_SEARCH_PATHS}
  PATH_SUFFIXES
    lib/${CMAKE_BUILD_TYPE}/x64
  DOC
    "The ogg lib files"
)

# Check if we found it!
if ( OGG_INCLUDE_DIR AND OGG_LIBRARIES )
  set( OGG_FOUND TRUE )
  message( STATUS "Looking for OGG - found include : ${OGG_INCLUDE_DIR} and lib : ${OGG_LIBRARIES}" )
else ()
  set( OGG_FOUND FALSE )
  message( FATAL_ERROR "Looking for OGG - not found" )
endif ()