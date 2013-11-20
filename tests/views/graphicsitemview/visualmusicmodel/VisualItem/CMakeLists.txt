set( testname AbstractVisualItemTest )
set( testmodules Test Gui )
set( testlibraries )

find_package( Qt5Gui REQUIRED )
find_package( Qt5Test    REQUIRED )

set( Test_SOURCES
        ${VIEWS_SOURCE_DIR}/graphicsitemview/visualmusicmodel/visualitem.cpp
        tst_visualitemtest.cpp
        )

add_executable( ${testname} ${Test_SOURCES} )
qt5_use_modules( ${testname} ${testmodules} )
target_link_libraries( ${testname} ${testlibraries} )

add_test( NAME ${testname} COMMAND ${testname} )
