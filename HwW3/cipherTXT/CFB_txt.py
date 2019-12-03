from Crypto.Cipher import AES
from Crypto import Random
import sys

bs = AES.block_size
mode = AES.MODE_CFB

key = 'thiscipher000001'
plaintext = sys.argv[1]
vi = Random.new().read(bs)

# enceypt
aes = AES.new(key, mode, vi)
encrypt = vi + aes.encrypt(plaintext)

# decrypt
vi = encrypt[:16]
aes = AES.new(key, mode, vi)
decrypt = aes.decrypt(encrypt[16:])

print('plaintext', plaintext)
print('encrypt', encrypt)
print('decrypt', decrypt)
