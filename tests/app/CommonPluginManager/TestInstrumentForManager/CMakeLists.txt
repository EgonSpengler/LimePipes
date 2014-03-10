set( plugin_SOURCES
        testinstrumentformanager.cpp
        ${DATATYPES_SOURCE_DIR}/instrument.cpp
        ${DATATYPES_SOURCE_DIR}/pitchcontext.cpp
        ${DATATYPES_SOURCE_DIR}/pitch.cpp
	)

add_library( lp_testinstrumentformanager SHARED ${plugin_SOURCES} )
qt5_use_modules( lp_testinstrumentformanager Gui )
