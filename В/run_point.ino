
#include <ros.h>
#include <std_msgs/String.h>
#include <LiquidCrystal.h>

ros::NodeHandle nh;
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
//LiquidCrystal lcd(12, 11, 5, 4, 3, 2); // Пины ЖК дисплея
int cursorX = 8; // Начальные координаты X символа
int cursorY = 0; // Начальные координаты Y символа

String key;

void commandCallback(const std_msgs::String& command_msg) {
    key = command_msg.data;
}

ros::Subscriber<std_msgs::String> sub("/computer/lcd/cmd", &commandCallback);

void setup() {
    nh.initNode();
    nh.subscribe(sub);
    lcd.begin(16, 2); // Инициализация ЖК Дисплея
    lcd.setCursor(cursorX, cursorY);
    lcd.print("*");
}

void loop() {
//    if (key == "W") {
//        lcd.scrollDisplayRight();
//    } else if (key == "A") {
//        lcd.scrollDisplayRight();
//    } else if (key == "S") {
//        lcd.scrollDisplayLeft();
//    } else if (key == "D") {
//        lcd.scrollDisplayLeft();
//    }

    if (key == "W" && cursorY > 0) {
        cursorY--;
    } else if (key == "A" && cursorX > 0) {
        cursorX--;
    } else if (key == "S" && cursorY < 1) {
        cursorY++;
    } else if (key == "D" && cursorX < 15) {
        cursorX++;
    }

    lcd.clear();
    lcd.setCursor(cursorX, cursorY);
    lcd.print("*"); // Отображение символа

    key = ' '; // Сбрасываем команду

    nh.spinOnce();
    delay(100);



