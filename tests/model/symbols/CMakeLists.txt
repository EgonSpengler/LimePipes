# MelodyNote
set( MelodyNoteTest_SOURCES MelodyNote/tst_melodynotetest.cpp )
qt4_automoc( ${MelodyNoteTest_SOURCES} )
add_executable( MelodyNoteTest ${MelodyNoteTest_SOURCES} )
target_link_libraries( MelodyNoteTest ${TEST_LIBRARIES} )
add_test( NAME MelodyNoteTest COMMAND MelodyNoteTest )
