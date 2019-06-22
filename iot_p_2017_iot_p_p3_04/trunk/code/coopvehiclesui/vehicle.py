VEHICLE_ERROR = 'Error: VehicleList'
NR_OF_VEHICLES = 255
OUT_OF_RANGE_ERROR = 'Error: Out of range'

class VehicleList:
    _vehicles = False
    selectedVehicle = 0
    def __init__(self,nrOfVehicles):
        self._vehicles = [None]*(nrOfVehicles)
        self.addVehicle(0,False,0,0,0,0,0)

	#Check if the vehicle exists in the vehiclelist
    def vehicleExists(self,vid):
        if int(vid) < len(self._vehicles):
            return self._vehicles[int(vid)] != None
        print('Out of range')
        return OUT_OF_RANGE_ERROR
	
	#Add a vehicle to the vehiclelist
    def addVehicle(self, vid, inRow, lSpeed, rSpeed, frontDist, lDist, rDist):
        if self.vehicleExists(int(vid)) == True:
            print('The vehicle',vid,'already exists')
            return VEHICLE_ERROR
        elif self.vehicleExists(int(vid)) == OUT_OF_RANGE_ERROR:
            print('The vehicle',vid,'is out of range')
            return OUT_OF_RANGE_ERROR
        self._vehicles[int(vid)] = Vehicle(int(vid),inRow,lSpeed,rSpeed,frontDist,lDist,rDist)

    #Deletes a vehicle from the vehiclelist
    def deleteVehicle(self,vid):
        if self.vehicleExists(vid) != OUT_OF_RANGE_ERROR:
            vehicles[int(vid)]=None
            return True
        return False

	#Change the information of a vehicle
    def changeVehicle(self,vid, lSpeed, rSpeed, frontdist, lDist, rDist):
        if self.vehicleExists(vid) != True:
            return VEHICLE_ERROR
        self._vehicles[int(vid)].change(lSpeed,rSpeed,frontdist,lDist,rDist)

	#---GETTERS---
	#Get a list with all the available vehicle id's
    def getAvailableVehicles(self):
        list = []
        for i in range(0,len(self._vehicles)):
            if self.vehicleExists(i):
                list.append(i)
        return list

    def getInRow(self,vid):
        if self.vehicleExists(vid) != True:
            return VEHICLE_ERROR
        return int(self._vehicles[int(vid)].inRow)
    
    def getLSpeed(self,vid):
        if self.vehicleExists(vid) != True:
            return VEHICLE_ERROR
        return int(self._vehicles[int(vid)].lSpeed)

    def getRSpeed(self,vid):
        if self.vehicleExists(vid) != True:
            return VEHICLE_ERROR
        return int(self._vehicles[int(vid)].rSpeed)

    def getFDist(self,vid):
        if self.vehicleExists(vid) != True:
            return VEHICLE_ERROR
        return int(self._vehicles[int(vid)].frontDist)

    def getLDist(self,vid):
        if self.vehicleExists(vid) != True:
            return VEHICLE_ERROR
        return int(self._vehicles[int(vid)].lDist)

    def getRDist(self,vid):
        if self.vehicleExists(vid) != True:
            return VEHICLE_ERROR
        return int(self._vehicles[int(vid)].rDist)
		
    def getListLength(self):
        return len(self._vehicles)
	
	#---SETTERS---
    def setInRow(self,vid,bool):
        if self.vehicleExists(vid) != True:
            return VEHICLE_ERROR
        self._vehicles[int(vid)].inRow = bool

class Vehicle:
    def __init__(self, vid, inRow, lSpeed, rSpeed, frontdist, lDist, rDist):
        self.vehicleId = vid
        self.inRow = inRow
        self.lSpeed = lSpeed
        self.rSpeed = rSpeed
        self.frontDist = frontdist
        self.lDist = lDist
        self.rDist = rDist

	#Change the vehicles information
    def change(self,lSpeed,rSpeed,frontdist,lDist,rDist):
        self.lSpeed = lSpeed
        self.rSpeed = rSpeed
        self.frontDist = frontdist
        self.lDist = lDist
        self.rDist = rDist

#The global vehicleList that can be used to update and get the information from		
vehicleList = VehicleList(NR_OF_VEHICLES)