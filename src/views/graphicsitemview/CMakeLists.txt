find_package( Qt5Widgets REQUIRED )
find_package( Qt5PrintSupport REQUIRED )

set( lp_graphicsitemview_SOURCES
        ${CMAKE_SOURCE_DIR}/src/model/datatypes/timesignature.cpp
        graphicsview.cpp
        graphicsscene.cpp
        graphicsitemview.cpp
        pageviewitem/pageviewitem.cpp
        pageviewitem/pageitem.cpp
        pageviewitem/pagecontentrowitem.cpp
        visualmusicpresenter.cpp
        musicsheetrowitems/textrowitem.cpp
        visualmusicmodel/visualmusicmodel.cpp
        visualmusicmodel/abstractvisualitem.cpp
        visualmusicmodel/visualrootitem.cpp
        visualmusicmodel/visualscore.cpp
        visualmusicmodel/visualtune.cpp
        visualmusicmodel/visualpart.cpp
        visualmusicmodel/visualmeasure.cpp
        visualmusicmodel/visualsymbol.cpp

        interactinggraphicsitems/interactinggraphicsitem.cpp
        interactinggraphicsitems/interactingscore.cpp
        interactinggraphicsitems/graphicalscoreitem.cpp
        interactinggraphicsitems/graphicitems/textwidget.cpp
        interactinggraphicsitems/graphicitems/textrowwidget.cpp
        interactinggraphicsitems/graphicitems/graphicstextitem.cpp
        scorepropertiesitem.cpp
        interactinggraphicsitems/dialogs/scorepropertiesdialog.cpp
        interactinggraphicsitems/dialogs/textpropertyeditwidget.cpp
        )

set( lp_graphicsitemview_UIs
        interactinggraphicsitems/dialogs/scorepropertiesdialog.ui
        interactinggraphicsitems/dialogs/textpropertyeditwidget.ui
        )
qt5_wrap_ui( lp_graphicsitemview_SOURCES ${lp_graphicsitemview_UIs} )

add_library( lp_graphicsitemview STATIC ${lp_graphicsitemview_SOURCES} )
qt5_use_modules( lp_graphicsitemview Widgets PrintSupport )
