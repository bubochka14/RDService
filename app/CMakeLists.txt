find_package(Qt6 REQUIRED COMPONENTS Core Gui Qml Quick Widgets)
set(APP_NAME ${PROJECT_NAME})

qt_add_executable(${APP_NAME}
	main.cpp
	rdsessionmodel.cpp
	rdsessionmodel.h
	rdserver.h 
	interfaces.h
	rdserver.cpp
	app.qrc
	qml/qml.qrc
)

target_link_libraries(${APP_NAME} PRIVATE 
	Qt::Core
	Qt::Gui 
	Qt::Qml 
	Qt::Quick
	qml_module
)
target_include_directories(${APP_NAME}
	PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}
	PRIVATE
	${CMAKE_CURRENT_BINARY_DIR}
)
get_target_property(_qmake_executable Qt6::qmake IMPORTED_LOCATION)
get_filename_component(_qt_bin_dir "${_qmake_executable}" DIRECTORY)
find_program(WINDEPLOYQT_EXECUTABLE windeployqt HINTS "${_qt_bin_dir}")
find_program(MACDEPLOYQT_EXECUTABLE macdeployqt HINTS "${_qt_bin_dir}")
add_custom_command(TARGET ${APP_NAME} POST_BUILD
        COMMAND "${CMAKE_COMMAND}" -E
        env PATH="${_qt_bin_dir}" "${WINDEPLOYQT_EXECUTABLE}"
        "$<TARGET_FILE:${APP_NAME}>"
        COMMENT "Running windeployqt...")
set(APP_SOURCE ${CMAKE_CURRENT_BINARY_DIR} CACHE INTERNAL "Path to app source")

add_subdirectory(qml)