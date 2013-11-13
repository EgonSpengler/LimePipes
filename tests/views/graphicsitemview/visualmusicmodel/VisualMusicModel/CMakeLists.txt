set( testname VisualMusicModelTest )
set( testmodules Test Widgets )
set( testlibraries lp_model lp_greathighlandbagpipe )

find_package( Qt5Widgets REQUIRED )
find_package( Qt5Test    REQUIRED )

set( Test_SOURCES
        ${VIEWS_SOURCE_DIR}/graphicsitemview/scorepropertiesitem.cpp
        ${VIEWS_SOURCE_DIR}/graphicsitemview/visualmusicmodel/visualmusicmodel.cpp
        ${VIEWS_SOURCE_DIR}/graphicsitemview/visualmusicmodel/abstractvisualitem.cpp
        ${VIEWS_SOURCE_DIR}/graphicsitemview/visualmusicmodel/visualrootitem.cpp
        ${VIEWS_SOURCE_DIR}/graphicsitemview/visualmusicmodel/visualscore.cpp
        ${VIEWS_SOURCE_DIR}/graphicsitemview/visualmusicmodel/visualtune.cpp
        ${VIEWS_SOURCE_DIR}/graphicsitemview/visualmusicmodel/visualpart.cpp
        ${VIEWS_SOURCE_DIR}/graphicsitemview/visualmusicmodel/visualmeasure.cpp
        ${VIEWS_SOURCE_DIR}/graphicsitemview/visualmusicmodel/visualsymbol.cpp
        tst_visualmusicmodeltest.cpp
        )

add_executable( ${testname} ${Test_SOURCES} )
qt5_use_modules( ${testname} ${testmodules} )
target_link_libraries( ${testname} ${testlibraries} )

add_test( NAME ${testname} COMMAND ${testname} )
