set( testname SymbolGraphicsItemTest )
set( testmodules Test Widgets )
set( testlibraries lp_graphicsitemview )

find_package( Qt5Widgets REQUIRED )
find_package( Qt5Test    REQUIRED )

set( Test_SOURCES
        ../common/iteminteractiondummy.cpp
        testgraphicbuilder.cpp
        tst_symbolgraphicsitemtest.cpp
        )

include_directories(
    ../common
)

add_executable( ${testname} ${Test_SOURCES} )
qt5_use_modules( ${testname} ${testmodules} )
target_link_libraries( ${testname} ${testlibraries} )

add_test( NAME ${testname} COMMAND ${testname} )
