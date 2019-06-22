from kivy.app import App
#kivy.require("1.8.0")
from kivy.uix.label import Label
from kivy.uix.button import Button
from kivy.uix.gridlayout import GridLayout
from kivy.uix.floatlayout import FloatLayout
from kivy.uix.textinput import TextInput
from kivy.graphics import *


#class InfoLabel(Label):
 #   def on_size(self, *args):
  #      self.canvas.before.clear()
   #     with self.canvas.before:
    #        Color(.8,.8,.8,.1)
     #       Rectangle(pos=self.pos, size=self.size)
                    
class MainScreen(GridLayout):
    def __init__(self, **kwargs):
        super(MainScreen, self).__init__(**kwargs)
        #self.cols = 2
        #self.add_widget(Label(text="Username:"))
        #self.add_widget(Button(pos_hint={'top': 0.5}, size=(70,100)))
        with self.canvas:
                # Add a red color
                Color(1., 0, 0)

                # Add a rectangle
                Rectangle(pos=(10, 10), size=(500, 500))
            

class SimpleKivy(App):
    def build(self):
        return MainScreen()

if __name__ == "__main__":
    SimpleKivy().run()
		
		
