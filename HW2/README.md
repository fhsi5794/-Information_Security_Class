Information Security HW1
===
## Methods

1. Caesar cipher
2. Playfair cipher
3. Vernam proposed the autokey system
4. Row transposition
5. Rail fence cipher

## Input
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
將字母往後位移key位數，因不希望超出26字母範圍，故在最後要 mod 26。
```c++=17
string caesar(string plaint, string key)
{
	string out=plaint;
	for(int i=0;i<plaint.length();i++)
	{
		out[i]=((plaint[i]-'a')+(key[0]-'0'))%26+'A';
	}
	return out;
}
```
#### 解密
將字母往前移ken位數，因不希望超出26字母範圍，故意開始要先加26然後再做 mod 26。  
＊程式碼基本上就是加密的反向，這邊就不貼上來了。 
#### 結果
<img width="1000" height="100" src="https://i.imgur.com/XqUE0Hw.png">

## Playfair cipher
#### 加密
1. 先製作5X5矩陣，將I/J視為同字，所以這邊我將J都換成I。
```c++=46
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
```c++=70
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
```c=84
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
```c=94
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
```c=104
    else
        {
            int dis=(cid[0]%5)-(cid[1]%5);
            out[i-1]=table[cid[0]-dis];
            out[i]=table[cid[1]+dis];
        }
```

#### 解密
1. 製作5X5矩陣。
2. 依規則解密
* 兩字母在同一橫列：取字母左方的字，若位於最左方，則取最右字。
* 兩字母在同一直列：取字母上方的字，若位於最上方，則取最下字。
* 兩字母不在同一橫/直列：取另外兩個字母，使這四個字母成為一個矩形。   
＊前兩項的程式就是加密的反向，而最後一項則和加密完全相同。
## Vernam proposed the autokey system
#### 加密
#### 解密

## Row transposition
#### 加密
#### 解密

## Rail fence cipher
#### 加密
#### 解密

---

###### tags: `Information Security` `encryption` `decryption`
