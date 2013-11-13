set( EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR}/bin )
set( LIBRARY_OUTPUT_PATH    ${CMAKE_CURRENT_BINARY_DIR}/bin/plugins )

add_subdirectory( InstrumentManager )
add_subdirectory( TestInstrumentForManager )
add_subdirectory( TestInstrumentGHB )

