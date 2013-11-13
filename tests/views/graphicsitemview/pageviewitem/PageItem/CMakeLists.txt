set( testname PageItemTest )
set( testmodules Test Gui PrintSupport )
set( testlibraries )

find_package( Qt5PrintSupport REQUIRED )
find_package( Qt5Gui REQUIRED )
find_package( Qt5Test    REQUIRED )

set( Test_SOURCES
        ${VIEWS_SOURCE_DIR}/graphicsitemview/pageviewitem/pageitem.cpp
        tst_pageitemtest.cpp
        )

add_executable( ${testname} ${Test_SOURCES} )
qt5_use_modules( ${testname} ${testmodules} )
target_link_libraries( ${testname} ${testlibraries} )

add_test( NAME ${testname} COMMAND ${testname} )
