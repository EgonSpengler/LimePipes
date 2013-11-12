set( testname NewTuneDialogTest )
set( testmodules Test Widgets )
#set( testlibraries )

find_package( Qt5Widgets REQUIRED )
find_package( Qt5Test    REQUIRED )

set( Test_SOURCES
        tst_newtunedialogtest.cpp
        ${CMAKE_SOURCE_DIR}/src/app/newtunedialog.cpp
        )

set( Test_UIs
        ${CMAKE_SOURCE_DIR}/src/app/newtunedialog.ui
        )

qt5_wrap_ui( Test_SOURCES ${Test_UIs} )

add_executable( ${testname} ${Test_SOURCES} )
qt5_use_modules( ${testname} ${testmodules} )

target_link_libraries( ${testname} ${testlibraries} )
add_test( NAME ${testname} COMMAND ${testname} )

