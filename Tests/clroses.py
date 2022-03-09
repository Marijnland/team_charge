from tkinter import *
import paho.mqtt.client as mqtt #import the client1
from PIL import ImageTk, Image
import os
import json

########## Progress bar

bar = ttk.Progressbar(window, 
    orient='horizontal',
    mode='determinate',
    length=280)

bar.grid(column=0, row=0, columnspan=2, padx=10, pady=20)

def mycal():
     bar['value'] += 10

start_button = ttk.Button(
    window,
    text='Start',
    command=mycal
)

#bar['value'] = 50

start_button.grid(column=0, row=1, padx=10, pady=10, sticky=E)
 
###############

############### PNG support

#test frame for png support
png_frame = Frame(window, relief='raised', borderwidth=2)
png_frame.place(x=400, y=270, anchor=W)


image2 = Image.open("Tests/dice.png")
img2 = image2.resize((500,500))
dice = ImageTk.PhotoImage(img2)
panel3 = Label(png_frame, image = dice)
panel3.grid(row=0, column=2, sticky=E)
#panel3.place(x=0, y=0, relwidth=1, relheight=1)

#######################



def my_callback():
    my_callback.is_on = True
    if my_callback.is_on:
        print("ok")
        panel1.configure(image = img_off)
        panel1.update()
        my_callback.is_on = False
    else:
        panel1.configure(image = img_on)
        panel1.update()
        my_callback.is_on = True

window = Tk()
window.geometry('800x480')
window.title("Welcome to LikeGeeks app")

#Load both the images
on = Image.open("Tests/on.jpg")
off = Image.open("Tests/off.jpg")

temp1 = on.resize((600,450))
temp2 = off.resize((600,450))


img_on = ImageTk.PhotoImage(temp1)
img_off = ImageTk.PhotoImage(temp2)


#img_on = ImageTk.PhotoImage(Image.open("Tests/on.jpg"))
#img_off = ImageTk.PhotoImage(Image.open("Tests/off.jpg"))

image = Image.open("Tests/blauwzwart.png")
img = image.resize((800,480))
blauwzwart = ImageTk.PhotoImage(img)

panel1 = Label(window, image = img_on)
panel1.place(x=0, y=0)

button = Button(window, text="ON/OFF", command = my_callback)
button.place(x=700, y=450)



#panel1.pack(side = "top", expand = "no")

#center_frame = Frame(window, relief='raised', borderwidth=2)
#center_frame.place(x=515, y=270, anchor=W)

#panel2 = Label(center_frame, text = "I3", font = ("Helvetica",14), fg = "white", bg = "black")
#panel2.pack()



# This is the event handler method that receives the Mosquito messages
def on_message(client, userdata, message):
    msg = str(message.payload.decode("utf-8"))
    print("message received " , msg)
    variables = json.loads(msg)
    try:
        if variables["SocketID"] == 1:
            #panel2.configure(text = variables["I3"])
            #panel2.update()
            print("Good message")
    except:
        print("Unknown message")
            

    #If the received message is light on then set the image the the ‘light on’ image
    if msg == "Study/HUE_STATE/on":
        panel1.configure(image=img_on)
        print("****ON")
        panel1.update()
    #If the received message is light off then set the image the the ‘light off’ image
    elif msg == "Study/HUE_STATE/off":
        panel1.configure(image=img_off)
        print("****OFF")         
        panel1.update()

broker_address="broker.hivemq.com"

print("creating new instance")
client = mqtt.Client() #create new instance
client.on_message=on_message #attach function to callback

print("connecting to broker")
client.connect(broker_address) #connect to broker

print("Subscribing to topic","hanevse")
client.subscribe("HANevse/#")

 #Start the MQTT Mosquito process loop
client.loop_start() 





window.mainloop()