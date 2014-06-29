
set( DataHandlingDir ${CMAKE_SOURCE_DIR}/src/common/datahandling )

set( lp_model_SOURCES
        musicitem.cpp
        musicmodel.cpp
        rootitem.cpp
        score.cpp
        symbol.cpp
        tune.cpp
        part.cpp
        measure.cpp

        ${DataHandlingDir}/itembehavior.cpp
        ${DataHandlingDir}/symbolbehavior.cpp

        ${CMAKE_SOURCE_DIR}/src/common/datatypes/instrument.cpp
        ${CMAKE_SOURCE_DIR}/src/common/datatypes/length.cpp
        ${CMAKE_SOURCE_DIR}/src/common/datatypes/pitch.cpp
        ${CMAKE_SOURCE_DIR}/src/common/datatypes/pitchcontext.cpp
        ${CMAKE_SOURCE_DIR}/src/common/datatypes/timesignature.cpp
        )

add_library( lp_model STATIC ${lp_model_SOURCES} )
qt5_use_modules( lp_model Widgets )


