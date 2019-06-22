from kivy.app import App
from kivy.graphics import *
from kivy.uix.label import Label
from kivy.uix.button import Button
from kivy.uix.relativelayout import RelativeLayout
from kivy.uix.screenmanager import ScreenManager, Screen
from kivy.core.window import Window
from kivy.properties import ListProperty

class CarView(RelativeLayout):
    def __init__(self, screenmanager, **kwargs):
        super(RelativeLayout, self).__init__(**kwargs)
        #Create carview layout
        layout = RelativeLayout()
        #Create carview items
        carView = Label(text='carView')
        #Add carview items to layout
        layout.add_widget(carView)
        with layout.canvas:
            Color(1,1,1,1)
            car1 = Rectangle(pos=(0, 0), size=(70,100))
        
        carId = Label(text='ID:1', pos=(-100,-100))
        layout.add_widget(carId)
        self.add_widget(layout)
