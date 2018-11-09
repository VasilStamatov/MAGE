SET(_PF86 "PROGRAMFILES(X86)")
set( CATCH_SEARCH_PATHS
  ${CATCH_ROOT_DIR}
  ${CMAKE_SOURCE_DIR}/contrib/catch # Project root
  $ENV{PROGRAMFILES}/catch # WINDOWS
  "$ENV{_PF86}/catch"	# WINDOWS
  ~/Library/Frameworks # MAC
  /Library/Frameworks # MAC
  /usr/local # LINUX/MAC/UNIX
  /usr # LINUX/MAC/UNIX
  /opt # LINUX/MAC/UNIX
  /sw # Fink
  /opt/local # DarwinPorts
  /opt/csw # Blastwave
)

find_path( CATCH_INCLUDE_DIR
  NAMES
    catch.hpp
    catch.h
  PATHS
    ${CATCH_SEARCH_PATHS}
  PATH_SUFFIXES
    include
  DOC
    "The directory where catch.hpp lives"
)

# Check if we found it!
if ( CATCH_INCLUDE_DIR )
  set( CATCH_FOUND TRUE )
  message( STATUS "Looking for CATCH - found include : ${CATCH_INCLUDE_DIR}" )
else ()
  set( CATCH_FOUND FALSE )
  message( FATAL_ERROR "Looking for CATCH - not found" )
endif ()