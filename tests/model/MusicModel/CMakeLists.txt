set( testname MusicModelTest )
set( testmodules Test Widgets XmlPatterns )
set( testlibraries lp_model lp_musicmodeltestplugin )

set(TESTFILE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/test_files")
set(LIMEPIPES_XSD_FILE "${limepipes_SOURCE_DIR}/limepipes.xsd")
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/config.h.in
        ${CMAKE_CURRENT_BINARY_DIR}/config.h)

find_package( Qt5Widgets REQUIRED )
find_package( Qt5Test    REQUIRED )

set( Test_SOURCES
        tst_musicmodeltest.cpp
        qt_modeltest/modeltest.cpp
        )

add_executable( ${testname} ${Test_SOURCES} )
qt5_use_modules( ${testname} ${testmodules} )
target_link_libraries( ${testname} ${testlibraries} )

add_test( NAME ${testname} COMMAND ${testname} )
