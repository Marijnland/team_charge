

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
        self.power = 0

    def update_measurements(self, variables):
        self.V1 = variables["V1"]
        self.V2 = variables["V2"]
        self.V3 = variables["V3"]
        self.I1 = variables["I1"]
        self.I2 = variables["I2"]
        self.I3 = variables["I3"]
        self.F  = variables["F"]
        self.UserID = variables["UserID"]


        #check for 3 phase
        if (self.I1 > 1) & (self.I2 > 1) & (self.I3 > 1):
            self.is_three_phase = True
        else:
            self.is_three_phase = False

        #set power
        if self.is_three_phase:
            self.power = (self.I1 * self.V1) + (self.I2 * self.V2) + (self.I3 * self.V3)
        else:
            if (self.I1 > 1):
                self.power = self.I1 * self.V1
            elif (self.I2 > 1):
                self.power = self.I2 * self.V2
            elif (self.I3 > 1):
                self.power = self.I3 * self.V3

        #set time
        if (self.is_active == False) & ((self.I1 > 1) | (self.I2 > 1) | (self.I3 > 1)):
            self.is_active = True
            self.start_time = variables["Time"]
        elif (self.is_active == True) & ((self.I1 > 1) | (self.I2 > 1) | (self.I3 > 1)):
            self.total_time = variables["Time"] - self.start_time
        elif (self.is_active == True) & ((self.I1 < 1) | (self.I2 < 1) | (self.I3 < 1)):
            self.is_active = False
            self.end_time = variables["Time"] - self.start_time
        print(self.total_time)