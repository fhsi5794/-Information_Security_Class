//Decryption
#include <iostream>
#include <string>
#include<vector>
using namespace std;
string caesar(string cipher, string key);
int getID(vector<char> &table, char c);
string playfair(string cipher, string key);
int main(int argc, char *argv[])
{
	string cipher, key, plaintext, encrypt;
	cipher=argv[1];
	key=argv[2];
	encrypt=argv[3];
    //trans to lowercase letter
    for(int i=0;i<encrypt.length();i++)
        encrypt[i]=encrypt[i]-'A'+'a';
    //Decryption
	if(cipher=="caesar")
		plaintext=caesar(encrypt,key);
    else if(cipher=="playfair")
        plaintext=playfair(encrypt,key);
	cout<<"Output : "<<plaintext<<endl;
}

string caesar(string cipher, string key)
{
	string out=cipher;
	for(int i=0;i<cipher.length();i++)
	{
		out[i]=((26+cipher[i]-'a')-(key[0]-'0'))%26+'a';
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
    //build aphabet table
    vector<char>table;
    for(int i=0;i<26;i++)
        if(i!=9)
            table.push_back('a'+i);
    int count=0;
    for(int i=0;i<key.length();i++)
    {
        key[i]=key[i]-'A'+'a';
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
