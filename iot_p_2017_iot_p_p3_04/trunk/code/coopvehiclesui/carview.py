from kivy.app import App
from kivy.graphics import *
from kivy.uix.relativelayout import RelativeLayout
from kivy.uix.screenmanager import ScreenManager, Screen
from kivy.core.window import Window
from kivy.clock import Clock

from variables import Variables
import vehicle

MIN_MARGIN = 10

class CarView(RelativeLayout):
    layout = 0
    def __init__(self, screenmanager, **kwargs):
        carViewSize = [Window.width * Variables().getCarViewSizeHint()[0], Window.height * Variables().getCarViewSizeHint()[1]]
        carSize = [carViewSize[0] / 7, carViewSize[1] / 4]
        
        super(RelativeLayout, self).__init__(**kwargs)
        #Create carview layout
        global layout
        layout = RelativeLayout()
        with layout.canvas:
            car = Rectangle(source='images/car.jpg', pos=(carViewSize[0] / 2 - carSize[0] / 2, carViewSize[1] / 2 - carSize[1] / 2), size=carSize)
        
        Clock.schedule_interval(self.updateCanvas, 0.1)
    
        self.add_widget(layout)
    
    def updateCanvas(self, *args):
        global MIN_MARGIN
        carViewSize = [Window.width * Variables().getCarViewSizeHint()[0], Window.height * Variables().getCarViewSizeHint()[1]]
        carSize = [carViewSize[0] / 7, carViewSize[1] / 4]
        
        MAX_DIST_SIDE = 150  #cm
        MAX_DIST_FRONT = 100  #cm
        multiplierSide = (float(carViewSize[0]) - float(carViewSize[0]) / 2 - float(carSize[0]) / 2 - 10) / MAX_DIST_SIDE
        multiplierFront = (float(carViewSize[1]) - float(carViewSize[1]) / 2 - float(carSize[1]) / 2 - 10) / MAX_DIST_FRONT
    
        with layout.canvas:
            layout.canvas.clear()
            car = Rectangle(source='images/car.jpg', pos=(carViewSize[0] / 2 - carSize[0] / 2, carViewSize[1] / 2 - carSize[1] / 2), size=carSize)
            
            leftDist = float(vehicle.vehicleList.getLDist(vehicle.vehicleList.selectedVehicle))
            rightDist = float(vehicle.vehicleList.getRDist(vehicle.vehicleList.selectedVehicle))
            frontDist = float(vehicle.vehicleList.getFDist(vehicle.vehicleList.selectedVehicle))
            
            leftMargin = carViewSize[0] / 2 - carSize[0] / 2 - leftDist * multiplierSide
            rightMargin = carViewSize[0] / 2 + carSize[0] / 2 + rightDist * multiplierSide
            frontMargin = carViewSize[1] / 2 + carSize[1] / 2 + frontDist * multiplierFront
            if leftMargin < MIN_MARGIN:
                leftMargin = MIN_MARGIN
            # Create line to left object
            Line(points=[leftMargin, 0, leftMargin, frontMargin], width=2)
            
            # Create line to right object
            Line(points=[rightMargin, 0, rightMargin, frontMargin], width=2)
            
            # Create line to front object
            Line(points=[leftMargin, frontMargin, rightMargin, frontMargin], width=2)