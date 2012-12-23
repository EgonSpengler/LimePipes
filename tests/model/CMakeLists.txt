SET( TEST_LIBRARIES lp_model ${QT_QTTEST_LIBRARY} ${QT_LIBRARIES} )

SET( RootItemTests_SOURCES RootItem/tst_rootitemtest.cpp )
QT4_AUTOMOC( ${RootItemTests_SOURCES} )
ADD_EXECUTABLE( RootItemTest ${RootItemTests_SOURCES} )
TARGET_LINK_LIBRARIES( RootItemTest ${TEST_LIBRARIES} )
ADD_TEST( NAME RootItemTest COMMAND RootItemTest )

