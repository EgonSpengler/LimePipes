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

        ${CMAKE_SOURCE_DIR}/src/common/datatypes/instrument.cpp
        ${CMAKE_SOURCE_DIR}/src/common/datatypes/length.cpp
        ${CMAKE_SOURCE_DIR}/src/common/datatypes/pitch.cpp
        ${CMAKE_SOURCE_DIR}/src/common/datatypes/pitchcontext.cpp
        ${CMAKE_SOURCE_DIR}/src/common/datatypes/symbolgraphic.cpp
        ${CMAKE_SOURCE_DIR}/src/common/datatypes/timesignature.cpp

        musicfont/emmentalermusicfont.cpp
        musicfont/musicfont.cpp

        symbols/melodynote.cpp
        symbols/melodynotegraphicbuilder.cpp
        )

set( lp_model_RESOURCES
        musicfont/musicfont_resources.qrc
        )

qt5_add_resources( lp_model_SOURCES ${lp_model_RESOURCES} )

add_library( lp_model STATIC ${lp_model_SOURCES} )
qt5_use_modules( lp_model Widgets )


