set( testname RootItemTest )
set( testmodules Test Core )
set( testlibraries lp_model )

find_package( Qt5Core REQUIRED )
find_package( Qt5Test    REQUIRED )

set( Test_SOURCES
        tst_rootitemtest.cpp
        )

add_executable( ${testname} ${Test_SOURCES} )
qt5_use_modules( ${testname} ${testmodules} )
target_link_libraries( ${testname} ${testlibraries} )

add_test( NAME ${testname} COMMAND ${testname} )
