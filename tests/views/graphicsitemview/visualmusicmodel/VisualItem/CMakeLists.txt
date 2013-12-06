set( testname VisualItemTest )
set( testmodules Test Widgets )
set( testlibraries )

find_package( Qt5Widgets REQUIRED )
find_package( Qt5Test    REQUIRED )

set( Test_SOURCES
        ${VIEWS_SOURCE_DIR}/graphicsitemview/visualmusicmodel/visualitem.cpp
        ${VIEWS_SOURCE_DIR}/graphicsitemview/visualmusicmodel/interactinggraphicsitems/interactinggraphicsitem.cpp
        ${VIEWS_SOURCE_DIR}/graphicsitemview/visualmusicmodel/iteminteraction.cpp
        tst_visualitemtest.cpp
        testinteraction.cpp
        )

add_executable( ${testname} ${Test_SOURCES} )
qt5_use_modules( ${testname} ${testmodules} )
target_link_libraries( ${testname} ${testlibraries} )

add_test( NAME ${testname} COMMAND ${testname} )
