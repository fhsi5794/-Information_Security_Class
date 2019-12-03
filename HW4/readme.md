Information Security HW4
===
## Methods

Advanced Encryption Standard (AES)

## Input
使用環境、程式：Linux  Python3  
檔案：RSA.py  
Mode : num, text  
輸入：  
```
RSA.py {Mode} {Plaintext} {p} {q}
```
---
# RSA
給一個公共鑰匙(public key):key(n,e)  
和一個私人鑰匙(private key):d  

產生密文y、明文x： 
<img width="234" height="63" src="https://i.imgur.com/N4ncdb9.png">  
# Detail
本程式有兩種mode，差異在於明文的輸入。  
num：明文為純數字輸入，直接對此數字進行加密。
text：明文為一段字串，加密時會轉成ACII，個別對其加密。  
## Variables
根據給定的質數p和質數q產生需要用到的變數：n, φ(n), e, d  
1. n = p*q  
```python=8
n=p*q
```
3. φ(n) = (p-1)(q-1)  
```python=10
phi=(p-1)*(q-1)
```
4. e => { 0<e<φ(n) AND gcd(e,φ(n))=1 }
```python=12
e=0
for i in range(2,phi):
    if gcd(i,phi)==1 :
        e=i
        break
```
5. d => d*e≡1(mod φ(n))
```python=18
d = 0
for i in range(2,phi):
    if (e*i%phi)==1 :
        d=i
        break
```

## Encryption & Decryption
<img width="234" height="63" src="https://i.imgur.com/N4ncdb9.png">  

### Number Mode
Encryption：Plaintext＾e mod n  
Decryption：ciphertext＾d mod n  
```python=25
if mode=="num" :
    plain=int(plain)
    cipher=pow(plain, e, n )
    decrypted=pow(cipher, d, n)
```

### Text Mode
Encryption：Plaintext[i]＾e mod n  
對Plaintext每個字（轉成ACII）進行加密動作，然後存到list裡面供解密時使用。  
```python=32
    for i in range(len(plain)):
        cipherList.append(pow(ord(plain[i]),e,n))
        cipher+=str(cipherList[i])
```
Decryption：cipherList[i]＾d mod n  
將list中的元素進行解密，然後轉成字元(chr)。
```python=36
    for i in range(len(plain)):
        decrypted+=chr(pow(cipherList[i],d,n))
```

## Result
```python3 RSA.py num 4 11 3```  
```python3 RSA.py num 3320 2999 2663```  
```python3 RSA.py text hello  2999 3571```  

<img width="650" height="700" src="https://i.imgur.com/EwJQoAC.png">  



## 遇到困難與心得
Python做大數運算真的很方便。  

---

###### tags: `Information Security` `RSA` `encryption` `decryption`


