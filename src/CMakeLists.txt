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
        )

set( limepipes_UIs
        app/mainwindow.ui
        app/newtunedialog.ui
        app/addsymbolsdialog.ui
        app/aboutdialog.ui
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

target_link_libraries( limepipes
                            lp_model
                            lp_greathighlandbagpipe
                            lp_graphicsitemview
)

add_subdirectory( model )
add_subdirectory( plugins )
add_subdirectory( views/graphicsitemview )

install( TARGETS limepipes DESTINATION bin )
