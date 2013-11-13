set( testname GHBPluginTest )
set( testmodules Test Gui )
set( testlibraries lp_model )

find_package( Qt5Gui REQUIRED )
find_package( Qt5Test    REQUIRED )

set( Test_SOURCES
        ${PLUGINS_SOURCE_DIR}/GreatHighlandBagpipe/ghb_doubling.cpp
        ${PLUGINS_SOURCE_DIR}/GreatHighlandBagpipe/ghb_melodynote.cpp
        ${PLUGINS_SOURCE_DIR}/GreatHighlandBagpipe/ghb_instrument.cpp
        ${PLUGINS_SOURCE_DIR}/GreatHighlandBagpipe/greathighlandbagpipe.cpp
        tst_ghb_plugintest.cpp
        )

add_executable( ${testname} ${Test_SOURCES} )
qt5_use_modules( ${testname} ${testmodules} )
target_link_libraries( ${testname} ${testlibraries} )

add_test( NAME ${testname} COMMAND ${testname} )
