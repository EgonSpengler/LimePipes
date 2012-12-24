set( limepipes_HEADERS
        interfaces/instrumentinterface.h
        interfaces/interfaceglobals.h
        interfaces/symbolinterface.h

        utilities/error.h
        )

set( limepipes_SOURCES
        app/main.cpp
        app/mainwindow.cpp
        app/newtunedialog.cpp
        app/addsymbolsdialog.cpp

        views/treeview/lengthdelegate.cpp
        views/treeview/musicproxymodel.cpp
        views/treeview/musicsymboldatadelegate.cpp
        views/treeview/pitchdelegate.cpp
        views/treeview/treeview.cpp
        )

set( limepipes_MOC_HEADERS
        app/mainwindow.h
        app/newtunedialog.h
        app/addsymbolsdialog.h

        views/treeview/lengthdelegate.h
        views/treeview/musicproxymodel.h
        views/treeview/musicsymboldatadelegate.h
        views/treeview/pitchdelegate.h
        views/treeview/treeview.h
        )

set( limepipes_UIs
        app/mainwindow.ui
        app/newtunedialog.ui
        app/addsymbolsdialog.ui
        )

set( limepipes_RESOURCES
        app/app_resources.qrc
        )

include( ${QT_USE_FILE} )

include_directories(
        ${CMAKE_SOURCE_DIR}
        ${CMAKE_CURRENT_BINARY_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}
        "${CMAKE_CURRENT_SOURCE_DIR}/model"
        "${CMAKE_CURRENT_SOURCE_DIR}/interfaces"
        "${CMAKE_CURRENT_SOURCE_DIR}/views"
        "${CMAKE_CURRENT_SOURCE_DIR}/app"
        ${QT_QTCORE_INCLUDE_DIR}
        ${QT_QTGUI_INCLUDE_DIR}
        )

add_subdirectory( model )
add_subdirectory( plugins )

QT4_WRAP_UI( limepipes_SOURCES ${limepipes_UIs} )

QT4_WRAP_CPP( limepipes_SOURCES ${limepipes_MOC_HEADERS} )

QT4_ADD_RESOURCES( limepipes_SOURCES ${limepipes_RESOURCES} )

set( EXECUTABLE_OUTPUT_PATH ${OUTPUT_BIN_FOLDER} )
add_executable( limepipes ${limepipes_SOURCES} )

target_link_libraries( limepipes  ${QT_LIBRARIES} lp_greathighlandbagpipe lp_model)

install( TARGETS limepipes DESTINATION bin )
