set( testname SymbolGraphicTest )
set( testmodules Test Gui )
set( testlibraries )

find_package( Qt5Gui REQUIRED )
find_package( Qt5Test    REQUIRED )

set( Test_SOURCES
        ${VIEWS_SOURCE_DIR}/common/symbolgraphic.cpp
        tst_symbolgraphictest.cpp
        )

add_executable( ${testname} ${Test_SOURCES} )
qt5_use_modules( ${testname} ${testmodules} )
target_link_libraries( ${testname} ${testlibraries} )

add_test( NAME ${testname} COMMAND ${testname} )
