set( testname SymbolGraphicsItemTest )
set( testmodules Test Widgets )
set( testlibraries lp_model lp_integratedsymbols lp_graphicsitemview )

find_package( Qt5Widgets REQUIRED )
find_package( Qt5Test    REQUIRED )

set( Test_SOURCES
        ${CMAKE_SOURCE_DIR}/src/app/commonpluginmanager.cpp
        ${TEST_MOCK_DIR}/testsymbolgraphicbuilder.cpp
        ../common/iteminteractiondummy.cpp
        tst_symbolgraphicsitemtest.cpp
        )

include_directories(
    ${TEST_MOCK_DIR}
    ../common
)

add_executable( ${testname} ${Test_SOURCES} )
qt5_use_modules( ${testname} ${testmodules} )
target_link_libraries( ${testname} ${testlibraries} )

add_test( NAME ${testname} COMMAND ${testname} )
