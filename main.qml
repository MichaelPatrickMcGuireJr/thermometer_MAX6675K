import QtQuick 2.11
import QtQuick.Window 2.11
import QtQuick.Controls 1.6


Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Temp Sensor")

    property double x: 0;

    property double posY: 0;
    property double tempVal: 120;


    Rectangle {
        id: thermo
        x: 0
        y: 0
        width: 459
        height: 480
        color: "#ffffff"

        signal adjustIndicator()

        Image {
            id: image
            x: 177
            y: 4
            width: 319
            height: 477
            z: 50
            source: "thermometer/base.png"
            fillMode: Image.PreserveAspectFit

            TextEdit {
                id: the_temp
                x: 257
                y: 113
                width: 31
                height: 20
                text: '00'
                font.bold: true
                horizontalAlignment: Text.AlignHCenter
                font.pixelSize: 12
                z: 50
            }

            Rectangle {
                id: rectangle1
                x: 250
                y: 107
                width: 51
                height: 26
                color: "#ffffff"
                border.width: 2
                z: 40

                Text {
                    id: element
                    x: 53
                    y: -3
                    text: qsTr("F")
                    font.pixelSize: 18
                }
            }
        }

        Image {
            id: image1

            property alias tr: mover.y

            x: 304
            y: 119
            width: 66
            height: 362
            z: 40
            source: "thermometer/indicator.png"
            fillMode: Image.PreserveAspectFit
            transform: Translate {
                id: mover
                x: 0;
                y: posY;
            }
            smooth: true
        }

        Button {
            id: button
            x: 32
            y: 383
            text: qsTr("down")
            onClicked: thermo.adjustIndicator.connect(thermo.moveDOWN())
        }

        Button {
            id: button1
            x: 32
            y: 307
            text: qsTr("up")
            onClicked: thermo.adjustIndicator.connect(thermo.moveUP())
        }
/*
        Popup {
            id: popup
            x: 100
            y: 100
            width: 200
            height: 300
            modal: true
            focus: true
            closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutsideParent
        }
*/
        Button {
            id: button2
            x: 32
            y: 81
            text: qsTr("START")
            onClicked: thermo.adjustIndicator.connect(thermo.startTHREAD())
        }

            Button {
                id: button3
                x: 32
                y: 149
                text: qsTr("STOP")
                onClicked: thermo.adjustIndicator.connect(thermo.stopTHREAD())
            }


            Timer {
                    id: textTimer
                    interval: 1000
                    repeat: true
                    running: true
                    triggeredOnStart: true
                    onTriggered: thermo.adjustIndicator.connect(thermo.updateVAL())
                }


        function updateVAL() {
            if(vals.isRunning)
            {
                vals.test();
                //tempVal = vals.sensor_reading;
                //tempVal = 5;

                posY = ( 122-vals.read_sensor() ) / .72;

                the_temp.text= vals.read_sensor().toFixed(2).toString();
            }

        }


        function moveUP() {
                posY -= 1;
                tempVal += .65;

                //the_temp.text = qsTr( tempVal.toFixed().toString() );
                the_temp.text = qsTr( posY.toFixed().toString() );
            }

        function moveDOWN() {
                posY += 1;
                tempVal -= .65;

                //the_temp.text = qsTr( tempVal.toFixed().toString() );
                the_temp.text = qsTr( posY.toFixed().toString() );
            }

        function startTHREAD() {
                vals.isRunning = true;
                vals.startThread();
            }

        function stopTHREAD() {
                vals.isRunning = false;
                vals.stopThread();
            }
    }

}
