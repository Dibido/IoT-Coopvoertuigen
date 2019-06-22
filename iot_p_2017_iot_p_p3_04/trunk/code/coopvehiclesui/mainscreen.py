from kivy.app import App
from kivy.uix.boxlayout import BoxLayout
from kivy.uix.screenmanager import ScreenManager, Screen
from kivy.core.window import Window

from infobox import InfoBox
from carview import CarView
from variables import Variables

class MainScreen(Screen, App):

    def __init__(self, screenmanager, **kwargs):
        super(MainScreen, self).__init__(**kwargs)
        #Set screenmanager
        sm = screenmanager
        #Set backgroundcolor
        Window.clearcolor = (.2,.2,.2,1)
        #Create master box layout
        layout = BoxLayout(spacing=10)
        #Create infobox
        infobox = InfoBox(sm, size_hint=Variables().getInfoboxSizeHint()) 
        #Create carview
        carViewLayout = CarView(sm, size_hint=Variables().getCarViewSizeHint())
        #Add layouts to the master layout
        layout.add_widget(infobox)
        layout.add_widget(carViewLayout)
        self.add_widget(layout)
        
    def getCarViewSize():
        return carViewSizeHint