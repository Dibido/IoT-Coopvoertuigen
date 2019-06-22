import serial
import serial.tools.list_ports
import platform
from XTea import XTea

# All the messagetypes which the visualiser can send
messagetypes = {'stopdriving' : 's','heartbeat' : 'h','startdriving' : 'd', 'merge' : 'm','exit' : 'e','register' : 'r'}

# Minimal and maximal speed for the car
minspeed = -200
maxspeed = 200

# Delimiters
data_delim = ';'
message_delim = '/'
message_ending = '\n'

# Encryption
key = [0x01020304, 0x05060708, 0x090a0b0c, 0x0d0e0f00]

class NetworkHandler:
    serial_port = 0
    _mysensors_separation = ';'
    _timeout = .1

    global xtea
    xtea = XTea()
    xtea.key(key)
    
    def get_serial_port_windows(self):
        # produce a list of all serial ports. The list contains a tuple with the port number, 
        # description and hardware address
        ports = list(serial.tools.list_ports.comports())  

        # return the port if 'USB' is in the description 
        for port_no, description, address in ports:
            if 'USB' in description:
                print(port_no)
                return port_no

    def get_serial_port_linux(self):
        return "/dev/pts/9"

    def __init__(self,baudrate):
        if platform.system() == 'Windows':
            self.serial_port = serial.Serial(self.get_serial_port_windows(),baudrate,timeout=self._timeout)
        elif platform.system() == 'Linux':
            self.serial_port = serial.Serial(self.get_serial_port_linux(),baudrate,timeout=self._timeout)
        else:
            print("The os ", platform.system(), " is not supported")

    def send_stop_driving(self,node_id):
        data = [ord(messagetypes['stopdriving']), int(node_id)]
        xtea.encryptValues(len(data), data, data)
        send_string = str(node_id)+data_delim+str(data[0])+data_delim+'0'+data_delim+'0'+data_delim+'0'+data_delim+message_delim+str(data[1])+message_delim+message_ending
        self.serial_port.write(send_string)

    def send_heartbeat(self,node_id):
        data = [ord(messagetypes['heartbeat']), int(node_id)]
        xtea.encryptValues(len(data), data, data)
        send_string = str(node_id)+data_delim+data[0]+data_delim+'0'+data_delim+'0'+data_delim+'0'+data_delim+message_delim+data[1]+message_delim+message_ending
        self.serial_port.write(send_string)

    def send_start_driving(self,node_id,speed):
        if speed < minspeed:
            speed = minspeed
        if speed > maxspeed:
            speed = maxspeed

        data = [ord(messagetypes['startdriving']), speed]
        xtea.encryptValues(len(data), data, data)

        send_string = str(node_id)+data_delim+str(data[0])+data_delim+'0'+data_delim+'0'+data_delim+'0'+data_delim+message_delim+str(data[1])+message_delim+message_ending
        self.serial_port.write(send_string)

    def send_merge_signal(self, node_id, lDist, rDist):
        data = [ord(messagetypes['merge']), lDist, rDist]
        xtea.encryptValues(len(data), data, data)

        send_string = str(node_id)+data_delim+str(data[0])+data_delim+'0'+data_delim+'0'+data_delim+'0'+data_delim+message_delim+str(data[1])+data_delim+str(data[2])+message_delim+message_ending
        self.serial_port.write(send_string)

    def send_exit_signal(self, node_id):
        data = [ord(messagetypes['exit']), int(node_id)]
        xtea.encryptValues(len(data), data, data)
        send_string = str(node_id)+';'+str(data[0])+data_delim+'0'+data_delim+'0'+data_delim+'0'+data_delim+message_delim+str(data[1])+message_delim+message_ending
        self.serial_port.write(send_string)

    def send_registered(self, node_id):
        data = [ord(messagetypes['register']), int(node_id)]
        xtea.encryptValues(len(data), data, data)
        send_string = str(node_id)+';'+str(data[0])+data_delim+'0'+data_delim+'0'+data_delim+'0'+data_delim+message_delim+str(data[1])+message_delim+message_ending
        self.serial_port.write(send_string)
		
    def receive_data(self):
        return self.serial_port.readline()
