add_definitions( -DQT_STATICPLUGIN )

set( lp_plugin_SOURCES
        ${CMAKE_SOURCE_DIR}/src/common/graphictypes/symbolgraphicbuilder.cpp
        ${CMAKE_SOURCE_DIR}/src/common/graphictypes/glyphitem.cpp

        symbols/melodynote.cpp

        integratedsymbols.cpp
        integratedsymbolsdefines.h
        MelodyNote/melodynoteglyphitem.cpp
        MelodyNote/melodynoteinteraction.cpp
        melodynotegraphicbuilder.cpp
    )

add_library( lp_integratedsymbols STATIC ${lp_plugin_SOURCES} )
qt5_use_modules( lp_integratedsymbols Widgets )
target_link_libraries( lp_integratedsymbols lp_model )
