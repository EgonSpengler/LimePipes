add_definitions( -DQT_STATICPLUGIN )

set( lp_greathighlandbagpipe_SOURCES
        greathighlandbagpipe.cpp

        Doubling/doublingbehavior.cpp
    )

add_library( lp_greathighlandbagpipe STATIC ${lp_greathighlandbagpipe_SOURCES} )
qt5_use_modules( lp_greathighlandbagpipe Widgets )
target_link_libraries( lp_greathighlandbagpipe lp_model )
