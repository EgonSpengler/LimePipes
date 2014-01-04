set( testname ScorePropertiesSettingsPageTest )
set( testmodules Test Widgets )
set( testlibraries )

find_package( Qt5Widgets REQUIRED )
find_package( Qt5Test    REQUIRED )

set( Test_SOURCES
        tst_scorepropertiessettingspagetest.cpp
        ${CMAKE_SOURCE_DIR}/src/app/dialogs/settingspages/scorepropertiessettingspage.cpp
        ${CMAKE_SOURCE_DIR}/src/app/dialogs/settingspages/scorepropertieswidget.cpp
        ${CMAKE_SOURCE_DIR}/src/common/scoresettings.cpp
        ${CMAKE_SOURCE_DIR}/src/common/observablesettings.cpp
        ${CMAKE_SOURCE_DIR}/src/common/settingsobserver.cpp
        )

set( Test_UIs
        ${CMAKE_SOURCE_DIR}/src/app/dialogs/settingspages/scorepropertiessettingspage.ui
        ${CMAKE_SOURCE_DIR}/src/app/dialogs/settingspages/scorepropertieswidget.ui
        )

qt5_wrap_ui( Test_SOURCES ${Test_UIs} )

add_executable( ${testname} ${Test_SOURCES} )
qt5_use_modules( ${testname} ${testmodules} )

target_link_libraries( ${testname} ${testlibraries} )
add_test( NAME ${testname} COMMAND ${testname} )
