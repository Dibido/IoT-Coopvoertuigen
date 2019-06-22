from kivy.app import App
from kivy.graphics import *
from kivy.uix.label import Label
from kivy.uix.button import Button
from kivy.uix.boxlayout import BoxLayout
from kivy.uix.screenmanager import ScreenManager, Screen
from kivy.core.window import Window
from kivy.uix.splitter import Splitter

'''
class InfoBoxLayout(BoxLayout):
    def on_size(self, *args):
        self.canvas.before.clear()
        with self.canvas.before:
            Color(.7,.7,.7,.2)
            Rectangle(pos=self.pos, size=self.size)
            '''

class InfoLabel(Label):
    def on_size(self, *args):
        self.canvas.before.clear()
        with self.canvas.before:
            Color(.8,.8,.8,.1)
            Rectangle(pos=self.pos, size=self.size)

class InfoBox(BoxLayout):
    
    selectedVehicle = None

    def __init__(self, screenmanager, **kwargs):
        super(InfoBox, self).__init__(**kwargs)
        #Set screenmanager
        sm = screenmanager
        #Create layout
        infoLayout = BoxLayout(size_hint=(None, 1), width=200, orientation='vertical', spacing=3)
        #No selected vehicle
        infoLayout.add_widget(InfoLabel(text=('Info'), size_hint_y = 0.05, bold=(True), halign=('center'), valign=('top')))
        noVehicle = InfoLabel(text=('No vehicle selected'), valign=('top'))
        graphButton = Button(size_hint=(1, 0.05), text=('Graphs'))
        #Add button callbacks
        def graphButtonCallback(instance):
            if(sm.has_screen('Graphscreen')):
                sm.current = 'Graphscreen'
        graphButton.bind(on_press=graphButtonCallback)
        infoLayout.add_widget(noVehicle)
        infoLayout.add_widget(graphButton)
        self.add_widget(infoLayout)

    def selectVehicle(vehicle):
        if vehicle != None:
            self.selectedVehicle = vehicle
            self.updateInfo()

    def updateInfo(self, *args):
        if vehicle != None:
            #If the id values have not been set create the widgets
            if(self.vehicleId == None):
                #Update infobox labels
                self.vehicleId = InfoLabel(size_hint=(1, 0.05), text=('ID : ' + vehicle.vid))
                self.frontDist = InfoLabel(size_hint=(1, 0.05), text=('FrontDist: ' + vehicle.frontdist))
                self.speed = InfoLabel(size_hint=(1, 0.05), text=('Speed : ' + vehicle.speed))
                self.lSpeed = InfoLabel(size_hint=(1, 0.05), text=('LSpeed : ' + vehicle.lSpeed))
                self.rSpeed = InfoLabel(size_hint=(1, 0.05), text=('RSpeed : ' + vehicle.rSpeed))
                self.lDist = InfoLabel(size_hint=(1, 0.05), text=('LDist : ' + vehicle.lDist))
                self.rDist = InfoLabel(size_hint=(1, 0.05), text=('RDist : ' + vehicle.rDist))
                self.mergeButton = Button(size_hint=(1, 0.05), text=('Merge'))
                self.exitButton = Button(size_hint=(1, 0.05), text=('Exit'))
                self.stopButton = Button(size_hint=(1, 0.05), text=('Stop'))
                self.GraphButton = Button(size_hint=(1, 0.05), text=('Graphs'))
                #Add button callbacks
                def graphButtonCallback(instance):
                    if(sm.has_screen('Graphscreen')):
                        sm.current = 'Graphscreen'
                graphButton.bind(on_press=graphButtonCallback)
                #Add buttons
                infoLayout.add_widget(graphButton)
                infoLayout.add_widget(frontDist)
                infoLayout.add_widget(speed)
                infoLayout.add_widget(lSpeed)
                infolayout.add_widget(rSpeed)
                infoLayout.add_widget(lDist)
                infoLayout.add_widget(rDist)
                infoLayout.add_widget(mergeButton)
                infoLayout.add_widget(exitButton)
                infoLayout.add_widget(stopButton)
            #Otherwise update the current info
            else:
                self.vehicleId.text = 'Id: ' + vehicle.vid
                self.frontDist = 'FrontDist: ' + vehicle.frontDist
                self.speed = 'Speed : ' + vehicle.speed
                self.lSpeed = 'Lspeed : ' + vehicle.lSpeed
                self.rSpeed = 'Rspeed : ' + vehicle.rSpeed
                self.lDist = 'LDist : ' + vehicle.lDist
                self.rDist = 'RDist : ' + vehicle.rDist
