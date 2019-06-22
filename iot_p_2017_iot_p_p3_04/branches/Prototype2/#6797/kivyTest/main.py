'''
TabbedPanel
============

Test of the widget TabbedPanel.
'''

from kivy.app import App
from kivy.graphics import *
from kivy.uix.label import Label
from kivy.uix.button import Button
from kivy.uix.relativelayout import RelativeLayout
from kivy.uix.screenmanager import ScreenManager, Screen
from kivy.core.window import Window
from kivy.properties import ListProperty
from kivy.uix.tabbedpanel import TabbedPanel
from kivy.lang import Builder


Builder.load_string("""

<Test>:
    FloatLayout:
        Button:
            text: "Button uno"
            pos_hint: {'x' : .8, 'y' : .6}
            size_hint: .2, .2
""")


class Test():
    pass


class TabbedPanelApp(App):
    def build(self):
        return Test()


if __name__ == '__main__':
    TabbedPanelApp().run()
