cmake_minimum_required( VERSION 2.8.11 )
project( LimePipes CXX )

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11 -stdlib=libc++")
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=gnu++0x")
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Intel")
  # using Intel C++
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
  # using Visual Studio C++
endif()

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_LIST_DIR}/cmake)

include_directories(
  ${CMAKE_CURRENT_LIST_DIR}/include/GuidoEngine
  ${CMAKE_CURRENT_LIST_DIR}/include/GuidoQt
  ${CMAKE_CURRENT_LIST_DIR}/src/plugins
  ${CMAKE_CURRENT_LIST_DIR}/src/include
)

find_library(GuidoEngine_libraries GUIDOEngine
  PATHS ${CMAKE_CURRENT_LIST_DIR}/bin/lib/GuidoEngine/linux_64
  NO_SYSTEM_ENVIRONMENT_PATH )

find_library(GuidoQt_libraries GuidoQt
  PATHS ${CMAKE_CURRENT_LIST_DIR}/bin/lib/GuidoQt/linux_64
  NO_SYSTEM_ENVIRONMENT_PATH )

add_subdirectory( src/app )
add_subdirectory( src/plugins )
