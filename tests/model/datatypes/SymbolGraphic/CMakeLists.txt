set( testname SymbolGraphicTest )
set( testmodules Test Widgets )
set( testlibraries )

find_package( Qt5Widgets REQUIRED )
find_package( Qt5Test    REQUIRED )

set( Test_SOURCES
        ${DATATYPES_SOURCE_DIR}/symbolgraphic.cpp
        tst_symbolgraphictest.cpp
        )

add_executable( ${testname} ${Test_SOURCES} )
qt5_use_modules( ${testname} ${testmodules} )
target_link_libraries( ${testname} ${testlibraries} )

add_test( NAME ${testname} COMMAND ${testname} )
