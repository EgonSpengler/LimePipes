set( testname MusicFontTest )
set( testmodules Test Gui )
set( testlibraries )

find_package( Qt5Gui REQUIRED )
find_package( Qt5Test    REQUIRED )

set( Test_SOURCES
        ${MODEL_SOURCE_DIR}/musicfont/musicfont.cpp
        tst_musicfonttest.cpp
        )

add_executable( ${testname} ${Test_SOURCES} )
qt5_use_modules( ${testname} ${testmodules} )
target_link_libraries( ${testname} ${testlibraries} )

add_test( NAME ${testname} COMMAND ${testname} )
