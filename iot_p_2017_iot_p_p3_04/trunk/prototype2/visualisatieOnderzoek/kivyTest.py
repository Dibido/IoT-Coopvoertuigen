from kivy.uix.boxlayout import BoxLayout
from kivy.uix.label import Label
from kivy.app import App
from kivy.uix.button import Button
from kivy.uix.image import Image

nr_of_cars=4
current_nr =2

class MainView(BoxLayout):
    def __init__(self, **kwargs):
		global nr_of_cars
		super(MainView, self).__init__(**kwargs)
		self.autos = []
		for i in xrange(0,nr_of_cars):
			if i<current_nr:
				self.autos.append(Label(text='Car '+str(i+1)))
			else:
				self.autos.append(Label(text=''))
		self.add_widget(Button(text='Delete',on_press=self.delete_car,size_hint_y=.10,pos_hint={'right':0,'center_y':.95}))
		self.add_widget(Button(text='Add',on_press=self.add_car,size_hint_y=.10,pos_hint={'right':1,'center_y':.95}))
		for i in self.autos:
			print i
			self.add_widget(i)
			
       
    def delete_car(self,button):
		global current_nr
		if current_nr != 0:
			current_nr -=1
			self.autos[current_nr].text = str('')
	
    def add_car(self,button):
		global current_nr
		if current_nr != nr_of_cars:
			current_nr+=1
			self.autos[current_nr-1].text=str('Car '+str(current_nr))
			

class MyApp(App):
    def build(self):
        return MainView()


MyApp().run()