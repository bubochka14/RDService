import QtCore
import QtQuick
import QtQuick.Layouts
import QtQuick.Window
import QtQuick.Controls

ApplicationWindow {
    id: root
    visible: true
    width: 640
    height: 480
    background: Rectangle {
        color: "grey"
    }
    menuBar: MenuBar {
        id: menuBar
        Menu {
            id: serversMenu
            title: qsTr("&Servers")
            Action {
                id: userInputAction
                text: qsTr("&User input")
            }
        }
    }
    ListView {
        width: 200
        model: sessModel
        height: 200

        delegate: Rectangle {
            height: 50
            width: parent.width
            Text {
                id: textInfo
                text: id + " " + st + " " + userName + " " + server
            }
            Button {
                id: shadowBt
                signal shadowClicked(int sess, string host)
                onClicked: shadowClicked(id, server)
                anchors.right: parent.right
                text: "shadow"
            }
            Button {
                id: messageBt
                signal messageClicked(int sess, string host)
                onClicked: messageClicked(id, server)
                anchors.right: shadowBt.left
                text: "message"
            }
            Button {
                id: disconnectBt
                signal disconnectClicked(int sess, string host)
                onClicked: disconnectClicked(id, server)
                anchors.right: messageBt.left
                text: "disconect"
            }
        }
    }
}
