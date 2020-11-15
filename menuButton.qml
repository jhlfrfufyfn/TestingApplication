import QtQuick 2.0
import QtQuick.Controls 2.0

Button {
    width: 200
    height: 90
    Rectangle {
        id: rectangle
        color: "#49aee4"
        radius: 30
        anchors.fill: parent

        Text {
            id: element
            text: qsTr("Button")
            anchors.fill: parent
            wrapMode: Text.NoWrap
            verticalAlignment: Text.AlignVCenter
            font.family: "Verdana"
            fontSizeMode: Text.Fit
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 39
        }
    }

}

/*##^##
Designer {
    D{i:1;anchors_height:200;anchors_width:200;anchors_x:88;anchors_y:"-184"}
}
##^##*/
