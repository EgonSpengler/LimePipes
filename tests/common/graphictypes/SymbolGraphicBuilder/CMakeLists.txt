set( testname SymbolGraphicBuilderTest )
set( testmodules Test Gui XmlPatterns )
set( testlibraries lp_graphicsitemview )

find_package( Qt5Test  REQUIRED )
find_package( Qt5Gui   REQUIRED )
find_package( Qt5XmlPatterns  REQUIRED )

set( Test_SOURCES
        tst_symbolgraphicbuildertest.cpp
        ${TEST_MOCK_DIR}/testsymbolgraphicbuilder.cpp
        )

add_executable( ${testname} ${Test_SOURCES} )
qt5_use_modules( ${testname} ${testmodules} )
target_link_libraries( ${testname} ${testlibraries} )

add_test( NAME ${testname} COMMAND ${testname} )
