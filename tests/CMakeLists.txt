#set( TEST_LIBRARIES lp_model ${QT_QTTEST_LIBRARY} ${QT_LIBRARIES} )

include_directories(
        ${PROJECT_BINARY_DIR}
        ${CMAKE_SOURCE_DIR}
        ${CMAKE_CURRENT_BINARY_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${limepipes_SOURCE_DIR}
        "${limepipes_SOURCE_DIR}/src"
        "${limepipes_SOURCE_DIR}/src/model"
        "${limepipes_SOURCE_DIR}/src/interfaces"
        "${limepipes_SOURCE_DIR}/src/views"
        "${limepipes_SOURCE_DIR}/src/app"
        )

#add_subdirectory( app )
#add_subdirectory( model )
#add_subdirectory( plugins )
#add_subdirectory( views )

# MusicModelTestPlugin
add_definitions( -DQT_STATICPLUGIN )
set( LIBRARY_OUTPUT_PATH ${STATIC_PLUGINS_FOLDER} )
set( MusicModelTestplugin_SOURCES
        MusicModelTestPlugin/musicmodeltestplugin.cpp
        MusicModelTestPlugin/testinstrument.cpp
        )

find_package( Qt5Widgets REQUIRED )
add_library( lp_musicmodeltestplugin STATIC ${MusicModelTestplugin_SOURCES} )
qt5_use_modules( lp_musicmodeltestplugin Widgets )


