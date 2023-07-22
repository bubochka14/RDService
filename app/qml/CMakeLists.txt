file(REAL_PATH "../qml" QML_PATH BASE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
list(APPEND QML_IMPORT_PATHS "${QML_PATH}")
#qt_add_qml_module(
#	qml_module
#	VERSION 1.0
#	URI "app.qml.qml_module"
##	QML_FILES MainWindow.qml
