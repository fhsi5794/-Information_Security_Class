Information Security HW1
===
## Methods

1. Caesar cipher
2. Playfair cipher
3. Vernam proposed the autokey system
4. Row transposition
5. Rail fence cipher

## Input
使用程式：C++  
加密檔案：Encrypt.cpp  
解密檔案：Decrypt.cpp  
輸入：  
```
./Encrypt {Cipher} {Key} {Plaintext}
```
```
./Decrypt {Cipher} {Key} {Ciphertext}
```
{Cipher} : caesar ,playfair ,vernam ,row ,rail_fence

---
# Detail

## Caesar cipher


#### 加密
```string caesar(string plaint, string key)```  
將字母往後位移key位數，因不希望超出26字母範圍，故在最後要 mod 26。
```c++=38
for(int i=0;i<plaint.length();i++)
{
    out[i]=((plaint[i]-'a')+atoi(key.c_str()))%26+'A';
}
```
#### 解密
```string caesar(string cipher, string key)```  
將字母往前移ken位數，因不希望超出26字母範圍，故意開始要先加26然後再做 mod 26。  
＊程式碼基本上就是加密的反向，這邊就不貼上來了。 
#### 結果
Plaintext: doyourbestandthenletgo  
Input: ```./Encrypt caesar 5 doyourbestandthenletgo```  
Output: ```ITDTZWGJXYFSIYMJSQJYLT```  
Input: ```./Decrypt caesar 5 ITDTZWGJXYFSIYMJSQJYLT```  
Output: ```doyourbestandthenletgo```  

## Playfair cipher
#### 加密
```string playfair(string plaint, string key)```  
1. 先製作5X5矩陣，將I/J視為同字，所以這邊我將J都換成I。
```c++=57
    vector<char>table;
    for(int i=0;i<26;i++)
        if(i!=9)
            table.push_back('A'+i);
    int count=0;
    for(int i=0;i<key.length();i++)
    {
        if(key[i]=='J') key[i]='I';
         for(int j=count;j<25;j++)
             if(key[i]==table[j])
             {
                 table.erase(table.begin()+j);
                 table.insert(table.begin()+count,key[i]);
                 count++;
                 break;
             }
    }
```
5X5矩陣示意:  
<img width="500" height="200" src="https://i.imgur.com/ohurBUx.png">  
2. 兩兩一組，若欲相同字母或最後剩一個字母，則插入X。
```c++=75
    for(int i=0;i<out.length();i++)
        if(out[i]=='J')  out[i]='I';
    //add X
    for(int i=1;i<out.length();i+=2)
    {
        char c[2]={out[i-1],out[i]};
        if(c[0]==c[1])
        {
            out.insert(out.begin()+i,'X');
        }
    }
    if(out.length()%2==1)
        out.insert(out.end(),'X');
```
3. 照規則加密
* 兩字母在同一橫列：取字母右方的字，若位於最右方，則取最左字。 
```c=92
    if((cid[0]/5)==(cid[1]/5))
        {
            for(int j=0;j<2;j++)
            {
                if((cid[j]%5)==4)
                    out[i-1+j]=table[cid[j]-4];
                else
                    out[i-1+j]=table[cid[j]+1];
            }
        }
```
* 兩字母在同一直列：取字母下方的字，若位於最下方，則取最上字。
```c=102
    else if((cid[0]%5)==(cid[1]%5))
        {
            for(int j=0;j<2;j++)
            {
                if((cid[j]/5)==4)
                    out[i-1+j]=table[cid[j]-20];
                else
                    out[i-1+j]=table[cid[j]+5];
            }
        }
```
* 兩字母不在同一橫/直列：取另外兩個字母，使這四個字母成為一個矩形。
* 我這邊是去該字母同橫列，位於另一字母上/下方的字。 
```c=112
    else
        {
            int diff=(cid[0]%5)-(cid[1]%5);
            out[i-1]=table[cid[0]-diff];
            out[i]=table[cid[1]+diff];
        }
```

#### 解密
```string playfair(string cipher, string key)```  
1. 製作5X5矩陣。
2. 依規則解密
* 兩字母在同一橫列：取字母左方的字，若位於最左方，則取最右字。
* 兩字母在同一直列：取字母上方的字，若位於最上方，則取最下字。
* 兩字母不在同一橫/直列：取另外兩個字母，使這四個字母成為一個矩形。   
＊前兩項的程式就是加密的反向，而最後一項則和加密完全相同。
#### 結果
Plaintext: doyourbestandthenletgo  
Input: ```./Encrypt playfair COMP doyourbestandthenletgo```  
Output: ```IDWPQSDFTUGUFRKBHNFSDA```  
Input: ```./Decrypt playfair COMP IDWPQSDFTUGUFRKBHNFSDA```  
Output: ```doyourbestandthenletgo```  


## Vernam proposed the autokey system
#### 加密
```string vernam(string plaint, string key)```  
1. 做autokey:將部分plainteat加在key後面，key長度plainteat相同。  
<img width="500" height="200" src="https://i.imgur.com/CvKQ463.png">  
```c++=127
key.append(plaint, 0, plaint.length()-key.length());
```
2. 將兩者做XOR  
```c++=128
for(int i=0;i<key.length();i++)
	{
		out+=(char)(((int)(key[i]-'a')^(int)(plaint[i]-'a'))+'A');
	}
```
#### 解密
```string vernam(string cipher, string key)```  
將key和ciphertext一個一個字母做XOR，結果不只加到output後面，還要加到key後面，因為前面加密時使用autokey，故key後段是plaintext。  
```c++=111
for(int i=0;i<cipher.length();i++)
	{
		out+=(char)(((int)(cipher[i]-'A')^(int)(key[0]-'A'))+'A');
		key.erase(key.begin());
		key+=out[i];
	}
```

#### 結果
Plaintext: doyourbestandthenletgo  
Input: ```./Encrypt vernam TEC doyourbestandthenletgo ```  
Output: ```QK[N[JPQDSE`QTKH_MA_NK```  
Input: ```./Decrypt vernam TEC QK[N[JPQDSE`QTKH_MA_NK```  
Output: ```doyourbestandthenletgo```  

## Row transposition
#### 加密

<img width="500" height="300" src="https://i.imgur.com/flC0ZF3.png">  

```string row_trans(string plaint, string key)```  
1. 先分好列  
```c++=142
for(int i=0,j=0;i<plaint.length();i++,j++)
    {
        if(j>=key.length()) j=0;
        rows[j].push_back(plaint[i]-'a'+'A');
    }
```
2. 照key順序排  
```c++=148
for(int i=0;i<rows.size();i++)
        cipherRows[key[i]-'0'-1]=rows[i];
```
#### 解密
```string row_trans(string cipher, string key)```  
1. 計算每列長度  
```c++=131
for(int i=0;i<key.length();i++)
    {
        int add=(i<(cipherLen%key.length()))?1:0;
        strSize[key[i]-'0'-1]=cipherLen/key.length()+add;
    }
```
2. 分割出每列  
```c++=136
for(int i=0;i<key.length();i++)
    {
        rows[i].append(cipher,0,strSize[i]);
        cipher.erase(0,strSize[i]);
    }
```
3. 依照順序排好  
```c++=141
for(int i=0;i<key.length();i++)
        plainRows[i]=rows[key[i]-'0'-1];
```
#### 結果
Plaintext: doyourbestandthenletgo  
Input: ```./Encrypt  row 45362178 doyourbestandthenletgo ```  
Output: ```RTOUDGYAEDSNOTLONTBHEE```  
Input: ```./Decrypt  row 45362178 RTOUDGYAEDSNOTLONTBHEE```  
Output: ```doyourbestandthenletgo```  

## Rail fence cipher
#### 加密
```string rail_fence(string plaint, string key)```  
依照規則，碰到底網上，碰到頂往下。  

<img width="400" height="150" src="https://i.imgur.com/jJPvSFp.png">  

```c++=161
for(int i=0;i<plaint.length();)
	{
		for(int j=0;j<keyInt;j++,i++)
		{
			if(!(i<plaint.length())) break;
			rail[j].push_back(plaint[i]-'a'+'A');

		}
		for(int j=keyInt-2;j>0;j--,i++)
        {
			if(!(i<plaint.length())) break;
			rail[j].push_back(plaint[i]-'a'+'A');
		}
	}
```
#### 解密
```string rail_fence(string cipher, string key)```  
1. 先算出每列的數量  
```c++=159
for(int i=0;i<cipher.size();)
    {
        for(int j=0;j<keyInt;j++,i++)
        {
            if(i>=cipher.size()) break;
            strSize[j]++;
        }
        for(int j=keyInt-2;j>0;j--,i++)
        {
            if(i>=cipher.size()) break;
            strSize[j]++;
        }
    }
```
2. 分割  
```c++=159
for(int i=0;i<cipher.size();)
    {
        for(int j=0;j<keyInt;j++,i++)
        {
            if(i>=cipher.size()) break;
            strSize[j]++;
        }
        for(int j=keyInt-2;j>0;j--,i++)
        {
            if(i>=cipher.size()) break;
            strSize[j]++;
        }
    }
```
3. 依規則重新排好  
```c++=179
for(int i=0;i<cipherLen;)
    {
        for(int j=0;j<keyInt;j++,i++)
        {
            if(i>=cipherLen) break;
            out.push_back(rail[j][0]-'A'+'a');
            rail[j].erase(0,1);
        }
        for(int j=keyInt-2;j>0;j--,i++)
        {
            if(i>=cipherLen) break;
            out.push_back(rail[j][0]-'A'+'a');
            rail[j].erase(0,1);
        }
    }
```
#### 結果
Plaintext: doyourbestandthenletgo  
Input: ```./Encrypt rail_fence 2 doyourbestandthenletgo ```  
Output: ```DYUBSADHNEGOORETNTELTO```  
Input: ```./Decrypt rail_fence 2 DYUBSADHNEGOORETNTELTO```  
Output: ```doyourbestandthenletgo```  

---

###### tags: `Information Security` `encryption` `decryption`
