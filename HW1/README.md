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
## Detail

### Caesar cipher


#### 加密：將字母往後位移key位數，因不希望超出26字母範圍，故在最後要 mod 26。
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
#### 解密：將字母往前移ken位數，因不希望超出26字母範圍，故意開始要先加26然後再做 mod 26。
```c++=17
string caesar(string cipher, string key)
{
	string out=cipher;
	for(int i=0;i<cipher.length();i++)
	{
		out[i]=((26+cipher[i]-'A')-(key[0]-'0'))%26+'a';
	}
	return out;
}
```
#### 結果
<img width="1000" height="100" src="https://i.imgur.com/XqUE0Hw.png">

### Playfair cipher

### Vernam proposed the autokey system

### Row transposition

### Rail fence cipher

---

###### tags: `Information Security` `encryption` `decryption`
