set( testname PitchDelegateTest )
set( testmodules Test Widgets )
set( testlibraries lp_model lp_musicmodeltestplugin )

find_package( Qt5Widgets REQUIRED )
find_package( Qt5Test    REQUIRED )

set( Test_SOURCES
        ${VIEWS_SOURCE_DIR}/treeview/pitchdelegate.cpp
        ${VIEWS_SOURCE_DIR}/treeview/musicsymboldatadelegate.cpp
        tst_pitchdelegatetest.cpp
        )

add_executable( ${testname} ${Test_SOURCES} )
qt5_use_modules( ${testname} ${testmodules} )
target_link_libraries( ${testname} ${testlibraries} )

add_test( NAME ${testname} COMMAND ${testname} )
