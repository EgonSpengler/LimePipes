set( lp_model_SOURCES
        instrumentmanager.cpp
        musicitem.cpp
        musicmodel.cpp
        rootitem.cpp
        score.cpp
        symbol.cpp
        tune.cpp
        part.cpp
        measure.cpp
        symbolgraphicbuilder.cpp

        datatypes/instrument.cpp
        datatypes/length.cpp
        datatypes/pitch.cpp
        datatypes/pitchcontext.cpp
        datatypes/symbolgraphic.cpp
        datatypes/timesignature.cpp

        musicfont/emmentalermusicfont.cpp
        musicfont/musicfont.cpp

        symbols/melodynote.cpp
        symbols/melodynotegraphicbuilder.cpp
        )

set( lp_model_RESOURCES
        musicfont/musicfont_resources.qrc
        )

find_package( Qt5Widgets REQUIRED )

qt5_add_resources( lp_model_SOURCES ${lp_model_RESOURCES} )

set( LIBRARY_OUTPUT_PATH ${STATIC_PLUGINS_FOLDER} )

add_library( lp_model STATIC ${lp_model_SOURCES} )
qt5_use_modules( lp_model Widgets )


