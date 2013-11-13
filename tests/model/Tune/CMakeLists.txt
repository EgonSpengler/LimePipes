set( testname TuneTest )
set( testmodules Test Gui )
set( testlibraries lp_model lp_greathighlandbagpipe )

find_package( Qt5Gui    REQUIRED )
find_package( Qt5Test   REQUIRED )

set( Test_SOURCES
        tst_tunetest.cpp
        )

add_executable( ${testname} ${Test_SOURCES} )
qt5_use_modules( ${testname} ${testmodules} )
target_link_libraries( ${testname} ${testlibraries} )

add_test( NAME ${testname} COMMAND ${testname} )
