set( MODEL_SOURCE_DIR ${CMAKE_SOURCE_DIR}/src/model )
set( COMMON_SOURCE_DIR ${CMAKE_SOURCE_DIR}/src/common )
set( DATATYPES_SOURCE_DIR ${CMAKE_SOURCE_DIR}/src/common/datatypes )
set( PLUGINS_SOURCE_DIR ${CMAKE_SOURCE_DIR}/src/plugins )
set( VIEWS_SOURCE_DIR ${CMAKE_SOURCE_DIR}/src/views )
set( TEST_MOCK_DIR ${CMAKE_CURRENT_LIST_DIR}/testmocks )

include_directories(
        ${DATATYPES_SOURCE_DIR}
        ${MODEL_SOURCE_DIR}
        ${PLUGINS_SOURCE_DIR}
        ${VIEWS_SOURCE_DIR}
        ${TEST_MOCK_DIR}
)

add_subdirectory( MusicModelTestPlugin )

add_subdirectory( common )
add_subdirectory( app )
add_subdirectory( model )
add_subdirectory( plugins )
add_subdirectory( views )
