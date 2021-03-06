find_package( Qt5Widgets REQUIRED )
find_package( Qt5PrintSupport REQUIRED )

set( GRAPHICTYPES_DIR ${CMAKE_SOURCE_DIR}/src/common/graphictypes )
set( TYPES_DIR ${CMAKE_SOURCE_DIR}/src/common/datatypes )

set( lp_graphicsitemview_SOURCES
        graphicsview.cpp
        graphicsscene.cpp
        graphicsitemview.cpp
        visualmusicpresenter.cpp

        ${CMAKE_SOURCE_DIR}/src/common/scoresettings.cpp
        ${CMAKE_SOURCE_DIR}/src/common/observablesettings.cpp
        ${CMAKE_SOURCE_DIR}/src/common/settingsobserver.cpp

        ${GRAPHICTYPES_DIR}/glyphitem.cpp
        ${GRAPHICTYPES_DIR}/iteminteraction.cpp
        ${GRAPHICTYPES_DIR}/baseengraver.cpp
        ${GRAPHICTYPES_DIR}/stemengraver.cpp
        ${GRAPHICTYPES_DIR}/tieengraver.cpp
        ${GRAPHICTYPES_DIR}/tiegraphicsitem.cpp
        ${GRAPHICTYPES_DIR}/stemglyphitem.cpp
        ${GRAPHICTYPES_DIR}/clefglyphitem.cpp
        ${GRAPHICTYPES_DIR}/timesignatureglyphitem.cpp

        ${TYPES_DIR}/pitchcontext.cpp
        ${TYPES_DIR}/pitch.cpp

        pageviewitem/pageviewitem.cpp
        pageviewitem/pageitem.cpp

        visualmusicmodel/visualitemfactory.cpp
        visualmusicmodel/visualmusicmodel.cpp
        visualmusicmodel/visualitem.cpp
        visualmusicmodel/visualpart.cpp
        visualmusicmodel/rowiterator.cpp
        visualmusicmodel/sequentialtunesrowiterator.cpp

        visualmusicmodel/iteminteractions/scoreinteraction.cpp
        visualmusicmodel/iteminteractions/symbolinteraction.cpp
        visualmusicmodel/iteminteractions/dialogs/scorepropertiesdialog.cpp
        visualmusicmodel/iteminteractions/dialogs/textpropertyeditwidget.cpp

        visualmusicmodel/interactinggraphicsitems/interactinggraphicsitem.cpp
        visualmusicmodel/interactinggraphicsitems/scoregraphicsitem.cpp
        visualmusicmodel/interactinggraphicsitems/graphicitems/textwidget.cpp
        visualmusicmodel/interactinggraphicsitems/graphicitems/textrowwidget.cpp
        visualmusicmodel/interactinggraphicsitems/graphicitems/graphicstextitem.cpp
        visualmusicmodel/interactinggraphicsitems/staffgraphicsitem.cpp
        visualmusicmodel/interactinggraphicsitems/measuregraphicsitem.cpp
        visualmusicmodel/interactinggraphicsitems/symbolgraphicsitem.cpp
        )

set( lp_graphicsitemview_UIs
        visualmusicmodel/iteminteractions/dialogs/scorepropertiesdialog.ui
        visualmusicmodel/iteminteractions/dialogs/textpropertyeditwidget.ui
        )
qt5_wrap_ui( lp_graphicsitemview_SOURCES ${lp_graphicsitemview_UIs} )

set( lp_graphicsitemview_RESOURCES
        )

qt5_add_resources( lp_graphicsitemview_SOURCES ${lp_graphicsitemview_RESOURCES} )

add_library( lp_graphicsitemview STATIC ${lp_graphicsitemview_SOURCES} )
qt5_use_modules( lp_graphicsitemview Widgets PrintSupport )
