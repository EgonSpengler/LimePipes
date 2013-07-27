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

# MainWindow
set( MainwindowTest_HEADERS
        ${CMAKE_SOURCE_DIR}/src/views/graphicsitemview/pageviewitem/pagecontentrowitem.h
        ${CMAKE_SOURCE_DIR}/src/views/graphicsitemview/musicsheetrowitems/textrowitem.h
        ${CMAKE_SOURCE_DIR}/src/views/graphicsitemview/visualmusicmodel/visualmusicmodel.h
        )

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

        ${CMAKE_SOURCE_DIR}/src/views/graphicsitemview/graphicsitemview.cpp
        ${CMAKE_SOURCE_DIR}/src/views/graphicsitemview/graphicsview.cpp
        ${CMAKE_SOURCE_DIR}/src/views/graphicsitemview/graphicsscene.cpp
        ${CMAKE_SOURCE_DIR}/src/views/graphicsitemview/pageviewitem/pageviewitem.cpp
        ${CMAKE_SOURCE_DIR}/src/views/graphicsitemview/pageviewitem/pageitem.cpp
        ${CMAKE_SOURCE_DIR}/src/views/graphicsitemview/pageviewitem/pagecontentrowitem.cpp
        ${CMAKE_SOURCE_DIR}/src/views/graphicsitemview/musicsheetrowitems/textrowitem.cpp
        ${CMAKE_SOURCE_DIR}/src/views/graphicsitemview/visualmusicmodel/visualmusicmodel.cpp
        )

set( MainwindowTest_MOC_HEADERS
        MainWindow/tst_mainwindowtest.h
        ${CMAKE_SOURCE_DIR}/src/app/mainwindow.h
        ${CMAKE_SOURCE_DIR}/src/app/addsymbolsdialog.h
        ${CMAKE_SOURCE_DIR}/src/app/newtunedialog.h
        ${CMAKE_SOURCE_DIR}/src/app/aboutdialog.h

        ${CMAKE_SOURCE_DIR}/src/views/treeview/lengthdelegate.h
        ${CMAKE_SOURCE_DIR}/src/views/treeview/musicproxymodel.h
        ${CMAKE_SOURCE_DIR}/src/views/treeview/musicsymboldatadelegate.h
        ${CMAKE_SOURCE_DIR}/src/views/treeview/pitchdelegate.h
        ${CMAKE_SOURCE_DIR}/src/views/treeview/treeview.h

        ${CMAKE_SOURCE_DIR}/src/views/graphicsitemview/graphicsitemview.h
        ${CMAKE_SOURCE_DIR}/src/views/graphicsitemview/graphicsview.h
        ${CMAKE_SOURCE_DIR}/src/views/graphicsitemview/graphicsscene.h
        ${CMAKE_SOURCE_DIR}/src/views/graphicsitemview/pageviewitem/pageitem.h
        ${CMAKE_SOURCE_DIR}/src/views/graphicsitemview/pageviewitem/pageviewitem.h
        )

set( MainwindowTest_UIs
        ${CMAKE_SOURCE_DIR}/src/app/mainwindow.ui
        ${CMAKE_SOURCE_DIR}/src/app/addsymbolsdialog.ui
        ${CMAKE_SOURCE_DIR}/src/app/newtunedialog.ui
        ${CMAKE_SOURCE_DIR}/src/app/aboutdialog.ui
        )

qt4_wrap_cpp( MainwindowTest_SOURCES ${MainwindowTest_MOC_HEADERS} )

qt4_wrap_ui( MainwindowTest_SOURCES ${MainwindowTest_UIs} )

add_executable( MainwindowTest ${MainwindowTest_SOURCES} ${MainwindowTest_HEADERS} )
target_link_libraries( MainwindowTest lp_greathighlandbagpipe ${TEST_LIBRARIES} )
add_test( NAME MainwindowTest COMMAND MainwindowTest )
