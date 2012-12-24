set( TEST_LIBRARIES lp_model ${QT_QTTEST_LIBRARY} ${QT_LIBRARIES} )

include_directories(
        ${CMAKE_SOURCE_DIR}
        ${CMAKE_CURRENT_BINARY_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${QT_QTCORE_INCLUDE_DIR}
        ${QT_QTGUI_INCLUDE_DIR}
        ${limepipes_SOURCE_DIR}
        "${limepipes_SOURCE_DIR}/src"
        "${limepipes_SOURCE_DIR}/src/model"
        "${limepipes_SOURCE_DIR}/src/interfaces"
        "${limepipes_SOURCE_DIR}/src/views"
        "${limepipes_SOURCE_DIR}/src/app"
        )

add_subdirectory( app )
add_subdirectory( model )
add_subdirectory( plugins )
add_subdirectory( views )

# MusicModelTestPlugin
add_definitions( -DQT_STATICPLUGIN )
set( LIBRARY_OUTPUT_PATH ${STATIC_PLUGINS_FOLDER} )
set( MusicModelTestplugin_SOURCES
        MusicModelTestPlugin/musicmodeltestplugin.cpp
        MusicModelTestPlugin/testinstrument.cpp
        )
set( MusicModelTestplugin_MOC_HEADERS
        MusicModelTestPlugin/musicmodeltestplugin.h
        )
qt4_wrap_cpp( MusicModelTestplugin_SOURCES ${MusicModelTestplugin_MOC_HEADERS})
add_library( lp_musicmodeltestplugin STATIC ${MusicModelTestplugin_SOURCES} )
target_link_libraries( lp_musicmodeltestplugin ${QT_LIBRARIES} )


