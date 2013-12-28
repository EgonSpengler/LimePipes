set( limepipes_SOURCES
        app/main.cpp
        app/mainwindow.cpp
        app/dialogs/newtunedialog.cpp
        app/dialogs/addsymbolsdialog.cpp
        app/dialogs/aboutdialog.cpp
        app/dialogs/settingsdialog.cpp
        app/dialogs/settingspages/scorepropertiessettingspage.cpp
        app/dialogs/settingspages/scorepropertieswidget.cpp
        common/scoresettings.cpp

        views/treeview/lengthdelegate.cpp
        views/treeview/musicproxymodel.cpp
        views/treeview/musicsymboldatadelegate.cpp
        views/treeview/pitchdelegate.cpp
        views/treeview/treeview.cpp
        )

set( limepipes_UIs
        app/mainwindow.ui
        app/dialogs/newtunedialog.ui
        app/dialogs/addsymbolsdialog.ui
        app/dialogs/aboutdialog.ui
        app/dialogs/settingsdialog.ui
        app/dialogs/settingspages/scorepropertiessettingspage.ui
        app/dialogs/settingspages/scorepropertieswidget.ui
        )

set( limepipes_RESOURCES
        app/app_resources.qrc
        )

find_package( Qt5Widgets REQUIRED )
find_package( Qt5PrintSupport REQUIRED )

QT5_WRAP_UI( limepipes_SOURCES ${limepipes_UIs} )

QT5_ADD_RESOURCES( limepipes_SOURCES ${limepipes_RESOURCES} )

set( EXECUTABLE_OUTPUT_PATH ${OUTPUT_BIN_FOLDER} )

add_executable( LimePipes ${limepipes_SOURCES} )
qt5_use_modules( LimePipes Widgets PrintSupport )

target_link_libraries( LimePipes
                            lp_model
                            lp_greathighlandbagpipe
                            lp_graphicsitemview
)

add_subdirectory( model )
add_subdirectory( plugins )
add_subdirectory( views/graphicsitemview )

install( TARGETS LimePipes DESTINATION bin )
