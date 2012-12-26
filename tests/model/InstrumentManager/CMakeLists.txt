set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR}/bin/plugins)

# InstrumentManager
set( InstrumentManagerTest_SOURCES InstrumentManager/tst_instrumentmanagertest.cpp )
qt4_automoc( ${InstrumentManagerTest_SOURCES} )
add_executable( InstrumentManagerTest ${InstrumentManagerTest_SOURCES} )
target_link_libraries( InstrumentManagerTest ${TEST_LIBRARIES} lp_greathighlandbagpipe lp_model)
add_test( NAME InstrumentManagerTest COMMAND InstrumentManagerTest )

# TestInstrumentForManager
set( TestInstrumentForManager_SOURCES
        TestInstrumentForManager/testinstrumentformanager.cpp
        ${CMAKE_SOURCE_DIR}/src/model/datatypes/instrument.cpp
        ${CMAKE_SOURCE_DIR}/src/model/datatypes/pitchcontext.cpp
        ${CMAKE_SOURCE_DIR}/src/model/datatypes/pitch.cpp
        )
set( TestInstrumentForManager_MOC_HEADERS TestInstrumentForManager/testinstrumentformanager.h )

set( TestInstrumentForManager_HEADERS
        ${CMAKE_SOURCE_DIR}/src/model/datatypes/instrument.h
        ${CMAKE_SOURCE_DIR}/src/model/datatypes/pitchcontext.h
        ${CMAKE_SOURCE_DIR}/src/model/datatypes/pitch.h
        )
qt4_wrap_cpp(TestInstrumentForManager_SOURCES ${TestInstrumentForManager_MOC_HEADERS})
add_library( lp_TestInstrumentForManager SHARED ${TestInstrumentForManager_SOURCES} ${TestInstrumentForManager_HEADERS} )
target_link_libraries( lp_TestInstrumentForManager ${QT_LIBRARIES}  )

# TestInstrumentGHB
SET( TestInstrumentGHB_SOURCES
        TestInstrumentGHB/testinstrumentghb.cpp
        ${CMAKE_SOURCE_DIR}/src/model/datatypes/instrument.cpp
        ${CMAKE_SOURCE_DIR}/src/model/datatypes/pitchcontext.cpp
        ${CMAKE_SOURCE_DIR}/src/model/datatypes/pitch.cpp
        )

SET( TestInstrumentGHB_MOC_HEADERS TestInstrumentGHB/testinstrumentghb.h )

set( TestInstrumentGHB_HEADERS
        ${CMAKE_SOURCE_DIR}/src/model/datatypes/instrument.h
        ${CMAKE_SOURCE_DIR}/src/model/datatypes/pitchcontext.h
        ${CMAKE_SOURCE_DIR}/src/model/datatypes/pitch.h
        )
qt4_wrap_cpp(TestInstrumentGHB_SOURCES ${TestInstrumentGHB_MOC_HEADERS} ${TestInstrumentGHB_HEADERS})
add_library( lp_TestInstrumentGHB SHARED ${TestInstrumentGHB_SOURCES} )
target_link_libraries( lp_TestInstrumentGHB ${QT_LIBRARIES} )
