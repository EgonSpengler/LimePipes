set( lp_model_HEADERS
        instrumentmanager.h
        itemdatatypes.h
        musicitem.h
        musicmodelinterface.h
        rootitem.h
        score.h
        symbol.h
        tune.h
        part.h
        measure.h
        symbolgraphicbuilder.h

        commands/insertitemscommand.h
        commands/removeitemscommand.h

        datatypes/instrument.h
        datatypes/length.h
        datatypes/pitch.h
        datatypes/pitchcontext.h
        datatypes/symbolgraphic.h
        datatypes/timesignature.h

        musicfont/emmentalermusicfont.h
        musicfont/musicfont.h

        symbols/melodynote.h
        symbols/melodynotegraphicbuilder.h
        symbols/barline.h
        )

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

        symbols/barline.cpp
        symbols/melodynote.cpp
        symbols/melodynotegraphicbuilder.cpp
        )

set( lp_model_MOC_HEADERS
        musicmodel.h
        )

set( lp_model_RESOURCES
        musicfont/musicfont_resources.qrc
        )

include( ${QT_USE_FILE} )

set( LIBRARY_OUTPUT_PATH ${STATIC_PLUGINS_FOLDER} )

qt4_wrap_cpp( lp_model_SOURCES ${lp_model_MOC_HEADERS} )

qt4_add_resources( lp_model_SOURCES ${lp_model_RESOURCES} )

add_library( lp_model ${lp_model_SOURCES} )
