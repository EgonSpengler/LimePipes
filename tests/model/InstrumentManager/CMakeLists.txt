set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR}/bin/plugins)

# InstrumentManager
set( InstrumentManagerTest_SOURCES InstrumentManager/tst_instrumentmanagertest.cpp )
qt4_automoc( ${InstrumentManagerTest_SOURCES} )
add_executable( InstrumentManagerTest ${InstrumentManagerTest_SOURCES} )
target_link_libraries( InstrumentManagerTest ${TEST_LIBRARIES} lp_greathighlandbagpipe lp_model)
add_test( NAME InstrumentManagerTest COMMAND InstrumentManagerTest )

# TestInstrumentForManager
set( TestInstrumentForManager_SOURCES TestInstrumentForManager/testinstrumentformanager.cpp )
set( TestInstrumentForManager_MOC_HEADERS TestInstrumentForManager/testinstrumentformanager.h )
qt4_wrap_cpp(TestInstrumentForManager_SOURCES ${TestInstrumentForManager_MOC_HEADERS})
add_library( lp_TestInstrumentForManager SHARED ${TestInstrumentForManager_SOURCES} )
target_link_libraries( lp_TestInstrumentForManager ${QT_LIBRARIES} )

# TestInstrumentGHB
SET( TestInstrumentGHB_SOURCES TestInstrumentGHB/testinstrumentghb.cpp )
SET( TestInstrumentGHB_MOC_HEADERS TestInstrumentGHB/testinstrumentghb.h )
qt4_wrap_cpp(TestInstrumentGHB_SOURCES ${TestInstrumentGHB_MOC_HEADERS})
add_library( lp_TestInstrumentGHB SHARED ${TestInstrumentGHB_SOURCES} )
target_link_libraries( lp_TestInstrumentGHB ${QT_LIBRARIES} )
