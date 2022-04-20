import paho.mqtt.client as mqtt #import the client
import json
import re

class MQTT():
    def __init__(self, charging_spot1, charging_spot2):
        self.spot1 = charging_spot1
        self.spot2 = charging_spot2
        self.client = mqtt.Client()
        self.client.on_message = self.on_message
        self.client.connect("broker.hivemq.com")
        self.client.subscribe("HANevse/#")
        print("Connected to MQTT")
        self.client.on_disconnect = self.client.reconnect

    def on_message(self, client, userdata, message):
        self.msg = str(message.payload.decode("utf-8"))
        print(self.msg)     
         
        if (message.topic == "HANevse/photonMeasure"):
            self.variables = json.loads(self.msg)

            if self.variables["SocketID"] == 1:
                self.spot1.update_measurements(self.variables)

            elif self.variables["SocketID"] == 2:
                self.spot2.update_measurements(self.variables)
        
        elif (message.topic == "HANevse/allowUser"):
            #retrieve ints from the string
            self.array =re.findall(r'\d+', self.msg)
            #//action=1  succesfull start new charge (charger is free and last stoped session > 20 sec ago)
            #//action=4  succesful stop this charge session
            #Not validated:
            #//action=2  charger is free, but you allready swiped the card in the last 20 sec (second swipe within 20sec)
            #//action=3  charger is occupied by annother user
            #//action=5  you just started a charge on this charger, but have another consecutive RFID read/swipe within 20 seconds
            #//action=6  you are already charging at another charger
            #//action=7  succesfull RFID read, but you are not in the userlist

 
            if (self.array[1] == '1'):
                if (self.array[0] == '1'):
                    self.spot1.start_charge()
                elif (self.array[0] == '2'):
                    self.spot2.start_charge()

            elif (self.array[1] == '4'):
                if (self.array[0] == '1'):
                    self.spot1.stop_charge()
                elif (self.array[0] == '2'):
                    self.spot2.stop_charge()

            elif (self.array[1] == '3'):
                if (self.array[0] == '1'):
                    self.spot1.message = 3
                    self.spot1.sub_message = "Charger is occupied \nby another user"
                elif (self.array[0] == '2'):
                    self.spot2.message = 3   
                    self.spot2.sub_message = "Charger is occupied \nby another user"
            
            elif (self.array[1] == '8'):
                if (self.array[0] == '1'):
                    self.spot1.message = 3
                    self.spot1.sub_message = "You are not in the \nuserlist, go to \nwww.sustainablecharging.nl"
                elif (self.array[0] == '2'):
                    self.spot2.message = 3   
                    self.spot2.sub_message = "You are not in the \nuserlist, go to \nwww.sustainablecharging.nl"
            else:
                if (self.array[0] == '1'):
                    self.spot1.message = 3
                    self.spot1.sub_message = "Please contact the \nsystem administrator"
                elif (self.array[0] == '2'):
                    self.spot2.message = 3
                    self.spot2.sub_message = "Please contact the \nsystem administrator"
            

            