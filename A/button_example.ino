#include <ros.h>
#include <std_msgs/Bool.h>
#include <std_msgs/String.h>

ros::NodeHandle nh;

std_msgs::String pushed_msg;
ros::Publisher pub_button("/arduino/led", &pushed_msg);

const int button_pin = 2;
const int led_pin = 8;

bool last_reading;
long last_debounce_time=0;
long debounce_delay=50;
bool published = true;

void setup()
{
  nh.initNode();
  nh.advertise(pub_button);

  pinMode(led_pin, OUTPUT);
  pinMode(button_pin, INPUT);
  
  digitalWrite(button_pin, HIGH);
  
  last_reading = ! digitalRead(button_pin);
 
}

void loop()
{
  
  bool reading = ! digitalRead(button_pin);
  
  if (last_reading!= reading){
      last_debounce_time = millis();
      published = false;
  }
 
  if ( !published && (millis() - last_debounce_time)  > debounce_delay) {
    digitalWrite(led_pin, reading);
  if (reading){
    pushed_msg.data = "Led:ON";
    pub_button.publish(&pushed_msg);
  }
  else {
    pushed_msg.data = "Led:OFF";
    pub_button.publish(&pushed_msg);
  }
    published = true;
  }

  last_reading = reading;
  
  nh.spinOnce();
}
