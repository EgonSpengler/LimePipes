project( limepipes )

cmake_minimum_required( VERSION 2.6 )

set ( CMAKE_BUILD_TYPE Release )

add_definitions ( -Wall )

find_package ( Qt4 REQUIRED )

set ( limepipes_HEADERS
        model/instrumentmanager.h
        model/itemdatatypes.h
        model/musicitem.h
        model/musicmodelinterface.h
        model/rootitem.h
        model/score.h
        model/symbol.h
        model/tune.h
        model/symbolgraphicbuilder.h

        model/datatypes/pitchcontext.h

        model/musicfont/emmentalermusicfont.h
        model/musicfont/musicfont.h

        model/symbols/melodynote.h
        model/symbols/melodynotegraphicbuilder.h

        utilities/error.h
        )

set ( limepipes_SOURCES
        app/main.cpp
        app/mainwindow.cpp
        app/newtunedialog.cpp
        app/addsymbolsdialog.cpp

        model/instrumentmanager.cpp
        model/musicitem.cpp
        model/musicmodel.cpp
        model/rootitem.cpp
        model/score.cpp
        model/symbol.cpp
        model/tune.cpp
        model/symbolgraphicbuilder.cpp

        model/datatypes/instrument.cpp
        model/datatypes/length.cpp
        model/datatypes/pitch.cpp
        model/datatypes/pitchcontext.cpp
        model/datatypes/symbolgraphic.cpp
        model/datatypes/timesignature.cpp

        model/musicfont/emmentalermusicfont.cpp
        model/musicfont/musicfont.cpp

        model/symbols/barline.cpp
        model/symbols/melodynote.cpp
        model/symbols/melodynotegraphicbuilder.cpp

        views/treeview/lengthdelegate.cpp
        views/treeview/musicproxymodel.cpp
        views/treeview/musicsymboldatadelegate.cpp
        views/treeview/pitchdelegate.cpp
        views/treeview/treeview.cpp
        )

set ( limepipes_MOC_HEADERS
        app/mainwindow.h
        app/newtunedialog.h
        app/addsymbolsdialog.h

        interfaces/instrumentinterface.h
        interfaces/interfaceglobals.h
        interfaces/symbolinterface.h

        model/musicmodel.h

        model/commands/insertitemscommand.h
        model/commands/removeitemscommand.h

        model/datatypes/instrument.h
        model/datatypes/length.h
        model/datatypes/pitch.h
        model/datatypes/symbolgraphic.h
        model/datatypes/timesignature.h

        model/symbols/barline.h

        views/treeview/lengthdelegate.h
        views/treeview/musicproxymodel.h
        views/treeview/musicsymboldatadelegate.h
        views/treeview/pitchdelegate.h
        views/treeview/treeview.h
        )

set ( limepipes_UIs
        app/mainwindow.ui
        app/newtunedialog.ui
        app/addsymbolsdialog.ui
        )

set ( limepipes_RESOURCES
        app/app_resources.qrc
        model/musicfont/musicfont_resources.qrc
        )

include ( ${QT_USE_FILE} )

include_directories (
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

add_subdirectory( plugins )

QT4_WRAP_UI(limepipes_SOURCES ${limepipes_UIs})

QT4_WRAP_CPP(limepipes_SOURCES ${limepipes_MOC_HEADERS})

QT4_ADD_RESOURCES(limepipes_SOURCES ${limepipes_RESOURCES})

set(EXECUTABLE_OUTPUT_PATH ${OUTPUT_BIN_FOLDER})
add_executable ( limepipes ${limepipes_SOURCES} )

target_link_libraries ( limepipes  ${QT_LIBRARIES} lp_greathighlandbagpipe)

INSTALL ( TARGETS limepipes DESTINATION bin )
