import requests
import time
import datetime


class RequestHandler:
    url = 0
    request = 0
    
    def __init__(self,url):
        self.url = url
		
    def sendJsonRequest(self,dict):
        ts = time.time()
        dict['Timestamp'] = datetime.datetime.fromtimestamp(ts).strftime("%Y-%m-%d %H:%M:%S")
        self.request = requests.post(self.url,json=dict)
        