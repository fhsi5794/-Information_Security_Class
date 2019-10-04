//Encryption
#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>     /* atoi */
using namespace std;
string caesar(string plaint, string key);
int getID(vector<char> &table, char c);
string playfair(string plaint, string key);
string vernam(string plaint, string key);
string row_trans(string plaint, string key);
string rail_fence(string plaint, string key);

int main(int argc, char *argv[])
{
	string cipher, key, plaintext, encrypt;
	cipher=argv[1];
	key=argv[2];
	plaintext=argv[3];
    //encryption
	if(cipher=="caesar")
		encrypt=caesar(plaintext,key);
    else if(cipher=="playfair")
        encrypt=playfair(plaintext,key);
    else if(cipher=="vernam")
        encrypt=vernam(plaintext,key);
    else if(cipher=="row")
        encrypt=row_trans(plaintext,key);
    else if(cipher=="rail_fence")
        encrypt=rail_fence(plaintext,key);
	
	cout<<"Output : "<<encrypt<<endl;
}

string caesar(string plaint, string key)
{
	string out=plaint;
	for(int i=0;i<plaint.length();i++)
	{
		out[i]=((plaint[i]-'a')+atoi(key.c_str()))%26+'A';
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
    string out=plaint;
	for(int i=0;i<out.length();i++)
		out[i]=out[i]-'a'+'A';
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

string vernam(string plaint, string key)
{
	string out="";
	for(int i=0;i<key.length();i++)
		key[i]=key[i]-'A'+'a';
	key.append(plaint, 0, plaint.length()-key.length());
	for(int i=0;i<key.length();i++)
	{
		out+=(char)(((int)(key[i]-'a')^(int)(plaint[i]-'a'))+'A');
	}
	return out; 
}

string row_trans(string plaint, string key)
{
    string out="";
    vector<string>rows;
    rows.resize(key.length());
    vector<string>cipherRows;
    cipherRows.resize(key.length());
    for(int i=0,j=0;i<plaint.length();i++,j++)
    {
        if(j>=key.length()) j=0;
        rows[j].push_back(plaint[i]-'a'+'A');
    }
    
    for(int i=0;i<rows.size();i++)
        cipherRows[key[i]-'0'-1]=rows[i];
    for(int i=0;i<cipherRows.size();i++)
        out.append(cipherRows[i]);
    return out;
}

string rail_fence(string plaint, string key)
{
	string out="";
	int keyInt= atoi(key.c_str());
	vector<string> rail;
	rail.resize(keyInt);
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
	for(int i=0;i<rail.size();i++)
		out.append(rail[i]);
	return out; 
}
