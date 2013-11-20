find_package( Qt5Widgets REQUIRED )
find_package( Qt5PrintSupport REQUIRED )

set( lp_graphicsitemview_SOURCES
        graphicsview.cpp
        graphicsscene.cpp
        graphicsitemview.cpp
        visualmusicpresenter.cpp

        pageviewitem/pageviewitem.cpp
        pageviewitem/pageitem.cpp

        visualmusicmodel/visualmusicmodel.cpp
        visualmusicmodel/visualitem.cpp
        visualmusicmodel/visualscore.cpp
        visualmusicmodel/visualtune.cpp
        visualmusicmodel/visualpart.cpp
        visualmusicmodel/visualmeasure.cpp
        visualmusicmodel/visualsymbol.cpp
        visualmusicmodel/iteminteraction.cpp

        visualmusicmodel/iteminteractions/scoreinteraction.cpp
        visualmusicmodel/iteminteractions/dialogs/scorepropertiesdialog.cpp
        visualmusicmodel/iteminteractions/dialogs/textpropertyeditwidget.cpp

        visualmusicmodel/interactinggraphicsitems/interactinggraphicsitem.cpp
        visualmusicmodel/interactinggraphicsitems/scoregraphicsitem.cpp
        visualmusicmodel/interactinggraphicsitems/graphicitems/textwidget.cpp
        visualmusicmodel/interactinggraphicsitems/graphicitems/textrowwidget.cpp
        visualmusicmodel/interactinggraphicsitems/graphicitems/graphicstextitem.cpp
        )

set( lp_graphicsitemview_UIs
        visualmusicmodel/iteminteractions/dialogs/scorepropertiesdialog.ui
        visualmusicmodel/iteminteractions/dialogs/textpropertyeditwidget.ui
        )
qt5_wrap_ui( lp_graphicsitemview_SOURCES ${lp_graphicsitemview_UIs} )

add_library( lp_graphicsitemview STATIC ${lp_graphicsitemview_SOURCES} )
qt5_use_modules( lp_graphicsitemview Widgets PrintSupport )
