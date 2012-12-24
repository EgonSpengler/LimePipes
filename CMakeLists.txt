project( limepipes CXX)
cmake_minimum_required( VERSION 2.8 )
add_definitions( -Wall )
find_package( Qt4 REQUIRED )
include( ${QT_USE_FILE} )

set( CMAKE_INCLUDE_CURRENT_DIR ON )

set( STATIC_PLUGINS_FOLDER ${CMAKE_BINARY_DIR}/plugins_static )
set( OUTPUT_BIN_FOLDER ${CMAKE_BINARY_DIR}/bin )

enable_testing()

add_subdirectory( src )
add_subdirectory( tests )
