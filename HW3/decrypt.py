from PIL import Image, ImageFile
from Crypto import Random
from Crypto.Cipher import AES
import math, sys, os

bs = AES.block_size
iv = Random.new().read(bs)
pad_key = lambda s: s + (bs-len(s))*"\0"
pad_txt = lambda s: s + bytes([(bs - len(s) % bs)]) * (bs - len(s) % bs)
unpad = lambda s : s[0:-ord(s[-1])]

#read command
mode = sys.argv[1]
key = sys.argv[2]
photo = sys.argv[3]

#png to ppm
img=Image.open(photo)
img.save('input_decrypt.ppm')
fin=open('input_decrypt.ppm','rb')
fout=open('decrypt.ppm','wb')
for i in range (3):
    fout.write(fin.readline())
bs=16
total_bytes = img.width * img.height * 3

#mode
if(mode == 'ECB'):
    encryption = AES.new(pad_key(key),AES.MODE_ECB)
elif(mode == 'CBC'):
    encryption = AES.new(pad_key(key),AES.MODE_CBC,iv)
elif(mode == 'CFB'):
    encryption = AES.new(pad_key(key),AES.MODE_CFB,iv)
else:
    print("not right mode")
    sys.exit()
    
#padding
plaintext=fin.read()
plaintext=pad_txt(plaintext)

#cut block(16 bytes) and encrypt
turns = math.ceil(total_bytes / 16)
index=0
while(index<turns*16):
    one_block_text = plaintext[index:index+16]
    fout.write(encryption.decrypt(one_block_text))
    index=index+16

#close files
fin.close()
fout.close()

#ppm to png
ImageFile.LOAD_TRUNCATED_IMAGES = True
outImg=Image.open('decrypt.ppm')
outImg.save('decrypt.png','png')

#remove ppm files
os.remove('input_decrypt.ppm')
os.remove('decrypt.ppm')
