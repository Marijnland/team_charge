from tkinter import *
from PIL import ImageTk, Image

class MainWindow():

    angle = 0
    show = False

    def __init__(self, main):
        self.main = main
        main.title("Welcome to the CHARGE interface!")
        main.geometry('800x480')
        #main.bind("<Escape>", lambda event: window.attributes("-fullscreen", False))
        main.bind("<Left>", self.keyleft)
        main.bind("<Right>", self.keyright)
        main.bind("<space>", self.spacebar)

        #Load the images
        self.load_image = Image.open("V1/Resources/background.png")
        self.tk_background_image = ImageTk.PhotoImage(self.load_image)

        self.load_image = Image.open("V1/Resources/pointer.png")
        self.pointer_image = self.load_image.resize((12,220), Image.ANTIALIAS)
        self.pointer_image_rotated = self.pointer_image.rotate(0, expand=True)
        self.tk_pointer_image = ImageTk.PhotoImage(self.pointer_image_rotated)

        self.load_image = Image.open("V1/Resources/foreground.png")
        self.tk_foreground_image = ImageTk.PhotoImage(self.load_image)

        self.load_image = Image.open("V1/Resources/red_light.png")
        self.tk_red_light_image = ImageTk.PhotoImage(self.load_image)

        self.load_image = Image.open("V1/Resources/orange_light.png")
        self.tk_orange_light_image = ImageTk.PhotoImage(self.load_image)

        self.load_image = Image.open("V1/Resources/green_light.png")
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
        #self.canvas_image_pointer_right = self.mainwindow_canvas.create_image(597,260,image=self.tk_pointer_image)

        self.mainwindow_canvas.create_image(210,270,image=self.tk_foreground_image)
        #self.mainwindow_canvas.create_image(597,270,image=self.tk_foreground_image)

        self.canvas_image_red_light = self.mainwindow_canvas.create_image(269,313,image=self.tk_red_light_image)
        self.mainwindow_canvas.itemconfig(self.canvas_image_red_light, state="hidden")

        self.canvas_image_orange_light = self.mainwindow_canvas.create_image(265,313,image=self.tk_orange_light_image)
        self.mainwindow_canvas.itemconfig(self.canvas_image_orange_light, state="hidden")

        self.canvas_image_green_light = self.mainwindow_canvas.create_image(260,313,image=self.tk_green_light_image)
        self.mainwindow_canvas.itemconfig(self.canvas_image_green_light, state="hidden")

    def toggle_red_light(self):
        #global my_canvas
        #global red_light_object
        #global show

        if self.show:
            self.mainwindow_canvas.itemconfig(self.canvas_image_red_light, state="hidden")
            self.show = False
            self.mainwindow_canvas.after(600, self.toggle_red_light)
        else:
            self.mainwindow_canvas.itemconfig(self.canvas_image_red_light, state="normal")
            self.show = True
            self.mainwindow_canvas.after(600, self.toggle_red_light)

    def spacebar(self, e):
        self.toggle_red_light()

    def keyleft(self, e):
        #global angle
        #global image_pointer_object_left
        #global image_pointer_object_right
        #global my_canvas
        #global img
        #global pointerimg

        self.angle += 1
        self.temp_rotate_image = self.pointer_image.rotate(self.angle, expand=True)
        self.rotated_pointer_image= ImageTk.PhotoImage(self.temp_rotate_image)
        self.mainwindow_canvas.itemconfig(self.canvas_image_pointer_left, image=self.rotated_pointer_image)
        #self.mainwindow_canvas.itemconfig(self.canvas_image_pointer_right, image=self.rotated_pointer_image)


    def keyright(self, e):
        #global angle
        #global image_pointer_object_left
        #global image_pointer_object_right
        #global my_canvas
        #global img
        #global pointerimg

        self.angle -= 1
        self.temp_rotate_image = self.pointer_image.rotate(self.angle, expand=True)
        self.rotated_pointer_image= ImageTk.PhotoImage(self.temp_rotate_image)
        self.mainwindow_canvas.itemconfig(self.canvas_image_pointer_left, image=self.rotated_pointer_image)
        #self.mainwindow_canvas.itemconfig(self.canvas_image_pointer_right, image=self.rotated_pointer_image)

