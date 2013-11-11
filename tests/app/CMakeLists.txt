
# AddSymbolsDialog
set( AddSymbolsDialogTest_SOURCES
        AddSymbolsDialog/tst_addsymbolsdialogtest.cpp
        ${CMAKE_SOURCE_DIR}/src/app/addsymbolsdialog.cpp
        )

set( AddSymbolsDialogTest_MOC_HEADERS
        AddSymbolsDialog/tst_addsymbolsdialogtest.h
        ${CMAKE_SOURCE_DIR}/src/app/addsymbolsdialog.h
        )

set( AddSymbolsDialogTest_UIs
        ${CMAKE_SOURCE_DIR}/src/app/addsymbolsdialog.ui
        )

qt4_wrap_cpp( AddSymbolsDialogTest_SOURCES ${AddSymbolsDialogTest_MOC_HEADERS} )

qt4_wrap_ui( AddSymbolsDialogTest_SOURCES ${AddSymbolsDialogTest_UIs} )

add_executable( AddSymbolsDialogTest ${AddSymbolsDialogTest_SOURCES} )
target_link_libraries( AddSymbolsDialogTest ${TEST_LIBRARIES} )
add_test( NAME AddSymbolsDialogTest COMMAND AddSymbolsDialogTest )

# NewTuneDialog
set( NewTuneDialogTest_SOURCES
        NewTuneDialog/tst_newtunedialogtest.cpp
        ${CMAKE_SOURCE_DIR}/src/app/newtunedialog.cpp
        )

set( NewTuneDialogTest_MOC_HEADERS
        NewTuneDialog/tst_newtunedialogtest.h
        ${CMAKE_SOURCE_DIR}/src/app/newtunedialog.h
        )

set( AddSymbolsDialogTest_UIs
        ${CMAKE_SOURCE_DIR}/src/app/newtunedialog.ui
        )

qt4_wrap_cpp( NewTuneDialogTest_SOURCES ${NewTuneDialogTest_MOC_HEADERS} )

qt4_wrap_ui( NewTuneDialogTest_SOURCES ${AddSymbolsDialogTest_UIs} )

add_executable( NewTuneDialogTest ${NewTuneDialogTest_SOURCES} )
target_link_libraries( NewTuneDialogTest ${TEST_LIBRARIES} )
add_test( NAME NewTuneDialogTest COMMAND NewTuneDialogTest )

set(CMAKE_AUTOMOC ON)

file(GLOB_RECURSE GraphicsItemView_SOURCES ${CMAKE_SOURCE_DIR}/src/views/graphicsitemview/*.cpp)
set( MainwindowTest_SOURCES
        MainWindow/tst_mainwindowtest.cpp
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


set( MainwindowTest_UIs
        ${CMAKE_SOURCE_DIR}/src/app/mainwindow.ui
        ${CMAKE_SOURCE_DIR}/src/app/addsymbolsdialog.ui
        ${CMAKE_SOURCE_DIR}/src/app/newtunedialog.ui
        ${CMAKE_SOURCE_DIR}/src/app/aboutdialog.ui
        ${CMAKE_SOURCE_DIR}/src/views/graphicsitemview/interactinggraphicsitems/dialogs/scorepropertiesdialog.ui
        ${CMAKE_SOURCE_DIR}/src/views/graphicsitemview/interactinggraphicsitems/dialogs/textpropertyeditwidget.ui
        )

qt4_wrap_ui( MainwindowTest_SOURCES ${MainwindowTest_UIs} )

add_executable( MainwindowTest ${MainwindowTest_SOURCES} ${GraphicsItemView_SOURCES} )
target_link_libraries( MainwindowTest lp_greathighlandbagpipe ${TEST_LIBRARIES} )
add_test( NAME MainwindowTest COMMAND MainwindowTest )
