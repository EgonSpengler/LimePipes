set( testname VisualItemFactoryTest )
set( testmodules Test Widgets )
set( testlibraries lp_model lp_graphicsitemview )

find_package( Qt5Widgets REQUIRED )
find_package( Qt5Test    REQUIRED )

set( Test_SOURCES
        ${CMAKE_SOURCE_DIR}/src/app/commonpluginmanager.cpp
        tst_visualitemfactorytest.cpp
        )

add_executable( ${testname} ${Test_SOURCES} )
qt5_use_modules( ${testname} ${testmodules} )
target_link_libraries( ${testname} ${testlibraries} )

add_test( NAME ${testname} COMMAND ${testname} )
