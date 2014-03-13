add_definitions( -DQT_STATICPLUGIN )

set( lp_plugin_SOURCES
        integratedsymbols.cpp
        melodynotegraphicbuilder.cpp
    )

add_library( lp_integratedsymbols STATIC ${lp_plugin_SOURCES} )
qt5_use_modules( lp_integratedsymbols Widgets )
target_link_libraries( lp_integratedsymbols lp_model )
