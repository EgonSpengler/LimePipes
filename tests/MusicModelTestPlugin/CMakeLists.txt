add_definitions( -DQT_STATICPLUGIN )
set( MusicModelTestplugin_SOURCES
        musicmodeltestplugin.cpp
        testinstrument.cpp
        )

find_package( Qt5Widgets REQUIRED )
add_library( lp_musicmodeltestplugin STATIC ${MusicModelTestplugin_SOURCES} )
qt5_use_modules( lp_musicmodeltestplugin Gui )
