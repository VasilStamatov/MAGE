SET(_PF86 "PROGRAMFILES(X86)")
set( STB_SEARCH_PATHS
  ${STB_ROOT_DIR}
  ${CMAKE_SOURCE_DIR}/contrib/stb # Project root
  $ENV{PROGRAMFILES}/STB # WINDOWS
  "$ENV{_PF86}/STB"	# WINDOWS
  ~/Library/Frameworks # MAC
  /Library/Frameworks # MAC
  /usr/local # LINUX/MAC/UNIX
  /usr # LINUX/MAC/UNIX
  /opt # LINUX/MAC/UNIX
  /sw # Fink
  /opt/local # DarwinPorts
  /opt/csw # Blastwave
)

find_path( STB_INCLUDE_DIR
  NAMES
    stb
  PATHS
    ${STB_SEARCH_PATHS}
  PATH_SUFFIXES
    include
  DOC
    "The directory where stb_image.h lives"
)

# Check if we found it!
if ( STB_INCLUDE_DIR )
  set( STB_FOUND TRUE )
  message( STATUS "Looking for STB - found include : ${STB_INCLUDE_DIR}" )
else ()
  set( STB_FOUND FALSE )
  message( FATAL_ERROR "Looking for STB - not found" )
endif ()