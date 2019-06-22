import string

#Message separationcharacters for user messages and MySensors messages
message_begin_end = '/'
mysensors_separation = ';'
mysensors_child_sensor ='255'
user_separation = ';'

#An array for standard characters which are included in messages
chars = [message_begin_end,mysensors_separation,user_separation,'-','\n']

#Returns a list with [0] = node_id, [1] = child_sensor, [2] = content
def parse_message(received):
    global message_begin_end
    global mysensors_separation
    global mysensors_child_sensor

	#Split the received string into mysensors parts
    list = received.split(mysensors_separation)
	#This gets rid of the \n at the end of a message which is the standard ending of a MySensors message
    content = list[5][:-1]
	#If the child sensor is from the MySensors which is standard 255 it triggers an unique parser specific for mysensors
    if list[1] != mysensors_child_sensor:
        mysensors_header = received[:received.index(message_begin_end)]
        content = received[received.index(message_begin_end):-1]	
        #Filter the received string for any other characters than numbers
        tempstring = received
        for i in chars:
            tempstring = tempstring.replace(i, '')	
        if tempstring.isdigit() == False:
            print('Invalid message received')
            return 0
    return_list = []
    return_list.insert(0,list[0]) #Node id 
    return_list.insert(1,chr(int(list[1]))) #Child sensor/message sign
    return_list.insert(2,content) #Content
    return return_list
	
def parse_data(data):
    global message_begin_end
    global user_separation
	#This gets rid of the / at the beginning and the /\n at the end of a user defined message
    data = data[data.index(message_begin_end)+1:-2]
    list = data.split(user_separation)
    return list 
    #0 = leftSpeed, 1 = rightSpeed, 2 = frontDist, 3 = leftDist, 4 = rightDist
