from kivy.app import App
from kivy.uix.label import Label
from kivy.uix.button import Button
from kivy.uix.screenmanager import ScreenManager, Screen
from kivy.uix.boxlayout import BoxLayout
from kivy.uix.tabbedpanel import TabbedPanel, TabbedPanelHeader, TabbedPanelItem

class GraphScreen(TabbedPanel, BoxLayout, Screen):

    def __init__(self, screenmanager, **kwargs):
        super(GraphScreen, self).__init__(**kwargs)
        #Set screenmanager
        sm = screenmanager
        #Set master layout
        layout = BoxLayout(spacing=10)
        #Create tabpanel
        tabs = TabbedPanel()
        #Add tabs
        speedTab = TabbedPanelItem(text='Speed')
        speedTab.content = Label(text='Speed')
        backTab = TabbedPanelItem(text='Back')
        tabs.add_widget(speedTab)
        tabs.add_widget(backTab)
        layout.add_widget(tabs)
        self.add_widget(layout)

    def backButtonCallback(instance):
        if(sm.has_screen('Mainscreen')):
            sm.current = 'Mainscreen'
