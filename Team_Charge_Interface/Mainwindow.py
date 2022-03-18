from tkinter import *
from PIL import ImageTk, Image
import random

class MainWindow():

    angle = 0
    show = False

    def __init__(self, main, chargingspot_1, chargingspot_2):
        self.spot1 = chargingspot_1
        self.spot2 = chargingspot_2

        self.main = main
        main.title("Welcome to the CHARGE interface!")
        main.geometry('800x480')
        #main.bind("<Escape>", lambda event: window.attributes("-fullscreen", False))
        main.bind("<space>", self.spacebar)

        #Load the images
        self.load_image = Image.open("Resources/background.png")
        self.tk_background_image = ImageTk.PhotoImage(self.load_image)

        self.load_image = Image.open("Resources/pointer.png")
        self.pointer_image = self.load_image.resize((12,220), Image.ANTIALIAS)
        self.pointer_image_rotated = self.pointer_image.rotate(87, expand=True)
        self.tk_pointer_image = ImageTk.PhotoImage(self.pointer_image_rotated)

        self.load_image = Image.open("Resources/foreground.png")
        self.tk_foreground_image = ImageTk.PhotoImage(self.load_image)

        self.load_image = Image.open("Resources/red_light.png")
        self.tk_red_light_image = ImageTk.PhotoImage(self.load_image)

        self.load_image = Image.open("Resources/orange_light.png")
        self.tk_orange_light_image = ImageTk.PhotoImage(self.load_image)

        self.load_image = Image.open("Resources/green_light.png")
        self.tk_green_light_image = ImageTk.PhotoImage(self.load_image)

        #Make frame to show the images in a canvas
        self.mainwindow_frame = Frame(main)
        self.mainwindow_frame.pack()

        #Canvas to put images in (To overlap images we need a canvas)
        self.mainwindow_canvas = Canvas(self.mainwindow_frame, width=800, height=480)
        self.mainwindow_canvas.pack()

        #x,y is middle point of image (800x480)/2:
        self.mainwindow_canvas.create_image(400,240,image=self.tk_background_image)

        self.canvas_image_pointer_left = self.mainwindow_canvas.create_image(210,260,image=self.tk_pointer_image)
        self.canvas_image_pointer_right = self.mainwindow_canvas.create_image(597,260,image=self.tk_pointer_image)

        self.mainwindow_canvas.create_image(210,270,image=self.tk_foreground_image)
        self.mainwindow_canvas.create_image(597,270,image=self.tk_foreground_image)

        self.canvas_image_red_light_left = self.mainwindow_canvas.create_image(269,313,image=self.tk_red_light_image)
        self.mainwindow_canvas.itemconfig(self.canvas_image_red_light_left, state="hidden")
        self.canvas_image_red_light_right = self.mainwindow_canvas.create_image(656,313,image=self.tk_red_light_image)
        self.mainwindow_canvas.itemconfig(self.canvas_image_red_light_right, state="hidden")


        self.canvas_image_orange_light_left = self.mainwindow_canvas.create_image(212,340,image=self.tk_orange_light_image)
        self.mainwindow_canvas.itemconfig(self.canvas_image_orange_light_left, state="hidden")
        self.canvas_image_orange_light_right = self.mainwindow_canvas.create_image(599,340,image=self.tk_orange_light_image)
        self.mainwindow_canvas.itemconfig(self.canvas_image_orange_light_right, state="hidden")

        self.canvas_image_green_light_left = self.mainwindow_canvas.create_image(152,313,image=self.tk_green_light_image)
        self.mainwindow_canvas.itemconfig(self.canvas_image_green_light_left, state="hidden")
        self.canvas_image_green_light_right = self.mainwindow_canvas.create_image(539,313,image=self.tk_green_light_image)
        self.mainwindow_canvas.itemconfig(self.canvas_image_green_light_right, state="hidden")

        #Activate pointer
        self.mainwindow_canvas.after(50,self.set_pointer)

    def set_pointer(self):
        #172 degrees pointer (+86 to -86) 
        self.angle = 86 - ((self.spot1.power/12000) * 172) + random.randint(-1, 1)
        self.temp_rotate_image = self.pointer_image.rotate(self.angle, expand=True)
        self.rotated_pointer_image_left= ImageTk.PhotoImage(self.temp_rotate_image)
        self.mainwindow_canvas.itemconfig(self.canvas_image_pointer_left, image=self.rotated_pointer_image_left)
 
        self.angle = 86 - ((self.spot2.power/12000) * 172) + random.randint(-1, 1)
        self.temp_rotate_image = self.pointer_image.rotate(self.angle, expand=True)
        self.rotated_pointer_image_right= ImageTk.PhotoImage(self.temp_rotate_image)
        self.mainwindow_canvas.itemconfig(self.canvas_image_pointer_right, image=self.rotated_pointer_image_right)

        self.mainwindow_canvas.after(500, self.set_pointer)
        


    def spacebar(self, e):
        self.toggle_red_light()

    def toggle_red_light(self):

        if self.show:
            self.mainwindow_canvas.itemconfig(self.canvas_image_red_light_right, state="hidden")
            self.mainwindow_canvas.itemconfig(self.canvas_image_red_light_left, state="hidden")
            self.mainwindow_canvas.itemconfig(self.canvas_image_orange_light_right, state="hidden")
            self.mainwindow_canvas.itemconfig(self.canvas_image_orange_light_left, state="hidden")
            self.mainwindow_canvas.itemconfig(self.canvas_image_green_light_right, state="hidden")
            self.mainwindow_canvas.itemconfig(self.canvas_image_green_light_left, state="hidden")
            self.show = False
            self.mainwindow_canvas.after(600, self.toggle_red_light)
        else:
            self.mainwindow_canvas.itemconfig(self.canvas_image_red_light_right, state="normal")
            self.mainwindow_canvas.itemconfig(self.canvas_image_red_light_left, state="normal")
            self.mainwindow_canvas.itemconfig(self.canvas_image_orange_light_right, state="normal")
            self.mainwindow_canvas.itemconfig(self.canvas_image_orange_light_left, state="normal")
            self.mainwindow_canvas.itemconfig(self.canvas_image_green_light_right, state="normal")
            self.mainwindow_canvas.itemconfig(self.canvas_image_green_light_left, state="normal")
            self.show = True
            self.mainwindow_canvas.after(600, self.toggle_red_light)


