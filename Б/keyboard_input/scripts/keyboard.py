import rospy
from std_msgs.msg import String
import getch  # Модуль для чтения клавиш

def keyboard_publisher():
    pub = rospy.Publisher('/computer/traffic_light/cmd', String, queue_size=10)
    rospy.init_node('keyboard_publisher', anonymous=True)
    
    rate = rospy.Rate(10)  # Публикация сообщений со скоростью 10 Гц
    
    while not rospy.is_shutdown():
        key = getch.getch()  # Получаем нажатую клавишу
        key_str = str(key)
        rospy.loginfo("Published: %s" % key_str)
        pub.publish(key_str)
        rate.sleep()

if __name__ == '__main__':
    try:
        keyboard_publisher()
    except rospy.ROSInterruptException:
        pass