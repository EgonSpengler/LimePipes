set( MODEL_SOURCE_DIR ${CMAKE_SOURCE_DIR}/src/model )
set( DATATYPES_SOURCE_DIR ${CMAKE_SOURCE_DIR}/src/model/datatypes )

include_directories(
        ${DATATYPES_SOURCE_DIR}
        ${MODEL_SOURCE_DIR}
)

add_subdirectory( MusicModelTestPlugin )

add_subdirectory( app )
add_subdirectory( model )
#add_subdirectory( plugins )
#add_subdirectory( views )
