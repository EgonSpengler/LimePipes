# LenghtDelegate
set( LengthDelegateTest_SOURCES
        LengthDelegate/tst_lengthdelegatetest.cpp
        ${CMAKE_SOURCE_DIR}/src/views/treeview/lengthdelegate.cpp
        ${CMAKE_SOURCE_DIR}/src/views/treeview/musicsymboldatadelegate.cpp
        )
set( LengthDelegateTest_MOC_HEADERS
        LengthDelegate/tst_lengthdelegatetest.h
        ${CMAKE_SOURCE_DIR}/src/views/treeview/lengthdelegate.h
        ${CMAKE_SOURCE_DIR}/src/views/treeview/musicsymboldatadelegate.h
        )
qt4_wrap_cpp( LengthDelegateTest_SOURCES ${LengthDelegateTest_MOC_HEADERS} )
add_executable( LengthDelegateTest ${LengthDelegateTest_SOURCES} )
target_link_libraries( LengthDelegateTest ${TEST_LIBRARIES} lp_musicmodeltestplugin )
add_test( NAME LengthDelegateTest COMMAND LengthDelegateTest )

# PitchDelegate
set( PitchDelegateTest_SOURCES
        PitchDelegate/tst_pitchdelegatetest.cpp
        ${CMAKE_SOURCE_DIR}/src/views/treeview/pitchdelegate.cpp
        ${CMAKE_SOURCE_DIR}/src/views/treeview/musicsymboldatadelegate.cpp
        )
set( PitchDelegateTest_MOC_HEADERS
        PitchDelegate/tst_pitchdelegatetest.h
        ${CMAKE_SOURCE_DIR}/src/views/treeview/pitchdelegate.h
        ${CMAKE_SOURCE_DIR}/src/views/treeview/musicsymboldatadelegate.h
        )
qt4_wrap_cpp( PitchDelegateTest_SOURCES ${PitchDelegateTest_MOC_HEADERS} )
add_executable( PitchDelegateTest ${PitchDelegateTest_SOURCES} )
target_link_libraries( PitchDelegateTest ${TEST_LIBRARIES} lp_musicmodeltestplugin )
add_test( NAME PitchDelegateTest COMMAND PitchDelegateTest )

# MusicProxyModel
set( MusicProxyModelTest_SOURCES
        MusicProxyModel/tst_musicproxymodeltest.cpp
        ${CMAKE_SOURCE_DIR}/src/views/treeview/musicproxymodel.cpp
        )
set( MusicProxyModelTest_MOC_HEADERS
        MusicProxyModel/tst_musicproxymodeltest.h
        ${CMAKE_SOURCE_DIR}/src/views/treeview/musicproxymodel.h
        )
qt4_wrap_cpp( MusicProxyModelTest_SOURCES ${MusicProxyModelTest_MOC_HEADERS} )
add_executable( MusicProxyModelTest ${MusicProxyModelTest_SOURCES} )
target_link_libraries( MusicProxyModelTest ${TEST_LIBRARIES} lp_musicmodeltestplugin )
add_test( NAME MusicProxyModelTest COMMAND MusicProxyModelTest )

# TreeView
set( TreeViewTest_SOURCES
        TreeView/tst_treeviewtest.cpp
        ${CMAKE_SOURCE_DIR}/src/views/treeview/treeview.cpp
        ${CMAKE_SOURCE_DIR}/src/views/treeview/pitchdelegate.cpp
        ${CMAKE_SOURCE_DIR}/src/views/treeview/lengthdelegate.cpp
        ${CMAKE_SOURCE_DIR}/src/views/treeview/musicsymboldatadelegate.cpp
        )
set( TreeViewTest_MOC_HEADERS
        TreeView/tst_treeviewtest.h
        ${CMAKE_SOURCE_DIR}/src/views/treeview/treeview.h
        ${CMAKE_SOURCE_DIR}/src/views/treeview/pitchdelegate.h
        ${CMAKE_SOURCE_DIR}/src/views/treeview/lengthdelegate.h
        ${CMAKE_SOURCE_DIR}/src/views/treeview/musicsymboldatadelegate.h
        )
qt4_wrap_cpp( TreeViewTest_SOURCES ${TreeViewTest_MOC_HEADERS} )
add_executable( TreeViewTest ${TreeViewTest_SOURCES} )
target_link_libraries( TreeViewTest ${TEST_LIBRARIES} )
add_test( NAME TreeViewTest COMMAND TreeViewTest )
