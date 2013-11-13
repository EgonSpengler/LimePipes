set( testname GHBDoublingTest )
set( testmodules Test Gui )
set( testlibraries lp_model )

find_package( Qt5Gui REQUIRED )
find_package( Qt5Test    REQUIRED )

set( Test_SOURCES
        ${PLUGINS_SOURCE_DIR}/GreatHighlandBagpipe/ghb_doubling.cpp
        tst_ghb_doublingtest.cpp
        )

add_executable( ${testname} ${Test_SOURCES} )
qt5_use_modules( ${testname} ${testmodules} )
target_link_libraries( ${testname} ${testlibraries} )

add_test( NAME ${testname} COMMAND ${testname} )
