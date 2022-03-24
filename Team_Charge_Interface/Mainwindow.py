from tkinter import *
from PIL import ImageTk, Image
import random
import time

class MainWindow():

    angle = 0
    show = False

    def __init__(self, main, chargingspot_1, chargingspot_2):
        self.spot1 = chargingspot_1
        self.spot2 = chargingspot_2

        self.main = main
        main.title("Welcome to the CHARGE interface!")
        main.geometry('800x480')
        #window.attributes("-fullscreen", True)
        main.bind("<Escape>", lambda event: main.attributes("-fullscreen", False))

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

        self.load_image = Image.open("Resources/present card.png")
        self.tk_present_card_image = ImageTk.PhotoImage(self.load_image)

        self.load_image = Image.open("Resources/kwh counter.png")
        self.tk_kwh_counter_image = ImageTk.PhotoImage(self.load_image)


        #Make frame to show the images in a canvas
        self.mainwindow_frame = Frame(main)
        self.mainwindow_frame.pack()

        #Canvas to put images in (To overlap images we need a canvas)
        self.mainwindow_canvas = Canvas(self.mainwindow_frame, width=800, height=480)
        self.mainwindow_canvas.pack()

        #x,y is middle point of image (800x480)/2:
        self.mainwindow_canvas.create_image(400,240,image=self.tk_background_image)

        #Pointers, hidden by default
        self.canvas_image_pointer_left = self.mainwindow_canvas.create_image(210,260,image=self.tk_pointer_image, state="hidden")
        self.canvas_image_pointer_right = self.mainwindow_canvas.create_image(597,260,image=self.tk_pointer_image, state="hidden")

        #Foreground, hidden by default
        self.canvas_image_foreground_left = self.mainwindow_canvas.create_image(210,270,image=self.tk_foreground_image, state="hidden")
        self.canvas_image_foreground_right = self.mainwindow_canvas.create_image(597,270,image=self.tk_foreground_image, state="hidden")

        #Warning lights, hidden by default
        self.canvas_image_red_light_left = self.mainwindow_canvas.create_image(269,313,image=self.tk_red_light_image, state="hidden")
        self.canvas_image_red_light_right = self.mainwindow_canvas.create_image(656,313,image=self.tk_red_light_image, state="hidden")

        self.canvas_image_orange_light_left = self.mainwindow_canvas.create_image(212,340,image=self.tk_orange_light_image, state="hidden")
        self.canvas_image_orange_light_right = self.mainwindow_canvas.create_image(599,340,image=self.tk_orange_light_image, state="hidden")

        self.canvas_image_green_light_left = self.mainwindow_canvas.create_image(152,313,image=self.tk_green_light_image, state="hidden")
        self.canvas_image_green_light_right = self.mainwindow_canvas.create_image(539,313,image=self.tk_green_light_image, state="hidden")

        #Global time and date
        self.canvas_text_global_time = self.mainwindow_canvas.create_text(400,70,text="Placeholder", font=("Helvetica",16, "bold"), fill = "white")
        self.canvas_text_global_date = self.mainwindow_canvas.create_text(400,91,text="Placeholder", font=("Helvetica",16), fill = "white")
        
        #Power info, hidden by default
        self.canvas_text_power_left = self.mainwindow_canvas.create_text(213,247, text = str(round((self.spot1.power/1000),1))+ " kW", font=("Helvetica",16, "bold"), fill= "white", state="hidden")
        self.canvas_text_power_right = self.mainwindow_canvas.create_text(600,247, text = str(round((self.spot2.power/1000),1))+ " kW", font=("Helvetica",16, "bold"), fill= "white", state="hidden")

        #Time info, hidden by default
        self.canvas_text_time_left = self.mainwindow_canvas.create_text(213,267, text = "Placeholder", font=("Helvetica",15), fill="white", state="hidden")
        self.canvas_text_time_right = self.mainwindow_canvas.create_text(600,267, text = "Placeholder", font=("Helvetica",15), fill="white", state="hidden")

        #Present card
        self.canvas_image_present_card_left = self.mainwindow_canvas.create_image(207,400, image=self.tk_present_card_image)
        self.canvas_image_present_card_right = self.mainwindow_canvas.create_image(594,400, image=self.tk_present_card_image)

        #Kwh counter, hidden by default
        self.canvas_image_kwh_counter_left = self.mainwindow_canvas.create_image(207,400, image=self.tk_kwh_counter_image, state="hidden")
        self.canvas_image_kwh_counter_right = self.mainwindow_canvas.create_image(594,400, image=self.tk_kwh_counter_image, state="hidden")

        #kwh text info, hidden by default
        self.canvas_text_kwh_left = self.mainwindow_canvas.create_text(176,400, text= "placeholder", font=("Helvetica",16, "bold"), fill= "white", state="hidden")
        self.canvas_text_kwh_right = self.mainwindow_canvas.create_text(565,400, text= "placeholder", font=("Helvetica",16, "bold"), fill= "white", state="hidden")

        #Activate frame drawer
        self.mainwindow_canvas.after(50,self.draw_frame)
        self.mainwindow_canvas.after(100, self.update_active_elements)

    def update_active_elements(self):
        if (self.spot1.is_active):
            self.mainwindow_canvas.itemconfig(self.canvas_image_pointer_left, state="normal")
            self.mainwindow_canvas.itemconfig(self.canvas_text_power_left, state="normal")
            self.mainwindow_canvas.itemconfig(self.canvas_image_foreground_left, state="normal")
            self.mainwindow_canvas.itemconfig(self.canvas_text_time_left, state="normal")
            self.mainwindow_canvas.itemconfig(self.canvas_image_present_card_left, state="hidden")
            self.mainwindow_canvas.itemconfig(self.canvas_image_kwh_counter_left, state="normal")
            self.mainwindow_canvas.itemconfig(self.canvas_text_kwh_left, state="normal")
            if( (int(time.time()) - self.spot1.start_time) > 14400):
                self.mainwindow_canvas.itemconfig(self.canvas_image_red_light_left, state="normal")
            elif(self.spot1.power > 1):
                self.mainwindow_canvas.itemconfig(self.canvas_image_green_light_left, state="normal")
            elif(self.spot1.power < 1):
                self.mainwindow_canvas.itemconfig(self.canvas_image_orange_light_left, state="normal")
        else:
            self.mainwindow_canvas.itemconfig(self.canvas_image_pointer_left, state="hidden")
            self.mainwindow_canvas.itemconfig(self.canvas_text_power_left, state="hidden")
            self.mainwindow_canvas.itemconfig(self.canvas_image_foreground_left, state="hidden")
            self.mainwindow_canvas.itemconfig(self.canvas_text_time_left, state="hidden")
            self.mainwindow_canvas.itemconfig(self.canvas_image_present_card_left, state="normal")
            self.mainwindow_canvas.itemconfig(self.canvas_image_kwh_counter_left, state="hidden")
            self.mainwindow_canvas.itemconfig(self.canvas_text_kwh_left, state="hidden")
            self.mainwindow_canvas.itemconfig(self.canvas_image_red_light_left, state="hidden")
            self.mainwindow_canvas.itemconfig(self.canvas_image_orange_light_left, state="hidden")
            self.mainwindow_canvas.itemconfig(self.canvas_image_green_light_left, state="hidden")


        if (self.spot2.is_active):
            self.mainwindow_canvas.itemconfig(self.canvas_image_pointer_right, state="normal")
            self.mainwindow_canvas.itemconfig(self.canvas_text_power_right, state="normal")
            self.mainwindow_canvas.itemconfig(self.canvas_image_foreground_right, state="normal")
            self.mainwindow_canvas.itemconfig(self.canvas_text_time_right, state="normal")
            self.mainwindow_canvas.itemconfig(self.canvas_image_present_card_right, state="hidden")
            self.mainwindow_canvas.itemconfig(self.canvas_image_kwh_counter_right, state="normal")
            self.mainwindow_canvas.itemconfig(self.canvas_text_kwh_right, state="normal")
            if( (int(time.time()) - self.spot2.start_time) > 14400):
                self.mainwindow_canvas.itemconfig(self.canvas_image_red_light_right, state="normal")
            elif(self.spot2.power > 1):
                self.mainwindow_canvas.itemconfig(self.canvas_image_green_light_right, state="normal")
            elif(self.spot2.power < 1):
                self.mainwindow_canvas.itemconfig(self.canvas_image_orange_light_right, state="normal")
        else:
            self.mainwindow_canvas.itemconfig(self.canvas_image_pointer_right, state="hidden")
            self.mainwindow_canvas.itemconfig(self.canvas_text_power_right, state="hidden")
            self.mainwindow_canvas.itemconfig(self.canvas_image_foreground_right, state="hidden")
            self.mainwindow_canvas.itemconfig(self.canvas_text_time_right, state="hidden")
            self.mainwindow_canvas.itemconfig(self.canvas_image_present_card_right, state="normal")
            self.mainwindow_canvas.itemconfig(self.canvas_image_kwh_counter_right, state="hidden")
            self.mainwindow_canvas.itemconfig(self.canvas_text_kwh_right, state="hidden")
            self.mainwindow_canvas.itemconfig(self.canvas_image_red_light_right, state="hidden")
            self.mainwindow_canvas.itemconfig(self.canvas_image_orange_light_right, state="hidden")
            self.mainwindow_canvas.itemconfig(self.canvas_image_green_light_right, state="hidden")


        self.mainwindow_canvas.after(500, self.update_active_elements)

    def draw_frame(self):
        #172 degrees pointer (+86 to -86)

        #global
        self.mainwindow_canvas.itemconfig(self.canvas_text_global_time, text = time.strftime("%H:%M", time.localtime(time.time())))
        self.mainwindow_canvas.itemconfig(self.canvas_text_global_date, text = time.strftime("%d-%m-%Y", time.localtime(time.time())))

        
        #Left spot (1)
        self.angle = 86 - ((self.spot1.power/12000) * 172) + random.randint(-1, 1)
        self.temp_rotate_image = self.pointer_image.rotate(self.angle, expand=True)
        self.rotated_pointer_image_left= ImageTk.PhotoImage(self.temp_rotate_image)
        self.mainwindow_canvas.itemconfig(self.canvas_image_pointer_left, image=self.rotated_pointer_image_left)
        self.mainwindow_canvas.itemconfig(self.canvas_text_power_left, text = str(round((self.spot1.power/1000),1)) + " kW")
        self.mainwindow_canvas.itemconfig(self.canvas_text_time_left, text = str(int((time.time() - self.spot1.start_time) / 3600)) + ":" + str(int(((time.time() - self.spot1.start_time) / 60)%60)) + ":" + str(int((time.time() - self.spot1.start_time) % 60)))
        self.mainwindow_canvas.itemconfig(self.canvas_text_kwh_left, text = str(int(self.spot1.kwh/100)) + "     " + str(int((self.spot1.kwh/10)%10)) + "     " + str(int(self.spot1.kwh%10)) + "     "  + str(int((self.spot1.kwh*10)%10)) + "     " + str(int((self.spot1.kwh*100)%10)))
        
                                          
        #Right spot (2)
        self.angle = 86 - ((self.spot2.power/12000) * 172) + random.randint(-1, 1)
        self.temp_rotate_image = self.pointer_image.rotate(self.angle, expand=True)
        self.rotated_pointer_image_right= ImageTk.PhotoImage(self.temp_rotate_image)
        self.mainwindow_canvas.itemconfig(self.canvas_image_pointer_right, image=self.rotated_pointer_image_right)
        self.mainwindow_canvas.itemconfig(self.canvas_text_power_right, text = str(round((self.spot2.power/1000),1)) + " kW")
        self.mainwindow_canvas.itemconfig(self.canvas_text_time_right, text = str(int((time.time() - self.spot2.start_time) / 3600)) + ":" + str(int(((time.time() - self.spot2.start_time) / 60)%60)) + ":" + str(int((time.time() - self.spot2.start_time) % 60)))
        self.mainwindow_canvas.itemconfig(self.canvas_text_kwh_right, text = str(int(self.spot2.kwh/100)) + "     " + str(int((self.spot2.kwh/10)%10)) + "     " + str(int(self.spot2.kwh%10)) + "     " + str(int((self.spot2.kwh*10)%10)) + "     " + str(int((self.spot2.kwh*100)%10)))

        self.mainwindow_canvas.after(500, self.draw_frame)
        



