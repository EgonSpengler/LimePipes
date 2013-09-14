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


file(GLOB_RECURSE GraphicsItemView_SOURCES "${CMAKE_SOURCE_DIR}/src/views/graphicsitemview/*.cpp")
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
file(GLOB_RECURSE AbstractVisualItem_SOURCES ${CMAKE_SOURCE_DIR}/src/views/graphicsitemview/*.cpp)
set( AbstractVisualItem_TEST_SOURCES
        visualmusicmodel/AbstractVisualItem/tst_abstractvisualitemtest.cpp
        visualmusicmodel/AbstractVisualItem/testabstractvisualitem.cpp
        )

add_executable( AbstractVisualItemTest ${AbstractVisualItem_SOURCES}
    ${AbstractVisualItem_TEST_SOURCES})
target_link_libraries( AbstractVisualItemTest ${TEST_LIBRARIES} )
add_test( NAME AbstractVisualItemTest COMMAND AbstractVisualItemTest )

# VisualRootItem
file(GLOB_RECURSE VisualRootItem_SOURCES ${CMAKE_SOURCE_DIR}/src/views/graphicsitemview/*.cpp)
set( VisualRootItem_TEST_SOURCES
        visualmusicmodel/VisualRootItem/tst_visualrootitemtest.cpp
        )

add_executable( VisualRootItemTest ${VisualRootItem_SOURCES}
    ${VisualRootItem_TEST_SOURCES})
target_link_libraries( VisualRootItemTest ${TEST_LIBRARIES} )
add_test( NAME VisualRootItemTest COMMAND VisualRootItemTest )

# VisualScoreTest
file(GLOB_RECURSE VisualScore_SOURCES ${CMAKE_SOURCE_DIR}/src/views/graphicsitemview/*.cpp)
set( VisualScore_TEST_SOURCES
        visualmusicmodel/VisualScore/tst_visualscoretest.cpp
        )

add_executable( VisualScoreTest ${VisualScore_SOURCES}
    ${VisualScore_TEST_SOURCES})
target_link_libraries( VisualScoreTest ${TEST_LIBRARIES} )
add_test( NAME VisualScoreTest COMMAND VisualScoreTest )

# VisualTuneTest
file(GLOB_RECURSE VisualTune_SOURCES ${CMAKE_SOURCE_DIR}/src/views/graphicsitemview/*.cpp)
set( VisualTune_TEST_SOURCES
        visualmusicmodel/VisualTune/tst_visualtunetest.cpp
        )

add_executable( VisualTuneTest ${VisualTune_SOURCES}
    ${VisualTune_TEST_SOURCES})
target_link_libraries( VisualTuneTest ${TEST_LIBRARIES} )
add_test( NAME VisualTuneTest COMMAND VisualTuneTest )

# VisualPartTest
file(GLOB_RECURSE VisualPart_SOURCES ${CMAKE_SOURCE_DIR}/src/views/graphicsitemview/*.cpp)
set( VisualPart_TEST_SOURCES
        visualmusicmodel/VisualPart/tst_visualparttest.cpp
        )

add_executable( VisualPartTest ${VisualPart_SOURCES}
    ${VisualPart_TEST_SOURCES})
target_link_libraries( VisualPartTest ${TEST_LIBRARIES} )
add_test( NAME VisualPartTest COMMAND VisualPartTest )

# VisualMeasureTest
file(GLOB_RECURSE VisualMeasure_SOURCES ${CMAKE_SOURCE_DIR}/src/views/graphicsitemview/*.cpp)
set( VisualMeasure_TEST_SOURCES
        visualmusicmodel/VisualMeasure/tst_visualmeasuretest.cpp
        )

add_executable( VisualMeasureTest ${VisualMeasure_SOURCES}
    ${VisualMeasure_TEST_SOURCES})
target_link_libraries( VisualMeasureTest ${TEST_LIBRARIES} )
add_test( NAME VisualMeasureTest COMMAND VisualMeasureTest )

# VisualSymbolTest
file(GLOB_RECURSE VisualSymbol_SOURCES ${CMAKE_SOURCE_DIR}/src/views/graphicsitemview/*.cpp)
set( VisualSymbol_TEST_SOURCES
        visualmusicmodel/VisualSymbol/tst_visualsymboltest.cpp
        )

add_executable( VisualSymbolTest ${VisualSymbol_SOURCES}
    ${VisualSymbol_TEST_SOURCES})
target_link_libraries( VisualSymbolTest ${TEST_LIBRARIES} )
add_test( NAME VisualSymbolTest COMMAND VisualSymbolTest )

# InteractingGraphicsItem
file(GLOB_RECURSE VisualSymbol_SOURCES ${CMAKE_SOURCE_DIR}/src/views/graphicsitemview/*.cpp)
set( InteractingGraphicsItem_TEST_SOURCES
        interactinggraphicsitem/InteractingGraphicsItem/tst_interactinggraphicsitemtest.cpp
        interactinggraphicsitem/InteractingGraphicsItem/visualitemdummy.cpp
        )

add_executable( InteractingGraphicsItemTest ${VisualSymbol_SOURCES}
    ${InteractingGraphicsItem_TEST_SOURCES})
target_link_libraries( InteractingGraphicsItemTest ${TEST_LIBRARIES} )
add_test( NAME InteractingGraphicsItemTest COMMAND InteractingGraphicsItemTest )
