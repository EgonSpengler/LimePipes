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

# GraphicsItemView
set( GraphicsItemViewTest_SOURCES
        ${CMAKE_SOURCE_DIR}/src/views/graphicsitemview/graphicsitemview.cpp
        ${CMAKE_SOURCE_DIR}/src/views/graphicsitemview/graphicsscene.cpp
        ${CMAKE_SOURCE_DIR}/src/views/graphicsitemview/graphicsview.cpp
        ${CMAKE_SOURCE_DIR}/src/views/graphicsitemview/visualmusicmodel/visualmusicmodel.cpp
        GraphicsItemView/tst_graphicsitemviewtest.cpp
        )
set( GraphicsItemViewTest_MOC_HEADERS
        ${CMAKE_SOURCE_DIR}/src/views/graphicsitemview/graphicsitemview.h
        ${CMAKE_SOURCE_DIR}/src/views/graphicsitemview/graphicsscene.h
        ${CMAKE_SOURCE_DIR}/src/views/graphicsitemview/graphicsview.h
        GraphicsItemView/tst_graphicsitemviewtest.h
        GraphicsItemView/visualmusicmodeldummy.h
        )
qt4_wrap_cpp( GraphicsItemViewTest_SOURCES ${GraphicsItemViewTest_MOC_HEADERS} )
add_executable( GraphicsItemViewTest ${GraphicsItemViewTest_SOURCES}
        ${PageViewItem_SOURCES}
        ${PageViewItem_HEADERS} )
target_link_libraries( GraphicsItemViewTest ${TEST_LIBRARIES} lp_greathighlandbagpipe )
add_test( NAME GraphicsItemViewTest COMMAND GraphicsItemViewTest )

# VisualMusicModel
set( VisualMusicModelTest_SOURCES
        ${CMAKE_SOURCE_DIR}/src/views/graphicsitemview/graphicsscene.cpp
        ${CMAKE_SOURCE_DIR}/src/views/graphicsitemview/pageviewitem/pageitem.cpp
        ${CMAKE_SOURCE_DIR}/src/views/graphicsitemview/pageviewitem/pageviewitem.cpp
        ${CMAKE_SOURCE_DIR}/src/views/graphicsitemview/visualmusicmodel/visualmusicmodel.cpp
        visualmusicmodel/VisualMusicModel/tst_visualmusicmodel.cpp
        )
set( VisualMusicModelTest_MOC_HEADERS
        ${CMAKE_SOURCE_DIR}/src/views/graphicsitemview/graphicsscene.h
        ${CMAKE_SOURCE_DIR}/src/views/graphicsitemview/pageviewitem/pageitem.h
        ${CMAKE_SOURCE_DIR}/src/views/graphicsitemview/pageviewitem/pageviewitem.h
        visualmusicmodel/VisualMusicModel/tst_visualmusicmodel.h
        )
qt4_wrap_cpp( VisualMusicModelTest_SOURCES ${VisualMusicModelTest_MOC_HEADERS} )
add_executable( VisualMusicModelTest ${VisualMusicModelTest_SOURCES}
    ${VisualMusicModelTest_SOURCES})
target_link_libraries( VisualMusicModelTest ${TEST_LIBRARIES} )
add_test( NAME VisualMusicModelTest COMMAND VisualMusicModelTest )

set(CMAKE_AUTOMOC ON)

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
