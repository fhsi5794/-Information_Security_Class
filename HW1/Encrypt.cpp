//Encryption
#include <iostream>
#include <string>
#include <vector>
using namespace std;
string caesar(string plaint, string key);
int getID(vector<char> &table, char c);
string playfair(string plaint, string key);

int main(int argc, char *argv[])
{
	string cipher, key, plaintext, encrypt;
	cipher=argv[1];
	key=argv[2];
	plaintext=argv[3];
    //trans to capital letter
    for(int i=0;i<plaintext.length();i++)
        plaintext[i]=plaintext[i]-'a'+'A';
    //encryption
	if(cipher=="caesar")
		encrypt=caesar(plaintext,key);
    else if(cipher=="playfair")
        encrypt=playfair(plaintext,key);
	cout<<"Output : "<<encrypt<<endl;
}

string caesar(string plaint, string key)
{
	string out=plaint;
	for(int i=0;i<plaint.length();i++)
	{
		out[i]=((plaint[i]-'A')+(key[0]-'0'))%26+'A';
	}
	return out;
}

int getID(vector<char> &table, char c)
{
    for(int i=0;i<table.size();i++)
        if(table[i]==c) return i;
    return -1;
}
string playfair(string plaint, string key)
{
    string out="";
    //build aphabet table
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
    //build cipher
    out=plaint;
    for(int i=0;i<out.length();i++)
        if(out[i]=='J')  out[i]='I';
    //add X
    count=0;
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
    //do cipher
    for(int i=1;i<out.length();i+=2)
    {
        int cid[2]={getID(table,out[i-1]),getID(table,out[i])};
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
        else
        {
            int diff=(cid[0]%5)-(cid[1]%5);
            out[i-1]=table[cid[0]-diff];
            out[i]=table[cid[1]+diff];
        }
    }
    
    return out;
            
}
