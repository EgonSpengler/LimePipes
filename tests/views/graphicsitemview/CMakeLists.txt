set( PageViewItem_HEADERS
        ${CMAKE_SOURCE_DIR}/src/views/graphicsitemview/pageviewitem/pagecontentrowitem.h
        ${CMAKE_SOURCE_DIR}/src/views/graphicsitemview/musicsheetrowitems/textrowitem.h
        )
set( PageViewItem_SOURCES
        ${CMAKE_SOURCE_DIR}/src/views/graphicsitemview/pageviewitem/pageitem.cpp
        ${CMAKE_SOURCE_DIR}/src/views/graphicsitemview/pageviewitem/pagecontentrowitem.cpp
        ${CMAKE_SOURCE_DIR}/src/views/graphicsitemview/pageviewitem/pageviewitem.cpp
        ${CMAKE_SOURCE_DIR}/src/views/graphicsitemview/musicsheetrowitems/textrowitem.cpp
        )
set( PageViewItem_MOC_HEADERS
        ${CMAKE_SOURCE_DIR}/src/views/graphicsitemview/pageviewitem/pageitem.h
        ${CMAKE_SOURCE_DIR}/src/views/graphicsitemview/pageviewitem/pageviewitem.h
        )
qt4_wrap_cpp( PageViewItem_SOURCES ${PageViewItem_MOC_HEADERS} )


# PageContentRowItem
set( PageContentRowItemTest_SOURCES
        pageviewitem/PageContentRowItem/tst_pagecontentrowitemtest.cpp
        )
set( PageContentRowItemTest_MOC_HEADERS
        pageviewitem/PageContentRowItem/tst_pagecontentrowitemtest.h
        )
qt4_wrap_cpp( PageContentRowItemTest_SOURCES ${PageContentRowItemTest_MOC_HEADERS} )
add_executable( PageContentRowItemTest ${PageContentRowItemTest_SOURCES}
        ${PageViewItem_SOURCES}
        ${PageViewItem_HEADERS} )
target_link_libraries( PageContentRowItemTest ${TEST_LIBRARIES} )
add_test( NAME PageContentRowItemTest COMMAND PageContentRowItemTest )

# PageItem
set( PageItemTest_SOURCES
        pageviewitem/PageItem/tst_pageitemtest.cpp
        )
set( PageItemTest_MOC_HEADERS
        pageviewitem/PageItem/tst_pageitemtest.h
        )
qt4_wrap_cpp( PageItemTest_SOURCES ${PageItemTest_MOC_HEADERS} )
add_executable( PageItemTest ${PageItemTest_SOURCES}
        ${PageViewItem_SOURCES}
        ${PageViewItem_HEADERS} )
target_link_libraries( PageItemTest ${TEST_LIBRARIES} )
add_test( NAME PageItemTest COMMAND PageItemTest )

# PageViewItem
set( PageViewItemTest_SOURCES
        pageviewitem/PageViewItem/tst_pageviewitemtest.cpp
        )
set( PageViewItemTest_MOC_HEADERS
        pageviewitem/PageViewItem/tst_pageviewitemtest.h
        )
qt4_wrap_cpp( PageViewItemTest_SOURCES ${PageViewItemTest_MOC_HEADERS} )
add_executable( PageViewItemTest ${PageViewItemTest_SOURCES}
        ${PageViewItem_SOURCES}
        ${PageViewItem_HEADERS} )
target_link_libraries( PageViewItemTest ${TEST_LIBRARIES} )
add_test( NAME PageViewItemTest COMMAND PageViewItemTest )

set(CMAKE_AUTOMOC ON)
file(GLOB_RECURSE GraphicsItemView_SOURCES "${CMAKE_SOURCE_DIR}/src/views/graphicsitemview/*.cpp")

# VisualMusicModel
set( VisualMusicModelTest_SOURCES
        visualmusicmodel/VisualMusicModel/tst_visualmusicmodel.cpp
        )

add_executable( VisualMusicModelTest
    ${GraphicsItemView_SOURCES}
    ${VisualMusicModelTest_SOURCES}
    ${VisualMusicModelTest_SOURCES})
target_link_libraries( VisualMusicModelTest ${TEST_LIBRARIES} lp_greathighlandbagpipe )
add_test( NAME VisualMusicModelTest COMMAND VisualMusicModelTest )


# GraphicsItemView
set( GraphicsItemViewTest_SOURCES
        GraphicsItemView/tst_graphicsitemviewtest.cpp
        GraphicsItemView/visualmusicmodeldummy.h
        )

add_executable( GraphicsItemViewTest
        ${VisualMusicModel_SOURCES}
        ${GraphicsItemViewTest_SOURCES}
        ${GraphicsItemView_SOURCES} )

target_link_libraries( GraphicsItemViewTest ${TEST_LIBRARIES} lp_greathighlandbagpipe )
add_test( NAME GraphicsItemViewTest COMMAND GraphicsItemViewTest )

# AbstractVisualItemTest
set( AbstractVisualItem_TEST_SOURCES
        visualmusicmodel/AbstractVisualItem/tst_abstractvisualitemtest.cpp
        visualmusicmodel/AbstractVisualItem/testabstractvisualitem.cpp
        )

add_executable( AbstractVisualItemTest ${GraphicsItemView_SOURCES}
    ${AbstractVisualItem_TEST_SOURCES})
target_link_libraries( AbstractVisualItemTest ${TEST_LIBRARIES} )
add_test( NAME AbstractVisualItemTest COMMAND AbstractVisualItemTest )

# VisualRootItem
set( VisualRootItem_TEST_SOURCES
        visualmusicmodel/VisualRootItem/tst_visualrootitemtest.cpp
        )

add_executable( VisualRootItemTest ${GraphicsItemView_SOURCES}
    ${VisualRootItem_TEST_SOURCES})
target_link_libraries( VisualRootItemTest ${TEST_LIBRARIES} )
add_test( NAME VisualRootItemTest COMMAND VisualRootItemTest )

# VisualScoreTest
set( VisualScore_TEST_SOURCES
        visualmusicmodel/VisualScore/tst_visualscoretest.cpp
        )

add_executable( VisualScoreTest ${GraphicsItemView_SOURCES}
    ${VisualScore_TEST_SOURCES})
target_link_libraries( VisualScoreTest ${TEST_LIBRARIES} )
add_test( NAME VisualScoreTest COMMAND VisualScoreTest )

# VisualTuneTest
set( VisualTune_TEST_SOURCES
        visualmusicmodel/VisualTune/tst_visualtunetest.cpp
        )

add_executable( VisualTuneTest ${GraphicsItemView_SOURCES}
    ${VisualTune_TEST_SOURCES})
target_link_libraries( VisualTuneTest ${TEST_LIBRARIES} )
add_test( NAME VisualTuneTest COMMAND VisualTuneTest )

# VisualPartTest
set( VisualPart_TEST_SOURCES
        visualmusicmodel/VisualPart/tst_visualparttest.cpp
        )

add_executable( VisualPartTest ${GraphicsItemView_SOURCES}
    ${VisualPart_TEST_SOURCES})
target_link_libraries( VisualPartTest ${TEST_LIBRARIES} )
add_test( NAME VisualPartTest COMMAND VisualPartTest )

# VisualMeasureTest
set( VisualMeasure_TEST_SOURCES
        visualmusicmodel/VisualMeasure/tst_visualmeasuretest.cpp
        )

add_executable( VisualMeasureTest ${GraphicsItemView_SOURCES}
    ${VisualMeasure_TEST_SOURCES})
target_link_libraries( VisualMeasureTest ${TEST_LIBRARIES} )
add_test( NAME VisualMeasureTest COMMAND VisualMeasureTest )

# VisualSymbolTest
set( VisualSymbol_TEST_SOURCES
        visualmusicmodel/VisualSymbol/tst_visualsymboltest.cpp
        )

add_executable( VisualSymbolTest ${GraphicsItemView_SOURCES}
    ${VisualSymbol_TEST_SOURCES})
target_link_libraries( VisualSymbolTest ${TEST_LIBRARIES} )
add_test( NAME VisualSymbolTest COMMAND VisualSymbolTest )

# InteractingGraphicsItem
set( InteractingGraphicsItem_TEST_SOURCES
        interactinggraphicsitem/InteractingGraphicsItem/tst_interactinggraphicsitemtest.cpp
        interactinggraphicsitem/InteractingGraphicsItem/interactingitemdummy.cpp
        )

add_executable( InteractingGraphicsItemTest ${GraphicsItemView_SOURCES}
    ${InteractingGraphicsItem_TEST_SOURCES})
target_link_libraries( InteractingGraphicsItemTest ${TEST_LIBRARIES} )
add_test( NAME InteractingGraphicsItemTest COMMAND InteractingGraphicsItemTest )

# InteractingScore
set( InteractingScore_TEST_SOURCES
        interactinggraphicsitem/InteractingScore/tst_interactingscoretest.cpp
        )

add_executable( InteractingScoreTest ${GraphicsItemView_SOURCES}
    ${InteractingScore_TEST_SOURCES})
target_link_libraries( InteractingScoreTest ${TEST_LIBRARIES} )
add_test( NAME InteractingScoreTest COMMAND InteractingScoreTest )

# GraphicalScoreItem
set( GraphicalScoreItem_TEST_SOURCES
        interactinggraphicsitem/GraphicalScoreItem/tst_graphicalscoreitemtest.cpp
        )

add_executable( GraphicalScoreItemTest ${GraphicsItemView_SOURCES}
    ${GraphicalScoreItem_TEST_SOURCES})
target_link_libraries( GraphicalScoreItemTest ${TEST_LIBRARIES} )
add_test( NAME GraphicalScoreItemTest COMMAND GraphicalScoreItemTest )

# ScorePropertiesItem
set( ScorePropertiesItem_TEST_SOURCES
        ScorePropertiesItem/tst_scorepropertiesitemtest.cpp
        )

add_executable( ScorePropertiesItemTest ${GraphicsItemView_SOURCES}
    ${ScorePropertiesItem_TEST_SOURCES})
target_link_libraries( ScorePropertiesItemTest ${TEST_LIBRARIES} )
add_test( NAME ScorePropertiesItemTest COMMAND ScorePropertiesItemTest )

# AbstractScorePropertiesHolder
set( AbstractScorePropertiesHolder_TEST_SOURCES
        AbstractScorePropertiesHolder/tst_abstractscorepropertiesholdertest.cpp
        AbstractScorePropertiesHolder/scorepropertiesholderdummy.cpp
        )

add_executable( AbstractScorePropertiesHolderTest ${GraphicsItemView_SOURCES}
    ${AbstractScorePropertiesHolder_TEST_SOURCES})
target_link_libraries( AbstractScorePropertiesHolderTest ${TEST_LIBRARIES} )
add_test( NAME AbstractScorePropertiesHolderTest COMMAND AbstractScorePropertiesHolderTest )

# VisualMusicPresenter
set( VisualMusicPresenter_TEST_SOURCES
        VisualMusicPresenter/tst_visualmusicpresentertest.cpp
        VisualMusicPresenter/pageviewdummy.cpp
        )

add_executable( VisualMusicPresenterTest ${GraphicsItemView_SOURCES}
    ${VisualMusicPresenter_TEST_SOURCES})
target_link_libraries( VisualMusicPresenterTest ${TEST_LIBRARIES} )
add_test( NAME VisualMusicPresenterTest COMMAND VisualMusicPresenterTest )
