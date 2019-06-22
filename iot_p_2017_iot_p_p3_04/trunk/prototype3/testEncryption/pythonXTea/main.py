from XTea import XTea

xtea = XTea()

key = [ 0x01020304, 0x05060708, 0x090a0b0c, 0x0d0e0f00 ]
xtea.key(key)

v1 = [1, 82]
v2 = [1, 82, 7, 203]

print
print("Not yet encrypted with encrypt/decrypt: " + str(v1))

xtea.encrypt(v1)
print("Encrypted with encrypt: " + str(v1))    #should be 40 and 238

xtea.decrypt(v1)
print("Decrypted with decrypt: " + str(v1))    #should be 1 and 82

print
print("Not yet encrypted with encryptValues/decryptValues: " + str(v2))

xtea.encryptValues(4, v2, v2)
print("Encrypted with encryptValues: " + str(v2))    #should be 40 and 238 and 114 and 64

xtea.decryptValues(4, v2, v2)
print("Decrypted with decryptValues: " + str(v2))    #should be 1 and 82 and 7 and 203