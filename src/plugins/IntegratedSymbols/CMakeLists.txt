add_definitions( -DQT_STATICPLUGIN )

set( lp_plugin_SOURCES
        ${CMAKE_SOURCE_DIR}/src/common/graphictypes/symbolgraphicbuilder.cpp

        integratedsymbols.cpp
        integratedsymbolsdefines.h

        MelodyNote/melodynotebehavior.cpp
        MelodyNote/melodynoteglyphitem.cpp
        MelodyNote/melodynoteinteraction.cpp
        MelodyNote/melodynotegraphicbuilder.cpp

        Tie/tiegraphicbuilder.cpp
    )

set( symbol_resources
        integratedsymbols.qrc
        )

qt5_add_resources( lp_plugin_SOURCES ${symbol_resources} )

add_library( lp_integratedsymbols STATIC ${lp_plugin_SOURCES} )
qt5_use_modules( lp_integratedsymbols Widgets )
target_link_libraries( lp_integratedsymbols lp_model )
