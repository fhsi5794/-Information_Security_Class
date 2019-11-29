from Crypto.Cipher import AES
from Crypto import Random
import sys

bs = AES.block_size
mode = AES.MODE_ECB
pad_key = lambda s: s + (bs-len(s))*"\0"
pad_txt = lambda s: s + (bs - len(s) % bs) * chr(bs - len(s) % bs)
unpad = lambda s : s[0:-ord(s[-1])]

key = '123abc'
text = sys.argv[1]

#encrypt
aes = AES.new(pad_key(key), mode)
encrypt = aes.encrypt(str.encode(pad_txt(text)))

#decrypt
aes = AES.new(pad_key(key), mode)
decrypt = str(aes.decrypt(encrypt),encoding='utf-8')
decrypt=unpad(decrypt)

print('plaintext', text)
print('encrypt', encrypt)
print('decrypt', decrypt)
