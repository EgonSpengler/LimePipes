# Instrument
set( InstrumentTest_SOURCES Instrument/tst_instrumenttest.cpp )
qt4_automoc( ${InstrumentTest_SOURCES} )
add_executable( InstrumentTest ${InstrumentTest_SOURCES} )
target_link_libraries( InstrumentTest ${TEST_LIBRARIES} )
add_test( NAME InstrumentTest COMMAND InstrumentTest )

# Length
set( LengthTest_SOURCES Length/tst_lengthtest.cpp )
qt4_automoc( ${LengthTest_SOURCES} )
add_executable( LengthTest ${LengthTest_SOURCES} )
target_link_libraries( LengthTest ${TEST_LIBRARIES} )
add_test( NAME LengthTest COMMAND LengthTest )

# Pitch
set( PitchTest_SOURCES Pitch/tst_pitchtest.cpp )
qt4_automoc( ${PitchTest_SOURCES} )
add_executable( PitchTest ${PitchTest_SOURCES} )
target_link_libraries( PitchTest ${TEST_LIBRARIES} )
add_test( NAME PitchTest COMMAND PitchTest )

# PitchContext
set( PitchContextTest_SOURCES PitchContext/tst_pitchcontexttest.cpp )
qt4_automoc( ${PitchContextTest_SOURCES} )
add_executable( PitchContextTest ${PitchContextTest_SOURCES} )
target_link_libraries( PitchContextTest ${TEST_LIBRARIES} )
add_test( NAME PitchContextTest COMMAND PitchContextTest )

# SymbolGraphic
set( SymbolGraphicTest_SOURCES SymbolGraphic/tst_symbolgraphictest.cpp )
qt4_automoc( ${SymbolGraphicTest_SOURCES} )
add_executable( SymbolGraphicTest ${SymbolGraphicTest_SOURCES} )
target_link_libraries( SymbolGraphicTest ${TEST_LIBRARIES} )
add_test( NAME SymbolGraphicTest COMMAND SymbolGraphicTest )

# TimeSignature
set( TimeSignatureTest_SOURCES TimeSignature/tst_timesignaturetest.cpp )
qt4_automoc( ${TimeSignatureTest_SOURCES} )
add_executable( TimeSignatureTest ${TimeSignatureTest_SOURCES} )
target_link_libraries( TimeSignatureTest ${TEST_LIBRARIES} )
add_test( NAME TimeSignatureTest COMMAND TimeSignatureTest )
