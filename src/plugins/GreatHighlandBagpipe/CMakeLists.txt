project( lp_greathighlandbagpipe )

cmake_minimum_required( VERSION 2.6 )

set ( CMAKE_BUILD_TYPE Release )

add_definitions ( -Wall )

find_package ( Qt4 REQUIRED )

ADD_DEFINITIONS(-DQT_STATICPLUGIN)
include ( ${QT_USE_FILE} )

include_directories (
        ${CMAKE_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR}
	${QT_QTCORE_INCLUDE_DIR} ${QT_QTGUI_INCLUDE_DIR}
	)
set ( LIBRARY_OUTPUT_PATH ${STATIC_PLUGINS_FOLDER} )

set ( lp_greathighlandbagpipe_HEADERS
    	ghb_instrument.h
    	ghb_symboltypes.h
    	ghb_melodynote.h
    	ghb_doubling.h
	)

set ( lp_greathighlandbagpipe_SOURCES
	greathighlandbagpipe.cpp
    	ghb_instrument.cpp
    	ghb_melodynote.cpp
    	ghb_doubling.cpp
	)

set ( lp_greathighlandbagpipe_MOC_HEADERS
        greathighlandbagpipe.h
        )

QT4_WRAP_CPP(lp_greathighlandbagpipe_SOURCES ${lp_greathighlandbagpipe_MOC_HEADERS})

add_library ( lp_greathighlandbagpipe STATIC ${lp_greathighlandbagpipe_SOURCES} )
target_link_libraries ( lp_greathighlandbagpipe ${QT_LIBRARIES} )
