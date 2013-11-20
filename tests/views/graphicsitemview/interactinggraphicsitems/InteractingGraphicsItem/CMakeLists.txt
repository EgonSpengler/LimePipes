set( testname InteractingGraphicsItemTest )
set( testmodules Test Widgets )
set( testlibraries lp_graphicsitemview )

find_package( Qt5Widgets REQUIRED )
find_package( Qt5Test    REQUIRED )

set( Test_SOURCES
        ${VIEWS_SOURCE_DIR}/graphicsitemview/interactinggraphicsitems/interactinggraphicsitem.cpp
        iteminteractiondummy.cpp
        tst_interactinggraphicsitemtest.cpp
        )

add_executable( ${testname} ${Test_SOURCES} )
qt5_use_modules( ${testname} ${testmodules} )
target_link_libraries( ${testname} ${testlibraries} )

add_test( NAME ${testname} COMMAND ${testname} )
