import kivy
kivy.require('1.10.0') # replace with your current kivy version !

from kivy.app import App
from kivy.uix.screenmanager import ScreenManager, Screen

import serial

from mainscreen import MainScreen
from vehicle import Vehicle

#Create screenmanager
sm = ScreenManager()
sm.add_widget(MainScreen(sm, name='Mainscreen'))

class Coopvehicles(App):
    def build(self):
        return sm
    
if __name__ == '__main__':
    Coopvehicles().run()