from tkinter import *
from Mainwindow import MainWindow 
from MQTT import MQTT
from Charging_spot import charging_spot

charging_spot1 = charging_spot()
charging_spot2 = charging_spot()

mqtt_client = MQTT(charging_spot1, charging_spot2)
mqtt_client.client.loop_start()

window = Tk()
my_gui = MainWindow(window, charging_spot1, charging_spot2)
window.mainloop()
