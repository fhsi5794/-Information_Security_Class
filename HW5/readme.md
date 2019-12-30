Information Security HW5
===
## Methods
DSA (Digital Signature Algorithm)  

## Input
使用環境、程式：Linux  Python3  
檔案：DSA.py  
輸入：  
```
python3 DSA.py 
```
---
# DSA
## 0. Message Hashing
雜湊訊息（hashing message) : h  
此用SHA-1  

<img width="550" height="350" src="https://upload.wikimedia.org/wikipedia/commons/thumb/e/e2/SHA-1.svg/600px-SHA-1.svg.png">  

[SHA-1 - 维基百科](https://zh.wikipedia.org/wiki/SHA-1)  

## 1. Key Generation
私人鑰匙(private key) : d  
```
d : { 0 < d < q }
```  
公共鑰匙(public key) : key(p, q, α, β)  
```
p : 2的1023~1024次方中的質數
q : 2的159~160次方中的質數
==> p, q 滿足 { p = kq + 1 }

α : 
    1. 選一h：{ 1 < h < (p−1) }
    2. α = h ^ ( ( p − 1 ) / q ) mod p
    3. α ^ q ≡ 1 ( mod p )
    
β : β = α ^ d mod p 
```
## 2. Signature Generation
簽名(signature) ：sig(r, s)  
```
1. 生成 k : { 0 < k < q}
2. r = α ^ k mod p mod q
3. s = ( h + d * r) * k^(-1) mod q 
```  
註：  
k^(-1) 為k的模反元素（modular multiplicative inverse），可用擴展歐幾里得算法（Extended Euclidean algorithm）求得。  

[我的求模反元素的code](https://github.com/fhsi5794/Information_Security_Class/blob/master/HW5/ModIeverse.py)
## 3. Signature Verification
Given: hashing message h, signature (r, s) and public key (p, q, α, β)  
Verify:
```
1. w = s ^ (-1) mod q
2. u1 = w * h mod q
3. u2 = w *r mod q
4. v = (α ^ u1 * β ^ u2) mod p mod q

if { v ≡ r mod q } ==> signature is valid
if { v ≠ r mod q } ==> signature is invalid
```
## Result
```python3 DSA.py ```  

<img width="850" height="300" src="https://i.imgur.com/1jwuFgy.png">  



## 遇到困難與心得
Python很好用。  

---

###### tags: `Information Security` `DSA` `encryption` `decryption`


