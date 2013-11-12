set( testname MainWindowTest )
set( testmodules Test Widgets PrintSupport )
set( testlibraries lp_greathighlandbagpipe lp_model lp_graphicsitemview )

find_package( Qt5Widgets REQUIRED )
find_package( Qt5Test    REQUIRED )
find_package( Qt5PrintSupport REQUIRED )

set( Test_SOURCES
        tst_mainwindowtest.cpp
        ${CMAKE_SOURCE_DIR}/src/app/mainwindow.cpp
        ${CMAKE_SOURCE_DIR}/src/app/addsymbolsdialog.cpp
        ${CMAKE_SOURCE_DIR}/src/app/newtunedialog.cpp
        ${CMAKE_SOURCE_DIR}/src/app/aboutdialog.cpp

        ${CMAKE_SOURCE_DIR}/src/views/treeview/lengthdelegate.cpp
        ${CMAKE_SOURCE_DIR}/src/views/treeview/musicproxymodel.cpp
        ${CMAKE_SOURCE_DIR}/src/views/treeview/musicsymboldatadelegate.cpp
        ${CMAKE_SOURCE_DIR}/src/views/treeview/pitchdelegate.cpp
        ${CMAKE_SOURCE_DIR}/src/views/treeview/treeview.cpp
        )

set( Test_UIs
        ${CMAKE_SOURCE_DIR}/src/app/mainwindow.ui
        ${CMAKE_SOURCE_DIR}/src/app/addsymbolsdialog.ui
        ${CMAKE_SOURCE_DIR}/src/app/newtunedialog.ui
        ${CMAKE_SOURCE_DIR}/src/app/aboutdialog.ui
        )

qt5_wrap_ui( Test_SOURCES ${Test_UIs} )

add_executable( ${testname} ${Test_SOURCES} )
qt5_use_modules( ${testname} ${testmodules} )
target_link_libraries( ${testname} ${testlibraries} )

add_test( NAME ${testname} COMMAND ${testname} )
