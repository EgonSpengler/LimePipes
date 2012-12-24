# MusicFont
set( MusicFontTest_SOURCES MusicFont/tst_musicfonttest.cpp )
qt4_automoc( ${MusicFontTest_SOURCES} )
add_executable( MusicFontTest ${MusicFontTest_SOURCES} )
target_link_libraries( MusicFontTest ${TEST_LIBRARIES} )
add_test( NAME MusicFontTest COMMAND MusicFontTest )

# Emmentaler MusicFont
set( EmmentalerMusicFontTest_SOURCES EmmentalerMusicFont/tst_emmentalermusicfonttest.cpp )
qt4_automoc( ${EmmentalerMusicFontTest_SOURCES} )

set( EmmentalerMusicFontTest_RESOURCES
        ${CMAKE_SOURCE_DIR}/src/model/musicfont/musicfont_resources.qrc
        )
qt4_add_resources(EmmentalerMusicFontTest_SOURCES ${EmmentalerMusicFontTest_RESOURCES})

add_executable( EmmentalerMusicFontTest ${EmmentalerMusicFontTest_SOURCES} )
target_link_libraries( EmmentalerMusicFontTest ${TEST_LIBRARIES} )
add_test( NAME EmmentalerMusicFontTest COMMAND EmmentalerMusicFontTest )
