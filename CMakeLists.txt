project( limepipes CXX)
cmake_minimum_required( VERSION 2.8 )
add_definitions( -Wall )
find_package( Qt4 REQUIRED )
include( ${QT_USE_FILE} )

set( CMAKE_INCLUDE_CURRENT_DIR ON )

set( STATIC_PLUGINS_FOLDER ${CMAKE_BINARY_DIR}/plugins_static )
set( OUTPUT_BIN_FOLDER ${CMAKE_BINARY_DIR}/bin )

set( LimePipes_VERSION_MAJOR 0 )
set( LimePipes_VERSION_MINOR 1 )
set( LimePipes_VERSION_PATCH 1 )

configure_file(
  "${PROJECT_SOURCE_DIR}/LimePipesConfig.h.in"
  "${PROJECT_BINARY_DIR}/LimePipesConfig.h"
  )

enable_testing()

add_subdirectory( src )
add_subdirectory( tests )
