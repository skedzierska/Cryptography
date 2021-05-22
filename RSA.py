# Sonia Kędzierska

from Crypto.PublicKey import RSA
from Crypto.Cipher import PKCS1_OAEP
import binascii

# wygenerowałam klucz publiczny i prywatny nastepnie wybrałam klucz 1024 bitowy ponieważ tekst jawny jest krótki
# w innym wypadku można wziąć klucz 2048 bitowy lub 3072
# klucz publiczny jest reprezentowany jako para liczb (n, e), natomiast klucz prywatnym jako para (n, d).
# w kluczu publicznym n jest iloczynem 2 liczb pierwszych(p i q, ktore sa liczbami pierwszymi) a e jest publiczną eksponentą
# w kluczu prywatnym d jest prywatną eksponentą

Pair_key = RSA.generate(1024)
public_key = Pair_key.publickey()
private_key = Pair_key.exportKey

# otwieramy file1 aby móc zaszyfrować znajdujacy się w nim tekst
# oraz otwieramy file2 zeby umieścić w nim zaszyfrowany tekst
file_to_encrypt = open("file1.txt", 'rb')
text = file_to_encrypt.read()
encrypted_file = open("file2.txt", 'wb')
# PKCS1_OAEP to algorytm RSA który wykorzystuje padding aby zapewnić większe bezpieczeństwo szyfrowania
encryptor = PKCS1_OAEP.new(public_key)
# tekst jest paddingowany zerami aby jego długość zgadzała się z kluczem
# a następnie kodowana za pomocą modulo n
encrypted = encryptor.encrypt(text)
# umieszczamy zaszyfrowany tekst w file2
# binascii.hexlify zamienienia szyfr na system szesnastkowy
encrypted_file.write(binascii.hexlify(encrypted))

file_to_encrypt.close()
encrypted_file.close()
file_to_decrypt = open("file2.txt", 'rb')
text = file_to_decrypt.read()
decrypted_file = open("file3.txt", 'wb')

decryptor = PKCS1_OAEP.new(Pair_key)
decrypted = decryptor.decrypt(encrypted)
decrypted_file.write(decrypted)

file_to_decrypt.close()
decrypted_file.close()
