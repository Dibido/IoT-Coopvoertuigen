# External modules
from kivy.app import App
from kivy.graphics import *
from kivy.uix.label import Label
from kivy.uix.button import Button
from kivy.uix.boxlayout import BoxLayout
from kivy.uix.screenmanager import ScreenManager, Screen
from kivy.core.window import Window
from kivy.clock import Clock

from functools import partial
from XTea import XTea
from requestHandler import RequestHandler

# Internal modules
import networkHandler
import vehicle
import messageParser

# The baudrate on what the serial gateway runs
baudrate = 115200

#The url for the post
SERVER_URL = 'http://127.0.0.1:5000/data'

# The speed in seconds at which the screen updates
updatespeed = .1

# The speed at what the car should ride with the startdriving message
carspeed = 100

# The characters to identify a incoming message
request_char = 'R'
data_char = 'D'

# Max speed in cm per sec
MAX_SPEED = 15.24

# Maximum speed of vehicle
MAX_SERVO_SPEED = 200

# Encryption
N_VALUES = 6 # Number of encrypted values
key = [0x01020304, 0x05060708, 0x090a0b0c, 0x0d0e0f00] # Encryption key
CHAR_POSITION = 0

class InfoLabel(Label):
    def on_size(self, *args):
        self.canvas.before.clear()
        with self.canvas.before:
            Color(.8,.8,.8,.1)
            Rectangle(pos=self.pos, size=self.size)

class InfoBox(BoxLayout):
    labels = []
    idLayout = 0
    buttons = []
    networkHandler = 0
    requestHandler = 0
	
    def __init__(self, screenmanager, **kwargs):
        super(InfoBox, self).__init__(**kwargs)
		
        #Set default values for buttons
        self.buttons = [None]*(vehicle.NR_OF_VEHICLES+1)
        #Set screenmanager
        sm = screenmanager
        #Create layout
        infoLayout = BoxLayout(size_hint=(None, 1),width=250, orientation='vertical', spacing=3)
		
		#Make the updateclock with updatespeed in seconds
        Clock.schedule_interval(self.updateInfo,updatespeed)
		
        #Open the serial interface
        self.networkHandler = networkHandler.NetworkHandler(baudrate)
		
		#Set the server variables
        self.requestHandler = RequestHandler(SERVER_URL)

		#Make the labels with all zero's
        self.init_labels(infoLayout)
		
        #Create the buttons
        stopButton = Button(text='Stop')
        startButton = Button(text='Start')
        mergeButton = Button(text='Merge')
        exitButton = Button(text='Exit')
		
		#Bind the buttons to functions
        stopButton.bind(on_press=self.sendStop)
        startButton.bind(on_press=self.sendStart)
        mergeButton.bind(on_press=self.sendMerge)
        exitButton.bind(on_press=self.sendExit)
		
		#Add the buttons to the layout
		#Put the buttons in a seperate boxlayout to get them horizontal
        start_stopLayout = BoxLayout(orientation='horizontal', size_hint=(1,.5))
        start_stopLayout.add_widget(stopButton)
        start_stopLayout.add_widget(startButton)
        infoLayout.add_widget(start_stopLayout)
		
        #Make an apart boxlayout for the merge and exit buttons
        merge_exitLayout = BoxLayout(orientation='horizontal',size_hint=(1,.5))
        merge_exitLayout.add_widget(mergeButton)
        merge_exitLayout.add_widget(exitButton)
        infoLayout.add_widget(merge_exitLayout)
		
        self.idLayout =BoxLayout(orientation='horizontal', size_hint=(1,.5))
        infoLayout.add_widget(self.idLayout)
        self.add_widget(infoLayout)
    
	#Make button callbacks
    #Callback for the stop driving button
    def sendStop(self,args):
        self.networkHandler.send_stop_driving(vehicle.vehicleList.selectedVehicle)
        vehicle.vehicleList.setInRow(vehicle.vehicleList.selectedVehicle,True)
		
    #Callback for the start driving button
    def sendStart(self,args):
        self.networkHandler.send_start_driving(vehicle.vehicleList.selectedVehicle,carspeed)
        vehicle.vehicleList.setInRow(vehicle.vehicleList.selectedVehicle,True)
		
    def sendMerge(self,args):
        avgLDist = 0
        avgRDist = 0
        nrOfVehiclesCounted = 0
        for i in vehicle.vehicleList.getAvailableVehicles():
            if i != 0:
                if vehicle.vehicleList.getInRow(i) == True:
                    avgLDist += vehicle.vehicleList.getLDist(i)
                    avgRDist += vehicle.vehicleList.getRDist(i)
                    nrOfVehiclesCounted += 1
		#The -1 because of the 0 that is standard added in the vehicle list
        
        if nrOfVehiclesCounted > 0:
            avgLDist = avgLDist / nrOfVehiclesCounted
            avgRDist = avgRDist / nrOfVehiclesCounted

        self.networkHandler.send_merge_signal(vehicle.vehicleList.selectedVehicle,avgLDist,avgRDist)
        vehicle.vehicleList.setInRow(vehicle.vehicleList.selectedVehicle,True)

    def sendExit(self,args):
        self.networkHandler.send_exit_signal(vehicle.vehicleList.selectedVehicle)
        vehicle.vehicleList.setInRow(vehicle.vehicleList.selectedVehicle,False)

    #Initialise the labels
    def init_labels(self,infoLayout):
		#Make the initial labels
        lSpeed = vehicle.vehicleList.getLSpeed(vehicle.vehicleList.selectedVehicle)
        rSpeed = vehicle.vehicleList.getRSpeed(vehicle.vehicleList.selectedVehicle)
        fDist = vehicle.vehicleList.getFDist(vehicle.vehicleList.selectedVehicle)
        lDist = vehicle.vehicleList.getLDist(vehicle.vehicleList.selectedVehicle)
        rDist = vehicle.vehicleList.getRDist(vehicle.vehicleList.selectedVehicle)
        
		#Add initial text to the labels
        idLabel = InfoLabel(text=('Id: '+str(vehicle.vehicleList.selectedVehicle)))
        leftSpeed = InfoLabel(text=('Left speed: '+ str(lSpeed) + ' / ' + str((float(lSpeed) / MAX_SERVO_SPEED) * MAX_SPEED) + 'cm/s'))
        rightSpeed = InfoLabel(text=('Right speed: '+ str(rSpeed) + ' / ' + str((float(rSpeed) / MAX_SERVO_SPEED) * MAX_SPEED) + 'cm/s'))
        frontDist = InfoLabel(text=('Front distance: '+ str(fDist) + ' cm'))
        leftDist = InfoLabel(text=('Left distance: '+ str(lDist) + ' cm'))
        rightDist = InfoLabel(text=('Right distance: '+ str(rDist) + ' cm'))
		
		#Add the labels to the label array
        self.labels.append(idLabel)
        self.labels.append(leftSpeed)
        self.labels.append(rightSpeed)
        self.labels.append(frontDist)
        self.labels.append(leftDist)
        self.labels.append(rightDist)
		#Add the labels from the label array to the infoLayout
        for i in self.labels:
            infoLayout.add_widget(i)
			
    #Handle the serial input 
    def updateInfo(self, *args):
        #Update the labels
        lSpeed = vehicle.vehicleList.getLSpeed(vehicle.vehicleList.selectedVehicle)
        rSpeed = vehicle.vehicleList.getRSpeed(vehicle.vehicleList.selectedVehicle)
        fDist = vehicle.vehicleList.getFDist(vehicle.vehicleList.selectedVehicle)
        lDist = vehicle.vehicleList.getLDist(vehicle.vehicleList.selectedVehicle)
        rDist = vehicle.vehicleList.getRDist(vehicle.vehicleList.selectedVehicle)
		
        self.update_labels(vehicle.vehicleList.selectedVehicle,lSpeed,rSpeed,fDist,lDist,rDist)
        self.update_buttons()
	
        # Handle the incoming message
        received = self.networkHandler.receive_data()
        if received != "":
            print(received)

            list = messageParser.parse_message(received)
            if list == 0:
                return
            list[1] = ord(list[1])

            # Gateway startup, if empty: return
            if list[0] == str(0) or list[1] == 255:
                return

            data = messageParser.parse_data(received)
            encryptedData = [list[1]]

            for x in xrange(0, len(data)):
                if data[x] != '':
                    encryptedData.insert(x + 1, int(data[x]))

            xtea = XTea()
            xtea.key(key)
            decryptedData = [None]*N_VALUES
            xtea.decryptValues(len(encryptedData), encryptedData, decryptedData)

            # Handle a register request         
            if chr(decryptedData[CHAR_POSITION]) == request_char:
                vehicleId = list[0]
                if int(decryptedData[1]) == int(vehicleId):
                    self.networkHandler.send_registered(list[0])
                    inRow = True
                    vehicle.vehicleList.addVehicle(vehicleId, inRow, lSpeed, rSpeed, fDist, lDist, rDist)
                    if vehicle.vehicleList.selectedVehicle == 0:
                             vehicle.vehicleList.selectedVehicle = list[0]

            # Handle incoming data
            if chr(decryptedData[CHAR_POSITION]) == data_char:
                if int(list[0]) in vehicle.vehicleList.getAvailableVehicles():
                    vehicle.vehicleList.changeVehicle(list[0], decryptedData[1], decryptedData[2], decryptedData[3], decryptedData[4], decryptedData[5])
                    dict = {"vehicleId":int(list[0]),"leftSpeed":decryptedData[1],"rightSpeed":decryptedData[2],
				    "frontDist":decryptedData[3],"leftDist":decryptedData[4],"rightDist":decryptedData[5]}
                    self.requestHandler.sendJsonRequest(dict)
				
	#update the labels with the parameters				
    def update_labels(self, id, leftS, rightS, frontD, leftD, rightD):
        self.labels[0].text = 'Id: '+str(id)
        self.labels[1].text = 'Left speed: '+ str(leftS) + ' / ' + str((float(leftS) / MAX_SERVO_SPEED) * MAX_SPEED) + ' cm/s'
        self.labels[2].text = 'Right speed: '+ str(rightS) + ' / ' + str((float(rightS) / MAX_SERVO_SPEED) * MAX_SPEED) + ' cm/s'
        self.labels[3].text = 'Front distance: '+ str(frontD) + ' cm'
        self.labels[4].text = 'Left distance: '+ str(leftD) + ' cm'
        self.labels[5].text = 'Right distance: '+ str(rightD) + ' cm'

    def update_buttons(self):
        availableList = vehicle.vehicleList.getAvailableVehicles()
        for i in availableList:
            if self.buttons[i] == None:
                if i != 0:
                    self.buttons[i] = Button(text=str(i))
                    buttoncallback=partial(self.changeSelectedVehicle,i)
                    self.buttons[i].bind(on_press=buttoncallback)
                    self.idLayout.add_widget(self.buttons[i])
					
    def changeSelectedVehicle(self,vid,args):
        vehicle.vehicleList.selectedVehicle = vid