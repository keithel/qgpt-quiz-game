pragma ComponentBehavior: Bound

import QtQuick
import QtQuick.Layouts
import QtQuick.Controls.Material
import qgpt

Window {
    width: 640
    height: 480
    title: qsr("Qt GPT Interface")
    visible: true

    BusyIndicator {
        anchors.centerIn: parent
        running: ChatGptController.state == ChatGptController.GENERATING
        visible: running

        Label {
            text: "Generating Game..."

            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.bottom
        }
    }

    ListView {
        id: listView

        model: ChatGptController.questions
        spacing: 10

        delegate: Frame {
            id: frame

            required property var modelData

            Material.elevation: 10
            implicitWidth: listView.width

            ColumnLayout {
                anchors.fill: parent

                Label {
                    Layout.fillWidth: true
                    text: frame.modelData.question_description
                    wrapMode: Text.WordWrap
                }

                Repeater {
                    id: repeater

                    property var question: frame.modelData
                    model: question.answers

                    Button {
                        required property int index
                        required property string modelData

                        Layout.fillWidth: true
                        highlighted: repeater.question.reveal == true && repeater.question.right_answer == index

                        text: modelData

                        onClicked: {
                            let questionModified = repeater.question;
                            questionModified.reveal = true;
                            repeater.question = questionModified;
                        }
                    }
                }
            }
        }
    }
}
