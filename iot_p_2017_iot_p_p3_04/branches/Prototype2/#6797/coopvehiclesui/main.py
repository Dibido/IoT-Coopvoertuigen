import kivy
kivy.require('1.10.0') # replace with your current kivy version !

from kivy.app import App
from kivy.uix.screenmanager import ScreenManager, Screen

import serial

from mainscreen import MainScreen
from graphscreen import GraphScreen
from vehicle import Vehicle

vehicles = []
vehicles.append(Vehicle(1, True, '+100', '+100', 100, 10, 12, 13))

#arduinoSerial = serial.Serial('dev/ttyACM0', timeout=1)

#Create screenmanager
sm = ScreenManager()
sm.add_widget(MainScreen(sm, name='Mainscreen'))
sm.add_widget(GraphScreen(sm, name='Graphscreen'))

class Coopvehicles(App):
    def build(self):
        return sm
    
if __name__ == '__main__':
    Coopvehicles().run()
