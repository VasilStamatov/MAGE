SET(_PF86 "PROGRAMFILES(X86)")
set( TINY_OBJ_LOADER_SEARCH_PATHS
  ${TINY_OBJ_LOADER_ROOT_DIR}
  ${CMAKE_SOURCE_DIR}/contrib/tinyobj # Project root
  $ENV{PROGRAMFILES}/tinyobj # WINDOWS
  "$ENV{_PF86}/tinyobj"	# WINDOWS
  ~/Library/Frameworks # MAC
  /Library/Frameworks # MAC
  /usr/local # LINUX/MAC/UNIX
  /usr # LINUX/MAC/UNIX
  /opt # LINUX/MAC/UNIX
  /sw # Fink
  /opt/local # DarwinPorts
  /opt/csw # Blastwave
)

find_path( TINY_OBJ_LOADER_INCLUDE_DIR
  NAMES
    tiny_obj_loader.h
  PATHS
    ${TINY_OBJ_LOADER_SEARCH_PATHS}
  PATH_SUFFIXES
    include
  DOC
    "The directory where tiny_obj_loader.h lives"
)

# Check if we found it!
if ( TINY_OBJ_LOADER_INCLUDE_DIR )
  set( TINY_OBJ_LOADER_FOUND TRUE )
  message( STATUS "Looking for TINY_OBJ_LOADER - found include : ${TINY_OBJ_LOADER_INCLUDE_DIR}" )
else ()
  set( TINY_OBJ_LOADER_FOUND FALSE )
  message( FATAL_ERROR "Looking for TINY_OBJ_LOADER - not found" )
endif ()