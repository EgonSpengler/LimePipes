project( LimePipes )

find_package(Qt5Widgets REQUIRED)
find_package(Qt5PrintSupport REQUIRED)

set( sources
  main.cpp
  mainwindow.cpp
  guidowidget.cpp
  application.cpp
  texteditheaderwidget.cpp
  settings.cpp

  # Add interface classes for visibility in Creator
  ../include/iapplication.h
  ../include/itextformatplugin.h
)

set( uis
  mainwindow.ui
  texteditheaderwidget.ui
)

qt5_wrap_ui( sources ${uis} )

add_executable( ${PROJECT_NAME}
  ${sources}
)

target_link_libraries(${PROJECT_NAME}
  ${GuidoQt_libraries}
  ${GuidoEngine_libraries}
  BagpipeMusicWriterPlugin
  GuidoPlugin
)

qt5_use_modules( ${PROJECT_NAME} Widgets PrintSupport)
