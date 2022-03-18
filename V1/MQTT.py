import paho.mqtt.client as mqtt #import the client
import json

class MQTT():
    def __init__(self, charging_spot1, charging_spot2):
        self.spot1 = charging_spot1
        self.spot2 = charging_spot2
        self.client = mqtt.Client()
        self.client.on_message = self.on_message
        self.client.connect("broker.hivemq.com")
        self.client.subscribe("HANevse/#")
        print("Connected to MQTT")

    def on_message(self, client, userdata, message):
        self.msg = str(message.payload.decode("utf-8"))
        print(self.msg)
        self.variables = json.loads(self.msg)
        try:
            if self.variables["SocketID"] == 1:
                self.spot1.update_measurements(self.variables)

            elif self.variables["SocketID"] == 2:
                self.spot2.update_measurements(self.variables)
        except:
            print("Not a data message")