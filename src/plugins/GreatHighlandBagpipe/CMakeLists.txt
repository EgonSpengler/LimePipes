add_definitions( -DQT_STATICPLUGIN )

set( lp_greathighlandbagpipe_SOURCES
        ${CMAKE_SOURCE_DIR}/src/model/symbols/melodynote.cpp
        ${CMAKE_SOURCE_DIR}/src/model/symbols/melodynotegraphicbuilder.cpp
	    greathighlandbagpipe.cpp
    	ghb_instrument.cpp
    	ghb_melodynote.cpp
    	ghb_doubling.cpp
	)

add_library( lp_greathighlandbagpipe STATIC ${lp_greathighlandbagpipe_SOURCES} )
qt5_use_modules( lp_greathighlandbagpipe Widgets )
target_link_libraries( lp_greathighlandbagpipe ${Qt5Widgets_LIBRARIES} )
