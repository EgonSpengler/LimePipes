set( testname PitchTest )
set( testmodules Test Core )
set( testlibraries )

find_package( Qt5Core REQUIRED )
find_package( Qt5Test    REQUIRED )

set( Test_SOURCES
        ${DATATYPES_SOURCE_DIR}/pitch.cpp
        tst_pitchtest.cpp
        )

add_executable( ${testname} ${Test_SOURCES} )
qt5_use_modules( ${testname} ${testmodules} )
target_link_libraries( ${testname} ${testlibraries} )

add_test( NAME ${testname} COMMAND ${testname} )
