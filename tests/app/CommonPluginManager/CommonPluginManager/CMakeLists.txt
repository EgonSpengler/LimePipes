set( testname CommonPluginManagerTest )
set( testmodules Test Gui )
set( testlibraries lp_greathighlandbagpipe lp_integratedsymbols )

find_package( Qt5Gui REQUIRED )
find_package( Qt5Test    REQUIRED )

set( Test_SOURCES
        ${CMAKE_SOURCE_DIR}/src/app/commonpluginmanager.cpp
        tst_commonpluginmanagertest.cpp
        )

add_executable( ${testname} ${Test_SOURCES} )
qt5_use_modules( ${testname} ${testmodules} )
target_link_libraries( ${testname} ${testlibraries} )

add_test( NAME ${testname} COMMAND ${testname} )
