set( limepipes_SOURCES
        app/main.cpp
        app/mainwindow.cpp
        app/newtunedialog.cpp
        app/addsymbolsdialog.cpp
        app/aboutdialog.cpp

        views/treeview/lengthdelegate.cpp
        views/treeview/musicproxymodel.cpp
        views/treeview/musicsymboldatadelegate.cpp
        views/treeview/pitchdelegate.cpp
        views/treeview/treeview.cpp

        views/graphicsitemview/graphicsview.cpp
        views/graphicsitemview/graphicsscene.cpp
        views/graphicsitemview/graphicsitemview.cpp
        views/graphicsitemview/pageviewitem/pageviewitem.cpp
        views/graphicsitemview/pageviewitem/pageitem.cpp
        views/graphicsitemview/pageviewitem/pagecontentrowitem.cpp
        views/graphicsitemview/visualmusicpresenter.cpp
        views/graphicsitemview/musicsheetrowitems/textrowitem.cpp
        views/graphicsitemview/visualmusicmodel/visualmusicmodel.cpp
        views/graphicsitemview/visualmusicmodel/abstractvisualitem.cpp
        views/graphicsitemview/visualmusicmodel/visualrootitem.cpp
        views/graphicsitemview/visualmusicmodel/visualscore.cpp
        views/graphicsitemview/visualmusicmodel/visualtune.cpp
        views/graphicsitemview/visualmusicmodel/visualpart.cpp
        views/graphicsitemview/visualmusicmodel/visualmeasure.cpp
        views/graphicsitemview/visualmusicmodel/visualsymbol.cpp

        views/graphicsitemview/interactinggraphicsitems/interactinggraphicsitem.cpp
        views/graphicsitemview/interactinggraphicsitems/interactingscore.cpp
        views/graphicsitemview/interactinggraphicsitems/graphicalscoreitem.cpp
        views/graphicsitemview/interactinggraphicsitems/graphicitems/textwidget.cpp
        views/graphicsitemview/interactinggraphicsitems/graphicitems/textrowwidget.cpp
        views/graphicsitemview/interactinggraphicsitems/graphicitems/graphicstextitem.cpp
        views/graphicsitemview/scorepropertiesitem.cpp
        views/graphicsitemview/interactinggraphicsitems/dialogs/scorepropertiesdialog.cpp
        views/graphicsitemview/interactinggraphicsitems/dialogs/textpropertyeditwidget.cpp
        )

set( limepipes_UIs
        app/mainwindow.ui
        app/newtunedialog.ui
        app/addsymbolsdialog.ui
        app/aboutdialog.ui
        views/graphicsitemview/interactinggraphicsitems/dialogs/scorepropertiesdialog.ui
        views/graphicsitemview/interactinggraphicsitems/dialogs/textpropertyeditwidget.ui
        )

set( limepipes_RESOURCES
        app/app_resources.qrc
        )

find_package( Qt5Widgets REQUIRED )
find_package( Qt5PrintSupport REQUIRED )

QT5_WRAP_UI( limepipes_SOURCES ${limepipes_UIs} )

QT5_ADD_RESOURCES( limepipes_SOURCES ${limepipes_RESOURCES} )

set( EXECUTABLE_OUTPUT_PATH ${OUTPUT_BIN_FOLDER} )

add_executable( limepipes ${limepipes_SOURCES} )
qt5_use_modules( limepipes Widgets PrintSupport )

target_link_libraries( limepipes lp_model
                                 lp_greathighlandbagpipe
)

add_subdirectory( model )
add_subdirectory( plugins )

install( TARGETS limepipes DESTINATION bin )
