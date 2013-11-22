set( testname TextPropertyEditWidget )
set( testmodules Test Widgets )
set( testlibraries )

find_package( Qt5Widgets REQUIRED )
find_package( Qt5Test    REQUIRED )

set( ITEMINTERACTIONDIALOGS_SOURCE_DIR ${VIEWS_SOURCE_DIR}/graphicsitemview/visualmusicmodel/iteminteractions/dialogs )
set( Test_SOURCES
        ${ITEMINTERACTIONDIALOGS_SOURCE_DIR}/textpropertyeditwidget.cpp
        tst_textpropertyeditwidgettest.cpp
        )

set( Test_UIs
        ${ITEMINTERACTIONDIALOGS_SOURCE_DIR}/textpropertyeditwidget.ui
)
qt5_wrap_ui( Test_SOURCES ${Test_UIs} )

add_executable( ${testname} ${Test_SOURCES} )
qt5_use_modules( ${testname} ${testmodules} )
target_link_libraries( ${testname} ${testlibraries} )

add_test( NAME ${testname} COMMAND ${testname} )
