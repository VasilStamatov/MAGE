SET(_PF86 "PROGRAMFILES(X86)")
set( VORBIS_SEARCH_PATHS
  ${VORBIS_ROOT_DIR}
  ${CMAKE_SOURCE_DIR}/contrib/vorbis # Project root
  $ENV{PROGRAMFILES}/vorbis # WINDOWS
  "$ENV{_PF86}/vorbis"	# WINDOWS
  ~/Library/Frameworks # MAC
  /Library/Frameworks # MAC
  /usr/local # LINUX/MAC/UNIX
  /usr # LINUX/MAC/UNIX
  /opt # LINUX/MAC/UNIX
  /sw # Fink
  /opt/local # DarwinPorts
  /opt/csw # Blastwave
)

find_path( VORBIS_INCLUDE_DIR
  NAMES
    vorbis
  PATHS
    ${VORBIS_SEARCH_PATHS}
  PATH_SUFFIXES
    include
  DOC
    "The vorbis include directory"
)

find_library( VORBIS_LIBRARIES 
  NAMES
    vorbis
    vorbisenc
    vorbisfile
  PATHS
    ${VORBIS_SEARCH_PATHS}
  PATH_SUFFIXES
    lib/${CMAKE_BUILD_TYPE}/x64
  DOC
    "The vorbis lib files"
)

# Check if we found it!
if ( VORBIS_INCLUDE_DIR AND VORBIS_LIBRARIES )
  set( VORBIS_FOUND TRUE )
  message( STATUS "Looking for VORBIS - found include : ${VORBIS_INCLUDE_DIR} and lib : ${VORBIS_LIBRARIES}" )
else ()
  set( VORBIS_FOUND FALSE )
  message( FATAL_ERROR "Looking for VORBIS - not found" )
endif ()