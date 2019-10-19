Information Security HW2
===
## Methods

Data Encryption Standard (DES)

## Input
使用環境、程式：Linux  C++  
加密檔案：EncryptDES.cpp  
解密檔案：DecryptDES.cpp  
輸入：  
```
./EncryptDES {Key} {Plaintext}
```
```
./DecryptDES {Key} {Ciphertext}
```
---
# Detail
DES 是 Feistel network ，故加密、解密只差在 key schedule 的部分。
## Functions
### Permutation
依照對應 table 提供的順序重新排列原本的 bits 。   

<img width="400" height="150" src="https://i.imgur.com/7UA0Efp.png">  

```c++=276
string permu(string str,const int table[],int size)
{
    string result(size,'0');
    for(int i=0;i<size;i++)
        result[i]=str[table[i]-1];
    return result;
}
```

### F-Function
DES的主要核心。
1. 做 expantion 。 **(line 306)**
2. 將 R 和 key 做 XOR 。 **(line 307)**
3. 做 S-box substitution 。 **(line 308~318)**
* 把字串分成八份。 **(line 309~313)**
* 取每組的頭尾 bit 為 row ，中間為 colum ，對應到Sbox的值換成二進制(4 bit)，串接成結果。 **(line 314~318)**
<img width="400" height="250" src="https://i.imgur.com/duHV5pS.png">  

4. 做 permute 。  **(line 319)**

```c++=303
string func(string rstr, string key)
{
    string result="";
    result=permu(rstr, expansion, 48);
    result=doXOR(result, key);
    string sstr[8];
    for(int i=0;i<8;i++)
    {
        sstr[i].append(result,0,6);
        result.erase(0,6);
    }
    for(int i=0;i<8;i++)
    {
        sstr[i]=toBinary(DesSbox[i][2*(sstr[i][0]-'0')+(sstr[i][5]-'0')][8*(sstr[i][1]-'0')+4*(sstr[i][2]-'0')+2*(sstr[i][3]-'0')+(sstr[i][4]-'0')]);
        result+=sstr[i];
    }
    result=permu(result, pBox, 32);
    return result;
}
```

## 加密
### Key Schedule 
1. 做 Permutation。
2. 將key分成兩半，左半為cstr、右半為dstr。
3. transform 1 ~ transform 16：
* 做 transform 1, 2, 9, 16 時，cstr、dstr 各往左移 1 bit；其他 transform 則往右移 2 bit 。
* 合併做 Permutation 存入 keys[] ，待候用。
<img width="450" height="250" src="https://i.imgur.com/K5GDXRx.png">

```c++=148
while(count<=16)
    {
        if((count==1)||(count==2)||(count==9)||(count==16))
        {
            cstr=rotateBit(cstr, 1);
            dstr=rotateBit(dstr, 1);
        }
        else
        {
            cstr=rotateBit(cstr, 2);
            dstr=rotateBit(dstr, 2);
        }
        keys[count-1]=permu((cstr+dstr),pc2,48);
        count++;
    }
``` 

### Feistel Network
1. 做 Permutation。
2. 將key分成兩半，左半為lstr、右半為rstr。
4. round 1 ~ round 16，產生新的 lstr、rstr：
* 新 lstr = 舊 rstr。
* 新 rstr = ( **舊 lstr** ) XOR ( **F-Function( 舊 rstr, keys[i] )** )。
<img width="450" height="250" src="https://i.imgur.com/qwFcC65.png">  

5. 合併做 Permutation 即為加密結果。
```c++=148
while(count<=16)
    {
        if((count==1)||(count==2)||(count==9)||(count==16))
        {
            cstr=rotateBit(cstr, 1);
            dstr=rotateBit(dstr, 1);
        }
        else
        {
            cstr=rotateBit(cstr, 2);
            dstr=rotateBit(dstr, 2);
        }
        keys[count-1]=permu((cstr+dstr),pc2,48);
        count++;
    }
``` 
## 解密
與加密作法幾乎都一樣，只差在下述一個地方：
在 f-function 時，將 transformed keys 反向輸入。
```c++=171
rstr=doXOR(temp, func(rstr,keys[17-count-1]));
```

## 結果
Plaintext: 0xabcdef0123456789  

Input: ```./EncryptDES 0xafafafafafafafaf 0xabcdef0123456789 ```  
Output: ```0x4C30FC30FB2B0BFF```  

Input: ```./DecryptDES 0xafafafafafafafaf 0x4C30FC30FB2B0BFF```  
Output: ```0xabcdef0123456789```  

<img width="600" height="75" src="https://i.imgur.com/dHtPdxd.png">  

## 遇到困難與心得
因為過程基本上都是查表，我覺得不算特別困難，但正因如此，我很佩服做出這個加密法的人，能利用簡單的過程得到不容易被破解的結果。

---

###### tags: `Information Security` `DES` `encryption` `decryption`

