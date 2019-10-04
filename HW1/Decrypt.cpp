//Decryption
#include <iostream>
#include <string>
#include<vector>
#include <stdlib.h>     /* atoi */
using namespace std;
string caesar(string cipher, string key);
int getID(vector<char> &table, char c);
string playfair(string cipher, string key);
string vernam(string cipher, string key);
string row_trans(string cipher, string key);
string rail_fence(string cipher, string key);
int main(int argc, char *argv[])
{
	string cipher, key, plaintext, encrypt;
	cipher=argv[1];
	key=argv[2];
	encrypt=argv[3];
    //Decryption
	if(cipher=="caesar")
		plaintext=caesar(encrypt,key);
    else if(cipher=="playfair")
        plaintext=playfair(encrypt,key);
    else if(cipher=="vernam")
        plaintext=vernam(encrypt,key);
    else if(cipher=="row")
        plaintext=row_trans(encrypt,key);
    else if(cipher=="rail_fence")
        plaintext=rail_fence(encrypt,key);
	
	cout<<"Output : "<<plaintext<<endl;
}

string caesar(string cipher, string key)
{
	string out=cipher;
	for(int i=0;i<cipher.length();i++)
	{
		out[i]=((26+cipher[i]-'A')-atoi(key.c_str()))%26+'a';
	}
	return out;
}

int getID(vector<char> &table, char c)
{
    for(int i=0;i<table.size();i++)
        if(table[i]==c) return i;
    return -1;
}
string playfair(string cipher, string key)
{
    string out=cipher;
	for(int i=0;i<out.length();i++)
		out[i]=out[i]-'A'+'a';
    //build aphabet table
    vector<char>table;
    for(int i=0;i<26;i++)
        if(i!=9)
            table.push_back('a'+i);
    int count=0;
    for(int i=0;i<key.length();i++)
    {
        key[i]=key[i]-'A'+'a';
        if(key[i]=='j') key[i]='i';
         for(int j=count;j<25;j++)
             if(key[i]==table[j])
             {
                 table.erase(table.begin()+j);
                 table.insert(table.begin()+count,key[i]);
                 count++;
                 break;
             }
    }
    //decryption
    for(int i=1;i<out.length();i+=2)
    {
        int cid[2]={getID(table,out[i-1]),getID(table,out[i])};
        if((cid[0]/5)==(cid[1]/5))
        {
            for(int j=0;j<2;j++)
            {
                if((cid[j]%5)==0)
                    out[i-1+j]=table[cid[j]+4];
                else
                    out[i-1+j]=table[cid[j]-1];
            }
        }
        else if((cid[0]%5)==(cid[1]%5))
        {
            for(int j=0;j<2;j++)
            {
                if((cid[j]/5)==0)
                    out[i-1+j]=table[cid[j]+20];
                else
                    out[i-1+j]=table[cid[j]-5];
            }
        }
        else
        {
            int diff=(cid[0]%5)-(cid[1]%5);
            out[i-1]=table[cid[0]-diff];
            out[i]=table[cid[1]+diff];
        }
    }
	return out;
}
    
string vernam(string cipher, string key)
{
	string out="";
	for(int i=0;i<cipher.length();i++)
	{
		out+=(char)(((int)(cipher[i]-'A')^(int)(key[0]-'A'))+'A');
		key.erase(key.begin());
		key+=out[i];
	}
    for(int i=0;i<out.length();i++)
        out[i]=out[i]-'A'+'a';
	return out; 
}

string row_trans(string cipher, string key)
{
    string out="";
    vector<string>rows;
    rows.resize(key.length());
    vector<string>plainRows;
    plainRows.resize(key.length());
    int strSize[key.length()];
    int cipherLen=cipher.length();
    for(int i=0;i<key.length();i++)
    {
        int add=(i<(cipherLen%key.length()))?1:0;
        strSize[key[i]-'0'-1]=cipherLen/key.length()+add;
    }
    for(int i=0;i<key.length();i++)
    {
        rows[i].append(cipher,0,strSize[i]);
        cipher.erase(0,strSize[i]);
    }
    for(int i=0;i<key.length();i++)
        plainRows[i]=rows[key[i]-'0'-1];
    for(int i=0;i<cipherLen;i++)
        out+=plainRows[i%key.length()][i/key.length()]-'A'+'a';
    return out;
}

string rail_fence(string cipher, string key)
{
	string out="";
    int cipherLen=cipher.length();
	int keyInt= atoi(key.c_str());
    int strSize[keyInt];
	vector<string> rail;
	rail.resize(keyInt);
    
    for(int i=0;i<keyInt;i++)
        strSize[i]=0;
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
    
    for(int i=0;i<keyInt;i++)
    {
        rail[i].append(cipher,0,strSize[i]);
        cipher.erase(0,strSize[i]);
    }
    
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
	return out; 
}
