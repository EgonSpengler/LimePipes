# MusicItem
set( MusicItemTest_SOURCES
        MusicItem/tst_musicitemtest.cpp
        MusicItem/testmusicitem.cpp
        )
set( MusicItemTest_MOC_HEADERS
        MusicItem/tst_musicitemtest.h
        MusicItem/testmusicitem.h
        )
qt4_wrap_cpp( MusicItemTest_SOURCES ${MusicItemTest_MOC_HEADERS} )
add_executable( MusicItemTest ${MusicItemTest_SOURCES} )
target_link_libraries( MusicItemTest ${TEST_LIBRARIES} )
add_test( NAME MusicItemTest COMMAND MusicItemTest )

# MusicModel
set(TESTFILE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/MusicModel/test_files")
set(LIMEPIPES_XSD_FILE "${limepipes_SOURCE_DIR}/limepipes.xsd")
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/MusicModel/config.h.in
        ${CMAKE_CURRENT_BINARY_DIR}/config.h)

set( MusicModelTest_SOURCES
        MusicModel/tst_musicmodeltest.cpp
        MusicModel/qt_modeltest/modeltest.cpp
        )
set( MusicModelTest_MOC_HEADERS
        MusicModel/tst_musicmodeltest.h
        MusicModel/qt_modeltest/modeltest.h
        )
qt4_wrap_cpp( MusicModelTest_SOURCES ${MusicModelTest_MOC_HEADERS} )
add_executable( MusicModelTest ${MusicModelTest_SOURCES} )
target_link_libraries( MusicModelTest ${TEST_LIBRARIES} ${QT_QTXMLPATTERNS_LIBRARY} lp_musicmodeltestplugin )
add_test( NAME MusicModelTest COMMAND MusicModelTest )

# RootItem
set( RootItemTest_SOURCES RootItem/tst_rootitemtest.cpp )
qt4_automoc( ${RootItemTest_SOURCES} )
add_executable( RootItemTest ${RootItemTest_SOURCES} )
target_link_libraries( RootItemTest ${TEST_LIBRARIES} )
add_test( NAME RootItemTest COMMAND RootItemTest )

# Score
set( ScoreTest_SOURCES Score/tst_scoretest.cpp )
qt4_automoc( ${ScoreTest_SOURCES} )
add_executable( ScoreTest ${ScoreTest_SOURCES} )
target_link_libraries( ScoreTest ${TEST_LIBRARIES} )
add_test( NAME ScoreTest COMMAND ScoreTest )

# Part
set( PartTest_SOURCES Part/tst_parttest.cpp )
qt4_automoc( ${PartTest_SOURCES} )
add_executable( PartTest ${PartTest_SOURCES} )
target_link_libraries( PartTest ${TEST_LIBRARIES} )
add_test( NAME PartTest COMMAND PartTest )

# Measure
set( MeasureTest_SOURCES Measure/tst_measuretest.cpp )
qt4_automoc( ${MeasureTest_SOURCES} )
add_executable( MeasureTest ${MeasureTest_SOURCES} )
target_link_libraries( MeasureTest lp_greathighlandbagpipe ${TEST_LIBRARIES} )
add_test( NAME MeasureTest COMMAND MeasureTest )

# Symbol
set( SymbolTest_SOURCES Symbol/tst_symboltest.cpp )
qt4_automoc( ${SymbolTest_SOURCES} )
add_executable( SymbolTest ${SymbolTest_SOURCES} )
target_link_libraries( SymbolTest ${TEST_LIBRARIES} )
add_test( NAME SymbolTest COMMAND SymbolTest )

# SymbolGraphicBuilder
set( SymbolGraphicBuilderTest_SOURCES SymbolGraphicBuilder/tst_symbolgraphicbuildertest.cpp )
qt4_automoc( ${SymbolGraphicBuilderTest_SOURCES} )
add_executable( SymbolGraphicBuilderTest ${SymbolGraphicBuilderTest_SOURCES} )
target_link_libraries( SymbolGraphicBuilderTest ${TEST_LIBRARIES} )
add_test( NAME SymbolGraphicBuilderTest COMMAND SymbolGraphicBuilderTest )

# Tune
set( TuneTest_SOURCES Tune/tst_tunetest.cpp )
qt4_automoc( ${TuneTest_SOURCES} )
add_executable( TuneTest ${TuneTest_SOURCES} )
target_link_libraries( TuneTest lp_greathighlandbagpipe ${TEST_LIBRARIES} )
add_test( NAME TuneTest COMMAND TuneTest )

add_subdirectory( datatypes )
add_subdirectory( InstrumentManager )
add_subdirectory( musicfont )
add_subdirectory( symbols )
