# Sonia Kedzierska

from Crypto.PublicKey import RSA
from Crypto.Cipher import PKCS1_OAEP
import binascii
import math

Pair_key = RSA.generate(1024)
public_key = Pair_key.publickey()
private_key = Pair_key.exportKey

file_to_encrypt = open("file1.txt", 'rb')
text = file_to_encrypt.read()
encrypted_file = open("file2.txt", 'wb')

encryptor = PKCS1_OAEP.new(public_key)
encrypted = encryptor.encrypt(text)
encrypted_file.write(binascii.hexlify(encrypted))


def count(message):
    number = 0
    for char in message.upper():
        number += 1
    return number


file_to_encrypt.close()

stats = open("file2.txt", 'a+')
stats.write('\n\nNumber of all chars: ')
num_of_chars = count(encrypted)
stats.write(str(num_of_chars))
stats.write('\n')


def frequency_entropy(message):
    # frequency
    chars = []
    for char in message.upper():
        if char not in chars:
            chars.append(char)
    stats.write('Number of chars without the repeated ones: ')
    stats.write(str(len(chars)))
    stats.write('\n\nFrequency of the chars: \n')
    n = 0
    freq_char = {}
    for char in range(len(chars)):
        freq = 1
        for ch in message.upper():
            if ch == char:
                freq += 1
        freq_char[hex(chars[char])] = freq
    sorted_freq = {k: v for k, v in sorted(freq_char.items(), key=lambda item: item[1], reverse=True)}
    for i, val in sorted_freq.items():
        stats.write(i)
        stats.write(': ')
        stats.write(str(val))
        stats.write('\n')
    stats.write('\n')

    # entropy
    v = []
    for i, val in sorted_freq.items():
        v.append(val)
    en = 0
    for i in range(len(v)):
        p = v[i]/len(v)
        en += -p*math.log(p, 2)
    stats.write('Entropy: ')
    stats.write(str(en))


frequency_entropy(encrypted)
