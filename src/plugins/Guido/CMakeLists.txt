project( GuidoPlugin )

find_package( Qt5Core REQUIRED )
find_package( Qt5Gui REQUIRED )

set( sources
  guidotextformatplugin.cpp
)

add_library( ${PROJECT_NAME} STATIC
 ${sources}
)

qt5_use_modules( ${PROJECT_NAME} Core Gui )
