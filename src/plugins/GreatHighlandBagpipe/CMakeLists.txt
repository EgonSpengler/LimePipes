add_definitions( -DQT_STATICPLUGIN )
include( ${QT_USE_FILE} )

set( LIBRARY_OUTPUT_PATH ${STATIC_PLUGINS_FOLDER} )

set( lp_greathighlandbagpipe_HEADERS
    	ghb_instrument.h
    	ghb_symboltypes.h
    	ghb_melodynote.h
    	ghb_doubling.h
	)

set( lp_greathighlandbagpipe_SOURCES
	greathighlandbagpipe.cpp
    	ghb_instrument.cpp
    	ghb_melodynote.cpp
    	ghb_doubling.cpp
	)

set( lp_greathighlandbagpipe_MOC_HEADERS
        greathighlandbagpipe.h
        )

qt4_wrap_cpp(lp_greathighlandbagpipe_SOURCES ${lp_greathighlandbagpipe_MOC_HEADERS})
add_library( lp_greathighlandbagpipe STATIC ${lp_greathighlandbagpipe_SOURCES} )
target_link_libraries( lp_greathighlandbagpipe ${QT_LIBRARIES} )
