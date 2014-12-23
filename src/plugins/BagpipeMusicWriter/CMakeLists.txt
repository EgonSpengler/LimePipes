project( BagpipeMusicWriterPlugin )

find_package( Qt5Core REQUIRED )
find_package( Qt5Gui REQUIRED )

find_package(BISON)
find_package(FLEX)

bison_target(BwwParser ${CMAKE_CURRENT_LIST_DIR}/parser/parser.y
                       ${CMAKE_CURRENT_BINARY_DIR}/parser.cpp)
flex_target(BwwScanner ${CMAKE_CURRENT_LIST_DIR}/parser/lexer.l
                       ${CMAKE_CURRENT_BINARY_DIR}/lexer.cpp)
add_flex_bison_dependency(BwwScanner BwwParser)

set( sources
  bagpipemusicwriterformatplugin.cpp
  parser/parser.y
  parser/lexer.l
  parser/BwwAstFactory.cpp
  parser/GuidoCodeVisitor.cpp
  parser/EmbellishmentRules.cpp
  parser/EmbellishmentRule.cpp
  parser/PitchRange.cpp

  parser/ast/AstDefines.cpp
  parser/ast/musicitem.cpp
  parser/ast/score.cpp
  parser/ast/tune.cpp
  parser/ast/part.cpp
  parser/ast/symbol.cpp
  parser/ast/melodynote.cpp
  parser/ast/timesignature.cpp
  parser/ast/embellishment.cpp
  parser/ast/AstVisitorInterface.h
)

qt5_add_resources( sources
  parser/embellishment_rules/embellishment_rules_resources.qrc
)

add_library( ${PROJECT_NAME} STATIC
 ${sources}
 ${BISON_BwwParser_OUTPUTS}
 ${FLEX_BwwScanner_OUTPUTS}
)

qt5_use_modules( ${PROJECT_NAME} Core Gui )
