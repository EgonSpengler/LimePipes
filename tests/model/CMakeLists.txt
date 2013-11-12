
# MusicModel
#set(TESTFILE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/MusicModel/test_files")
#set(LIMEPIPES_XSD_FILE "${limepipes_SOURCE_DIR}/limepipes.xsd")
#configure_file(${CMAKE_CURRENT_SOURCE_DIR}/MusicModel/config.h.in
#        ${CMAKE_CURRENT_BINARY_DIR}/config.h)

#set( MusicModelTest_SOURCES
#        MusicModel/tst_musicmodeltest.cpp
#        MusicModel/qt_modeltest/modeltest.cpp
#        )
#set( MusicModelTest_MOC_HEADERS
#        MusicModel/tst_musicmodeltest.h
#        MusicModel/qt_modeltest/modeltest.h
#        )
#qt4_wrap_cpp( MusicModelTest_SOURCES ${MusicModelTest_MOC_HEADERS} )
#add_executable( MusicModelTest ${MusicModelTest_SOURCES} )
#target_link_libraries( MusicModelTest ${TEST_LIBRARIES} ${QT_QTXMLPATTERNS_LIBRARY} lp_musicmodeltestplugin )
#add_test( NAME MusicModelTest COMMAND MusicModelTest )

# SymbolGraphicBuilder
#set( SymbolGraphicBuilderTest_SOURCES SymbolGraphicBuilder/tst_symbolgraphicbuildertest.cpp )
#qt4_automoc( ${SymbolGraphicBuilderTest_SOURCES} )
#add_executable( SymbolGraphicBuilderTest ${SymbolGraphicBuilderTest_SOURCES} )
#target_link_libraries( SymbolGraphicBuilderTest ${TEST_LIBRARIES} )
#add_test( NAME SymbolGraphicBuilderTest COMMAND SymbolGraphicBuilderTest )

add_subdirectory( RootItem )
add_subdirectory( Score )
add_subdirectory( Tune )
add_subdirectory( Part )
add_subdirectory( Measure )
add_subdirectory( Symbol )
add_subdirectory( MusicItem )

#add_subdirectory( datatypes )
#add_subdirectory( InstrumentManager )
#add_subdirectory( musicfont )
#add_subdirectory( symbols )
