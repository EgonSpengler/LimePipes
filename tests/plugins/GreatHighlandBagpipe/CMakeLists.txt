# GHB Doubling
set( GHBDoublingTest_SOURCES GHB_Doubling/tst_ghb_doublingtest.cpp )
qt4_automoc( ${GHBDoublingTest_SOURCES} )
add_executable( GHBDoublingTest ${GHBDoublingTest_SOURCES} )
target_link_libraries( GHBDoublingTest lp_greathighlandbagpipe ${TEST_LIBRARIES} )
add_test( NAME GHBDoublingTest COMMAND GHBDoublingTest )

# GHB MelodyNote
set( GHBMelodyNoteTest_SOURCES GHB_MelodyNote/tst_ghb_melodynotetest.cpp )
qt4_automoc( ${GHBMelodyNoteTest_SOURCES} )
add_executable( GHBMelodyNoteTest ${GHBMelodyNoteTest_SOURCES} )
target_link_libraries( GHBMelodyNoteTest lp_greathighlandbagpipe ${TEST_LIBRARIES} )
add_test( NAME GHBMelodyNoteTest COMMAND GHBMelodyNoteTest )

# GHB Plugin
set( GHBPluginTest_SOURCES GHB_Plugin/tst_ghb_plugintest.cpp )
qt4_automoc( ${GHBPluginTest_SOURCES} )
add_executable( GHBPluginTest ${GHBPluginTest_SOURCES} )
target_link_libraries( GHBPluginTest lp_greathighlandbagpipe ${TEST_LIBRARIES} )
add_test( NAME GHBPluginTest COMMAND GHBPluginTest )
