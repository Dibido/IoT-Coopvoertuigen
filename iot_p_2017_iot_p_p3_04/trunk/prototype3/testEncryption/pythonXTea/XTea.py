from ctypes import c_uint8

class XTea:
    NUM_ROUNDS = 0
    key = []
    delta = 0
    
    def __init__(self):
        global NUM_ROUNDS
        global delta
        
        NUM_ROUNDS = 32
        delta = 0x9E3779B9
        
    def key(self, _key = []):
        global key
        key = _key
            
    def encrypt(self, v = []):
        v0 = v[0]
        v1 = v[1]
        
        sum = 0
        
        for i in range(NUM_ROUNDS):
            v0 += (((v1 << 4) ^ (v1 >> 5)) + v1) ^ (sum + key[sum & 3])
            sum += delta;
            v0 = c_uint8(v0).value
            v1 += (((v0 << 4) ^ (v0 >> 5)) + v0) ^ (sum + key[(sum >> 11) & 3])
            v1 = c_uint8(v1).value
        
        v[0] = v0
        v[1] = v1
        
    def decrypt(self, v = []):
        v0 = c_uint8(v[0]).value
        v1 = c_uint8(v[1]).value
        
        sum = delta * NUM_ROUNDS
        
        for i in range(NUM_ROUNDS):
            v1 -= (((v0 << 4) ^ (v0 >> 5)) + v0) ^ (sum + key[(sum >> 11) & 3])
            v1 = c_uint8(v1).value
            sum -= delta
            v0 -= (((v1 << 4) ^ (v1 >> 5)) + v1) ^ (sum + key[sum & 3])
            v0 = c_uint8(v0).value
        
        v[0] = v0
        v[1] = v1
        
    def encryptValues(self, nrOfValues, values = [], encryptedValues = []):
        tempList = []
        if (nrOfValues % 2 != 0):
            nrOfValues -= 1
            encryptedValues[nrOfValues] = values[nrOfValues]
        
        for i in range(0, nrOfValues, 2):
            tempList.insert(0, values[i])
            tempList.insert(1, values[i + 1])
            self.encrypt(tempList)
            encryptedValues[i] = tempList[0]
            encryptedValues[i + 1] = tempList[1]
    
    def decryptValues(self, nrOfValues, values = [], decryptedValues = []):
        tempList = []
        if (nrOfValues % 2 != 0):
            nrOfValues -= 1
            decryptedValues[nrOfValues] = values[nrOfValues]
        
        for i in range(0, nrOfValues, 2):
            print i+1
            print "test"
            tempList.insert(0, values[i])
            tempList.insert(1, values[i + 1])
            self.decrypt(tempList)
            decryptedValues[i] = tempList[0]
            decryptedValues[i + 1] = tempList[1]
    