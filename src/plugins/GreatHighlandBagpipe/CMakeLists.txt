add_definitions( -DQT_STATICPLUGIN )

set( LIBRARY_OUTPUT_PATH ${STATIC_PLUGINS_FOLDER} )

set( lp_greathighlandbagpipe_SOURCES
        ${CMAKE_SOURCE_DIR}/src/model/symbols/melodynote.cpp
        ${CMAKE_SOURCE_DIR}/src/model/symbols/melodynotegraphicbuilder.cpp
	    greathighlandbagpipe.cpp
    	ghb_instrument.cpp
    	ghb_melodynote.cpp
    	ghb_doubling.cpp
	)
find_package( Qt5Widgets REQUIRED )
add_library( lp_greathighlandbagpipe STATIC ${lp_greathighlandbagpipe_SOURCES} )
qt5_use_modules( lp_greathighlandbagpipe Widgets )
