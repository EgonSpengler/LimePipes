project( limepipes )
cmake_minimum_required( VERSION 2.6 )
set ( CMAKE_BUILD_TYPE Release )
add_definitions ( -Wall )
find_package ( Qt4 REQUIRED )
include ( ${QT_USE_FILE} )
include_directories (
        ${CMAKE_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR}
        ${QT_QTCORE_INCLUDE_DIR} ${QT_QTGUI_INCLUDE_DIR}
        )
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(STATIC_PLUGINS_FOLDER ${CMAKE_BINARY_DIR}/plugins_static)
set(OUTPUT_BIN_FOLDER ${CMAKE_BINARY_DIR}/bin)

ENABLE_TESTING()

add_subdirectory( src )
add_subdirectory( tests )
