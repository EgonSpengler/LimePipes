set( testname EmmentalerMusicFontTest )
set( testmodules Test Gui )
set( testlibraries )

find_package( Qt5Gui REQUIRED )
find_package( Qt5Test    REQUIRED )

set( Test_SOURCES
        ${MODEL_SOURCE_DIR}/musicfont/musicfont.cpp
        ${MODEL_SOURCE_DIR}/musicfont/emmentalermusicfont.cpp
        tst_emmentalermusicfonttest.cpp
        )

set( Test_RESOURCES
        ${MODEL_SOURCE_DIR}/musicfont/musicfont_resources.qrc
        )
qt5_add_resources( Test_SOURCES ${Test_RESOURCES} )

add_executable( ${testname} ${Test_SOURCES} )
qt5_use_modules( ${testname} ${testmodules} )
target_link_libraries( ${testname} ${testlibraries} )

add_test( NAME ${testname} COMMAND ${testname} )
