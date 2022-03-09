# coding=utf-8
from tkinter import *
from tkinter import ttk
import paho.mqtt.client as mqtt #import the client1
from PIL import ImageTk, Image
import os
import json

class charging_spot:
    def __init__(self):
        self.is_active = False
        self.V1 = 0
        self.V2 = 0
        self.V3 = 0
        self.I1 = 0
        self.I2 = 0
        self.I3 = 0
        self.F = 0
        self.UserID = ""
        self.is_three_phase = False
        self.start_time = 0
        self.end_time = 0
        self.total_time = 0

    def update_measurements(self, variables):
        self.V1 = variables["V1"]
        self.V2 = variables["V2"]
        self.V3 = variables["V3"]
        self.I1 = variables["I1"]
        self.I2 = variables["I2"]
        self.I3 = variables["I3"]
        self.F  = variables["F"]
        self.UserID = variables["UserID"]

        if (self.I1 > 1) & (self.I2 > 1) & (self.I3 > 1):
            self.is_three_phase = True
        else:
            self.is_three_phase = False

        if (self.is_active == False) & ((self.I1 > 1) | (self.I2 > 1) | (self.I3 > 1)):
            self.is_active = True
            self.start_time = variables["Time"]
        elif (self.is_active == True) & ((self.I1 > 1) | (self.I2 > 1) | (self.I3 > 1)):
            self.total_time = variables["Time"] - self.start_time
        elif (self.is_active == True) & ((self.I1 < 1) | (self.I2 < 1) | (self.I3 < 1)):
            self.is_active = False
            self.end_time = variables["Time"] - self.start_time
        print(self.total_time)



#Set attributes for the main window
window = Tk()
window.geometry('800x480')
window.title("Welcome to the CHARGE interface!")
#window.attributes("-fullscreen", True)
window.bind("<Escape>", lambda event: window.attributes("-fullscreen", False))


#Set image as main window
image = Image.open("Tests/blauwzwart.png")
img = image.resize((800,480))
blauwzwart = ImageTk.PhotoImage(img)
panel1 = Label(window, image = blauwzwart)
panel1.place(x=0, y=0, relwidth=1, relheight=1)


#Make frame for data overlay
data_frame = Frame(window, relief='raised', borderwidth=2)
data_frame.place(x=515, y=270, anchor=W)
I3_data = Label(data_frame, text = "I3", font = ("Helvetica",14), fg = "white", bg = "black")
I3_data.pack()

    

# This is the event handler method that receives the Mosquito messages
def on_message(client, userdata, message):
    msg = str(message.payload.decode("utf-8"))
    variables = json.loads(msg)
    try:
        if variables["SocketID"] == 1:
            charging_spot1.update_measurements(variables)

        elif variables["SocketID"] == 2:
            charging_spot2.update_measurements(variables)
    except:
        print("Not a data message")
            



print("creating new instance")
client = mqtt.Client() #create new instance
client.on_message=on_message #attach function to callback

print("connecting to broker")
client.connect("broker.hivemq.com") #connect to broker

print("Subscribing to topic","hanevse/#")
client.subscribe("HANevse/#")

charging_spot1 = charging_spot()
charging_spot2 = charging_spot()


#Start the MQTT Mosquito process loop
client.loop_start() 

window.mainloop()