set( plugin_SOURCES
        testinstrumentghb.cpp
        ${DATATYPES_SOURCE_DIR}/instrument.cpp
        ${DATATYPES_SOURCE_DIR}/pitchcontext.cpp
        ${DATATYPES_SOURCE_DIR}/pitch.cpp
	)

add_library( lp_testinstrumentghb SHARED ${plugin_SOURCES} )
qt5_use_modules( lp_testinstrumentghb Widgets )