from kivy.app import App
from kivy.graphics import *
from kivy.uix.label import Label
from kivy.uix.button import Button
from kivy.uix.boxlayout import BoxLayout
from kivy.uix.stacklayout import StackLayout
from kivy.uix.screenmanager import ScreenManager, Screen
from kivy.core.window import Window
from kivy.uix.splitter import Splitter

from infobox import InfoBox
from carview import CarView

#class InfoStackLayout(StackLayout):
#    def on_size(self, *args):
#        self.canvas.before.clear()
#        with self.canvas.before:
#            Color(.7,.7,.7,.2)
#            Rectangle(pos=self.pos, size=self.size)
#
#class InfoLabel(Label):
#    def on_size(self, *args):
#        self.canvas.before.clear()
#        with self.canvas.before:
#            Color(.8,.8,.8,.1)
#            Rectangle(pos=self.pos, size=self.size)

class MainScreen(Screen, App):

    def __init__(self, screenmanager, **kwargs):
        super(MainScreen, self).__init__(**kwargs)
        #Set screenmanager
        sm = screenmanager
        #Set backgroundcolor
        Window.clearcolor = (.2,.2,.2,1)
        #Set selected vehicle id
        selectedVehicle = None 
        #Create master box layout
        layout = BoxLayout(spacing=10)
        #Create infobox
        infobox = InfoBox(sm, size_hint=(0.3,1)) 
        #Create carview
        carViewLayout = CarView(sm, size_hint=(0.7,1))
        #Add layouts to the master layout
        layout.add_widget(infobox)
        layout.add_widget(carViewLayout)
        self.add_widget(layout)
        #self.add_widget(infobox)
        #self.add_widget(carViewLayout)

