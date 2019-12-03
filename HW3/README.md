Information Security HW3
===
## Methods

Advanced Encryption Standard (AES)

## Input
使用環境、程式：Linux  Python3  
加密檔案：encrypt.py  
解密檔案：decrypt.py  
Mode : ECB, CBC, CFB  
輸入：  
```
encrypt.py {Mode} {Key} {File}
```
```
decrypt.py {Mode} {Key} {File}
```
---
# Detail
### Image Processing
輸入、輸出的圖片是PNG格式，中間是使用PPM格式來處理，在此使用PIL(Python Imaging Library)，將其在PPM和PNG之間轉換。  
```python=1
from PIL import Image, ImageFile
```
```python=18
img=Image.open(photo)
img.save('input_decrypt.ppm')
```
```python=55
ImageFile.LOAD_TRUNCATED_IMAGES = True
outImg=Image.open('decrypt.ppm')
outImg.save('decrypt.png','png')
```

## Encryption
解密方法雷同，故不復述。  
使用Crypto.Cipher來做不同模式的AES。  

```python=3
from Crypto.Cipher import AES
```
### Different Mode
建立新的AES。  
```python=28
if(mode == 'ECB'):
    encryption = AES.new(pad_key(key),AES.MODE_ECB)
elif(mode == 'CBC'):
    encryption = AES.new(pad_key(key),AES.MODE_CBC,iv)
elif(mode == 'CFB'):
    encryption = AES.new(pad_key(key),AES.MODE_CFB,iv)
```
### Initialization Vector
此用隨機方法產生。  
```python=7
iv = Random.new().read(bs)
```
IV(Initialization Vector)用於CBC和CFB，作用如下圖：  
<img width="600" height="450" src="https://i.imgur.com/hB3LSfL.png">  
[picture source1](https://en.wikipedia.org/wiki/Block_cipher_mode_of_operation#Cipher_Block_Chaining_(CBC))  
[picture source2](https://en.wikipedia.org/wiki/Block_cipher_mode_of_operation#Cipher_Feedback_(CFB))  
### Padding
AES的key要為一個block長度，長度不夠則補0。  
```python=8
pad_key = lambda s: s + (bs-len(s))*"\0"
```
Plaintext因為是分block加密，所以長度需為block長度倍數，若不夠則需padding。  
```python=9
pad_txt = lambda s: s + bytes([(bs - len(s) % bs)]) * (bs - len(s) % bs)
```
此用PKCS7（公鑰密碼學標準第 7 號）:  
每個填充字節的值是用於填充的字節數，即是說，若需要填充 N 個字節，則每個填充字節值都是 N 。 填充的字節數取決於算法可以處理的最小數據塊的字節數量。  
例：下例中，塊大小為 8 字節，需要填充 4 字節。  
```... | DD DD DD DD DD DD DD DD | DD DD DD DD 04 04 04 04 |```  
[reference](https://zh.wikipedia.org/wiki/填充_(密码学)#PKCS7_（公钥密码学标准第_7_号）)  

### Encrypt
將plaintext分段(block)加密。  
```python=41
turns = math.ceil(total_bytes / 16)
index=0
while(index<turns*16):
    one_block_text = plaintext[index:index+16]
    fout.write(encryption.encrypt(one_block_text))
    index=index+16
```
## Result
encrypt:  
```python3 encrypt.py CBC 0123456789abc ./png/0.png```  

decrypt:  
```python3 decrypt.py CBC 0123456789abc encrypt.png```  

|  | encrypt | decrypt |
| -------- | -------- | -------- |
| input(picture)     |<img width="100" height="100" src="https://i.imgur.com/S5eZnV2.jpg"> |<img width="100" height="100" src="https://i.imgur.com/0P3bFiI.jpg"> 
|
| output(picture)     | <img width="100" height="100" src="https://i.imgur.com/0P3bFiI.jpg">      | <img width="100" height="100" src="https://i.imgur.com/bvEqYEn.jpg">     |

## 遇到困難與心得
先是做了純字串的加解密，很快就做出來了，但因為以前沒有處理過圖片，這部分反而卡了很久。  

---

###### tags: `Information Security` `AES`  `ECB`  `CBC` `CFB` `encryption` `decryption`


