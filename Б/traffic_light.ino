#include <ros.h>
#include <std_msgs/String.h>

ros::NodeHandle nh;

String key;
bool newCommand = false;

void commandCallback(const std_msgs::String& command_msg) {
    key = command_msg.data;
    newCommand = true;
}

ros::Subscriber<std_msgs::String> sub("/computer/traffic_light/cmd", &commandCallback);

void setup() {
    nh.initNode();
    nh.subscribe(sub);

    pinMode(11, OUTPUT);  // Красный светодиод
    pinMode(13, OUTPUT); // Зеленый светодиод
    pinMode(12, OUTPUT); // Синий светодиод
}

void loop() {
    if (newCommand) {
        newCommand = false;

        if (key == "R") {
            digitalWrite(11, HIGH);  // Включить красный
            digitalWrite(13, LOW);   // Выключить зеленый
            digitalWrite(12, LOW);   // Выключить синий
        } else if (key == "G") {
            digitalWrite(11, LOW);
            digitalWrite(13, HIGH);
            digitalWrite(12, LOW);
        } else if (key == "B") {
            digitalWrite(11, LOW);
            digitalWrite(13, LOW);
            digitalWrite(12, HIGH);
        }
    }

    nh.spinOnce();
    delay(10);
}
