set( PageViewItem_HEADERS
        ${CMAKE_SOURCE_DIR}/src/views/graphicsitemview/pageviewitem/pagecontentrowitem.h
        )
set( PageViewItem_SOURCES
        ${CMAKE_SOURCE_DIR}/src/views/graphicsitemview/pageviewitem/pageitem.cpp
        ${CMAKE_SOURCE_DIR}/src/views/graphicsitemview/pageviewitem/pagecontentrowitem.cpp
        ${CMAKE_SOURCE_DIR}/src/views/graphicsitemview/pageviewitem/pageviewitem.cpp
        )

# PageContentRowItem
set( PageContentRowItemTest_SOURCES
        pageviewitem/PageContentRowItem/tst_pagecontentrowitemtest.cpp
        )
set( PageContentRowItemTest_MOC_HEADERS
        ${CMAKE_SOURCE_DIR}/src/views/graphicsitemview/pageviewitem/pageitem.h
        ${CMAKE_SOURCE_DIR}/src/views/graphicsitemview/pageviewitem/pageviewitem.h
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
        ${CMAKE_SOURCE_DIR}/src/views/graphicsitemview/pageviewitem/pageitem.h
        ${CMAKE_SOURCE_DIR}/src/views/graphicsitemview/pageviewitem/pageviewitem.h
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
        ${CMAKE_SOURCE_DIR}/src/views/graphicsitemview/pageviewitem/pageitem.h
        ${CMAKE_SOURCE_DIR}/src/views/graphicsitemview/pageviewitem/pageviewitem.h
        pageviewitem/PageViewItem/tst_pageviewitemtest.h
        )
qt4_wrap_cpp( PageViewItemTest_SOURCES ${PageViewItemTest_MOC_HEADERS} )
add_executable( PageViewItemTest ${PageViewItemTest_SOURCES}
        ${PageViewItem_SOURCES}
        ${PageViewItem_HEADERS} )
target_link_libraries( PageViewItemTest ${TEST_LIBRARIES} )
add_test( NAME PageViewItemTest COMMAND PageViewItemTest )
