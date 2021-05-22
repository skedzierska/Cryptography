# Sonia Kedzierska

from Crypto.Cipher import AES
from Crypto.Random import get_random_bytes

# encryption

input1_file = open("file1.txt", 'rb')
output1_file = open("file2.txt", 'wb')

key = get_random_bytes(16)
buffer_size = 32768  #32kb

cipher = AES.new(key, AES.MODE_CFB)
output1_file.write(cipher.iv)

buffer = input1_file.read(buffer_size)
while len(buffer) > 0:
    ciphered_bytes = cipher.encrypt(buffer)
    output1_file.write(ciphered_bytes)
    buffer = input1_file.read(buffer_size)

input1_file.close()
output1_file.close()

# decryption

input2_file = open("file2.txt", 'rb')
output2_file = open("file3.txt", 'wb')

iv = input2_file.read(16)
cipher = AES.new(key, AES.MODE_CFB, iv=iv)

buffer = input2_file.read(buffer_size)
while len(buffer) > 0:
    decrypted_bytes = cipher.decrypt(buffer)
    output2_file.write(decrypted_bytes)
    buffer = input2_file.read(buffer_size)

input2_file.close()
output2_file.close()
