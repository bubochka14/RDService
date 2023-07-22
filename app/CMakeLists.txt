find_package(Qt6 REQUIRED COMPONENTS Core Gui Qml Quick Sql)
set(APP_NAME ${PROJECT_NAME})
set(HEADERS 
	sessionsqlmodel.h 
	session.h 	
	errorlogic.h 	
	interfaces.h
)
set(APP_SOURCES
	main.cpp
	sessionsqlmodel.cpp
	session.cpp
	errorlogic.cpp 	
	qml/qml.qrc
)
QT_ADD_EXECUTABLE(${APP_NAME} ${APP_SOURCES})
target_precompile_headers(${APP_NAME} PUBLIC ${HEADERS})
target_link_libraries(${APP_NAME} PRIVATE 
	Qt::Core
	Qt::Gui 
	Qt::Qml 
	Qt::Sql
	Qt::Quick
	
)
target_include_directories(${APP_NAME}
	PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}
	PRIVATE
	${CMAKE_CURRENT_BINARY_DIR}
)

set(APP_LIB_SOURCES ${APP_SOURCES})
list(REMOVE_ITEM APP_LIB_SOURCES main.cpp)
#lib for tests
QT_ADD_LIBRARY(APP_LIB STATIC ${APP_LIB_SOURCES})
target_precompile_headers(APP_LIB REUSE_FROM ${APP_NAME})
target_link_libraries(APP_LIB PUBLIC 
	Qt::Core
	Qt::Gui 
	Qt::Qml 
	Qt::Sql
	Qt::Quick
	
)

set(APP_SOURCE ${CMAKE_CURRENT_SOURCE_DIR} CACHE INTERNAL "Path to app source")

add_subdirectory(qml)
