set( testname TextWidgetTest )
set( testmodules Test Widgets )
set( testlibraries )

find_package( Qt5Widgets REQUIRED )
find_package( Qt5Test    REQUIRED )

set( GRAPHICITEMS_SOURCE_DIR ${VIEWS_SOURCE_DIR}/graphicsitemview/interactinggraphicsitems/graphicitems )
set( Test_SOURCES
        ${GRAPHICITEMS_SOURCE_DIR}/graphicstextitem.cpp
        ${GRAPHICITEMS_SOURCE_DIR}/textwidget.cpp
        tst_textwidgettest.cpp
        )

add_executable( ${testname} ${Test_SOURCES} )
qt5_use_modules( ${testname} ${testmodules} )
target_link_libraries( ${testname} ${testlibraries} )

add_test( NAME ${testname} COMMAND ${testname} )
