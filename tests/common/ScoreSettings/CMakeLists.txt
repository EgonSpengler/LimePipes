set( testname ScoreSettingsTest )
set( testmodules Test Widgets )
set( testlibraries )

find_package( Qt5Widgets REQUIRED )
find_package( Qt5Test    REQUIRED )

set( Test_SOURCES
        tst_scoresettingstest.cpp
        ../common/testsettingsobserver.cpp
        ${CMAKE_SOURCE_DIR}/src/common/scoresettings.cpp
        ${CMAKE_SOURCE_DIR}/src/common/observablesettings.cpp
        ${CMAKE_SOURCE_DIR}/src/common/settingsobserver.cpp
        )

include_directories(
    ../common
)

add_executable( ${testname} ${Test_SOURCES} )
qt5_use_modules( ${testname} ${testmodules} )
target_link_libraries( ${testname} ${testlibraries} )

add_test( NAME ${testname} COMMAND ${testname} )
