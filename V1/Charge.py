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

angle = 0
show = False

def toggle_red_light():
    global my_canvas
    global red_light_object
    global show

    if show:
        my_canvas.itemconfig(red_light_object, state="hidden")
        show = False
        my_canvas.after(600, toggle_red_light)
    else:
        my_canvas.itemconfig(red_light_object, state="normal")
        show = True
        my_canvas.after(600, toggle_red_light)

def spacebar(e):
    toggle_red_light()


def keyleft(e):
    global angle
    global image_pointer_object_left
    global image_pointer_object_right
    global my_canvas
    global img
    global pointerimg

    angle += 1
    testimg = img.rotate(angle, expand=True)
    pointerimg = ImageTk.PhotoImage(testimg)
    my_canvas.itemconfig(image_pointer_object_left, image=pointerimg)
    #my_canvas.itemconfig(image_pointer_object_right, image=pointerimg)


def keyright(e):
    global angle
    global image_pointer_object_left
    global image_pointer_object_right
    global my_canvas
    global img
    global pointerimg

    angle -= 1
    testimg = img.rotate(angle, expand=True)
    pointerimg = ImageTk.PhotoImage(testimg)
    my_canvas.itemconfig(image_pointer_object_left, image=pointerimg)
    #my_canvas.itemconfig(image_pointer_object_right, image=pointerimg)

#Set attributes for the main window
window = Tk()
window.geometry('800x480')
window.title("Welcome to the CHARGE interface!")
#window.attributes("-fullscreen", True)
window.bind("<Escape>", lambda event: window.attributes("-fullscreen", False))
window.bind("<Left>", keyleft)
window.bind("<Right>", keyright)
window.bind("<space>", spacebar)


#Load the images
image = Image.open("V1/Resources/background.png")
background = ImageTk.PhotoImage(image)

image = Image.open("V1/Resources/pointer.png")
img = image.resize((12,220), Image.ANTIALIAS)

img2 = img.rotate(0, expand=True)
pointer = ImageTk.PhotoImage(img2)

image = Image.open("V1/Resources/foreground.png")
foreground = ImageTk.PhotoImage(image)

image = Image.open("V1/Resources/red_light.png")
red_light = ImageTk.PhotoImage(image)

image = Image.open("V1/Resources/orange_light.png")
orange_light = ImageTk.PhotoImage(image)

image = Image.open("V1/Resources/green_light.png")
green_light = ImageTk.PhotoImage(image)

#Make frame to show the images in a canvas
pointer_frame = Frame(window)
pointer_frame.pack()

#Canvas to put images in (To overlap images we need a canvas)
my_canvas = Canvas(pointer_frame, width=800, height=480)
my_canvas.pack()

#x,y is middle point of image (800x480)/2:
my_canvas.create_image(400,240,image=background)
image_pointer_object_left = my_canvas.create_image(210,260,image=pointer)
#image_pointer_object_right = my_canvas.create_image(597,260,image=pointer)

my_canvas.create_image(210,270,image=foreground)
#my_canvas.create_image(597,270,image=foreground)

red_light_object = my_canvas.create_image(269,313,image=red_light)
my_canvas.itemconfig(red_light_object, state="hidden")



#panel1 = Label(window, image = background)
#panel1.place(x=0, y=0, relwidth=1, relheight=1)

#Make frame for pointer 

#pointer_frame.place(x=100, y=100, anchor=W)
#image2 = Image.open("Tests/wijzer.png")
#img2 = image2.resize((100,100))



#pointer_canvas = Canvas(pointer_frame, width=100, height=100)
#pointer_canvas.pack()

#pointer_canvas.create_image(0, 0, image=pointer)

#pointer_canvas.place(x=5,y=5, relwidth=1, relheight=1)
#pointer_label = Label(pointer_frame, image = pointer)
#pointer_label.pack()


#Make frame for data overlay
data_frame = Frame(window, relief='raised', borderwidth=2)
data_frame.place(x=515, y=270, anchor=W)
I3_data = Label(data_frame, text = "I3", font = ("Helvetica",14), fg = "white", bg = "black")
#I3_data.pack()

    

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