//Encryption
#include <iostream>
#include <string>
#include <vector>
using namespace std;
const int iniP[64] =
{
    58, 50, 42, 34, 26, 18, 10,  2,
    60, 52, 44, 36, 28, 20, 12,  4,
    62, 54, 46, 38, 30, 22, 14,  6,
    64, 56, 48, 40, 32, 24, 16,  8,
    57, 49, 41, 33, 25, 17,  9,  1,
    59, 51, 43, 35, 27, 19, 11,  3,
    61, 53, 45, 37, 29, 21, 13,  5,
    63, 55, 47, 39, 31, 23, 15,  7
};
const int fianlP[64] =
{
    40,  8, 48, 16, 56, 24, 64, 32,
    39,  7, 47, 15, 55, 23, 63, 31,
    38,  6, 46, 14, 54, 22, 62, 30,
    37,  5, 45, 13, 53, 21, 61, 29,
    36,  4, 44, 12, 52, 20, 60, 28,
    35,  3, 43, 11, 51, 19, 59, 27,
    34,  2, 42, 10, 50, 18, 58, 26,
    33,  1, 41,  9, 49, 17, 57, 25
};
const int expansion[48] =
{
    32,  1,  2,  3,  4,  5,  4,  5,
     6,  7,  8,  9,  8,  9, 10, 11,
    12, 13, 12, 13, 14, 15, 16, 17,
    16, 17, 18, 19, 20, 21, 20, 21,
    22, 23, 24, 25, 24, 25, 26, 27,
    28, 29, 28, 29, 30, 31, 32,  1
};
const int pc1[56] =
{
   57, 49, 41, 33, 25, 17,  9,
    1, 58, 50, 42, 34, 26, 18,
   10,  2, 59, 51, 43, 35, 27,
   19, 11,  3, 60, 52, 44, 36,
   63, 55, 47, 39, 31, 23, 15,
    7, 62, 54, 46, 38, 30, 22,
   14,  6, 61, 53, 45, 37, 29,
   21, 13,  5, 28, 20, 12,  4
};
const int pc2[48] =
{
   14, 17, 11, 24,  1,  5,
    3, 28, 15,  6, 21, 10,
   23, 19, 12,  4, 26,  8,
   16,  7, 27, 20, 13,  2,
   41, 52, 31, 37, 47, 55,
   30, 40, 51, 45, 33, 48,
   44, 49, 39, 56, 34, 53,
   46, 42, 50, 36, 29, 32
};
const int pBox[32] =
{
    16,  7, 20, 21, 29, 12, 28, 17,
     1, 15, 23, 26,  5, 18, 31, 10,
     2,  8, 24, 14, 32, 27,  3,  9,
    19, 13, 30,  6, 22, 11,  4, 25
};
const int DesSbox[8][4][16] =
{
   {
   {14,  4, 13,  1,  2, 15, 11,  8,  3, 10,  6, 12,  5,  9,  0,  7},
   { 0, 15,  7,  4, 14,  2, 13,  1, 10,  6, 12, 11,  9,  5,  3,  8},
   { 4,  1, 14,  8, 13,  6,  2, 11, 15, 12,  9,  7,  3, 10,  5,  0},
   {15, 12,  8,  2,  4,  9,  1,  7,  5, 11,  3, 14, 10,  0,  6, 13},
   },
 
   {
   {15,  1,  8, 14,  6, 11,  3,  4,  9,  7,  2, 13, 12,  0,  5, 10},
   { 3, 13,  4,  7, 15,  2,  8, 14, 12,  0,  1, 10,  6,  9, 11,  5},
   { 0, 14,  7, 11, 10,  4, 13,  1,  5,  8, 12,  6,  9,  3,  2, 15},
   {13,  8, 10,  1,  3, 15,  4,  2, 11,  6,  7, 12,  0,  5, 14,  9},
   },
 
   {
   {10,  0,  9, 14,  6,  3, 15,  5,  1, 13, 12,  7, 11,  4,  2,  8},
   {13,  7,  0,  9,  3,  4,  6, 10,  2,  8,  5, 14, 12, 11, 15,  1},
   {13,  6,  4,  9,  8, 15,  3,  0, 11,  1,  2, 12,  5, 10, 14,  7},
   { 1, 10, 13,  0,  6,  9,  8,  7,  4, 15, 14,  3, 11,  5,  2, 12},
   },
 
   {
   { 7, 13, 14,  3,  0,  6,  9, 10,  1,  2,  8,  5, 11, 12,  4, 15},
   {13,  8, 11,  5,  6, 15,  0,  3,  4,  7,  2, 12,  1, 10, 14,  9},
   {10,  6,  9,  0, 12, 11,  7, 13, 15,  1,  3, 14,  5,  2,  8,  4},
   { 3, 15,  0,  6, 10,  1, 13,  8,  9,  4,  5, 11, 12,  7,  2, 14},
   },
 
   {
   { 2, 12,  4,  1,  7, 10, 11,  6,  8,  5,  3, 15, 13,  0, 14,  9},
   {14, 11,  2, 12,  4,  7, 13,  1,  5,  0, 15, 10,  3,  9,  8,  6},
   { 4,  2,  1, 11, 10, 13,  7,  8, 15,  9, 12,  5,  6,  3,  0, 14},
   {11,  8, 12,  7,  1, 14,  2, 13,  6, 15,  0,  9, 10,  4,  5,  3},
   },
 
   {
   {12,  1, 10, 15,  9,  2,  6,  8,  0, 13,  3,  4, 14,  7,  5, 11},
   {10, 15,  4,  2,  7, 12,  9,  5,  6,  1, 13, 14,  0, 11,  3,  8},
   { 9, 14, 15,  5,  2,  8, 12,  3,  7,  0,  4, 10,  1, 13, 11,  6},
   { 4,  3,  2, 12,  9,  5, 15, 10, 11, 14,  1,  7,  6,  0,  8, 13},
   },
 
   {
   { 4, 11,  2, 14, 15,  0,  8, 13,  3, 12,  9,  7,  5, 10,  6,  1},
   {13,  0, 11,  7,  4,  9,  1, 10, 14,  3,  5, 12,  2, 15,  8,  6},
   { 1,  4, 11, 13, 12,  3,  7, 14, 10, 15,  6,  8,  0,  5,  9,  2},
   { 6, 11, 13,  8,  1,  4, 10,  7,  9,  5,  0, 15, 14,  2,  3, 12},
   },
 
   {
   {13,  2,  8,  4,  6, 15, 11,  1, 10,  9,  3, 14,  5,  0, 12,  7},
   { 1, 15, 13,  8, 10,  3,  7,  4, 12,  5,  6, 11,  0, 14,  9,  2},
   { 7, 11,  4,  1,  9, 12, 14,  2,  0,  6, 10, 13, 15,  3,  5,  8},
   { 2,  1, 14,  7,  4, 10,  8, 13, 15, 12,  9,  0,  3,  5,  6, 11},
   },
};

string toBinary(string str);
string toBinary(int n);
string toHex(string str,int flag);  //0 lowercase, 1 capital
string permu(string str,const int table[],int size);
string doXOR(string str0,string str1);
string rotateBit(string str, int movebit);
string func(string rstr, string key);
int main(int argc, const char * argv[])
{
    //initialize
    string key, plaintext, encrypt;
    key=argv[1];
    plaintext=argv[2];
    key.erase(0,2);
    plaintext.erase(0,2);
    key=toBinary(key);
    plaintext=toBinary(plaintext);
    encrypt=permu(plaintext, iniP, 64);
    key=permu(key,pc1,56);
    string lstr(encrypt,0,32),rstr(encrypt,32,32),cstr(key,0,28),dstr(key,28,28);
    string keys[16];
    int count=1;
    //do key transform
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
    //into round
    count=1;
    while(count<=16)
    {
        string temp=lstr;
        lstr=rstr;
        rstr=doXOR(temp, func(rstr,keys[count-1]));
        count++;
    }
    encrypt=rstr+lstr;
    encrypt="0x"+toHex(permu(encrypt, fianlP, 64),1);
    
    cout<<encrypt<<endl;
    return 0;
}

string toBinary(string str)
{
    string biStr="";
    for(int i=0;i<str.length();i++)
    {
        if(str[i]=='0') biStr+="0000";
        else if (str[i]=='1') biStr+="0001";
        else if (str[i]=='2') biStr+="0010";
        else if (str[i]=='3') biStr+="0011";
        else if (str[i]=='4') biStr+="0100";
        else if (str[i]=='5') biStr+="0101";
        else if (str[i]=='6') biStr+="0110";
        else if (str[i]=='7') biStr+="0111";
        else if (str[i]=='8') biStr+="1000";
        else if (str[i]=='9') biStr+="1001";
        else if ((str[i]=='a')||(str[i]=='A')) biStr+="1010";
        else if ((str[i]=='b')||(str[i]=='B')) biStr+="1011";
        else if ((str[i]=='c')||(str[i]=='C')) biStr+="1100";
        else if ((str[i]=='d')||(str[i]=='D')) biStr+="1101";
        else if ((str[i]=='e')||(str[i]=='E')) biStr+="1110";
        else if ((str[i]=='f')||(str[i]=='F')) biStr+="1111";
    }
    return biStr;
}
string toBinary(int n)
{
    string biStr="";
    if(n==0) biStr+="0000";
    else if (n==1) biStr+="0001";
    else if (n==2) biStr+="0010";
    else if (n==3) biStr+="0011";
    else if (n==4) biStr+="0100";
    else if (n==5) biStr+="0101";
    else if (n==6) biStr+="0110";
    else if (n==7) biStr+="0111";
    else if (n==8) biStr+="1000";
    else if (n==9) biStr+="1001";
    else if (n==10) biStr+="1010";
    else if (n==11) biStr+="1011";
    else if (n==12) biStr+="1100";
    else if (n==13) biStr+="1101";
    else if (n==14) biStr+="1110";
    else if (n==15) biStr+="1111";
    return biStr;
}
string toHex(string str,int flag)
{
    string hStr="";
    if(flag==0)
    {
        while(str.length()!=0)
        {
            string temp(str,0,4);
            if(temp=="0000") hStr+="0";
            else if(temp=="0001") hStr+="1";
            else if(temp=="0010") hStr+="2";
            else if(temp=="0011") hStr+="3";
            else if(temp=="0100") hStr+="4";
            else if(temp=="0101") hStr+="5";
            else if(temp=="0110") hStr+="6";
            else if(temp=="0111") hStr+="7";
            else if(temp=="1000") hStr+="8";
            else if(temp=="1001") hStr+="9";
            else if(temp=="1010") hStr+="a";
            else if(temp=="1011") hStr+="b";
            else if(temp=="1100") hStr+="c";
            else if(temp=="1101") hStr+="d";
            else if(temp=="1110") hStr+="e";
            else if(temp=="1111") hStr+="f";
            str.erase(0,4);
        }
        return hStr;
    }
    while(str.length()!=0)
    {
        string temp(str,0,4);
        if(temp=="0000") hStr+="0";
        else if(temp=="0001") hStr+="1";
        else if(temp=="0010") hStr+="2";
        else if(temp=="0011") hStr+="3";
        else if(temp=="0100") hStr+="4";
        else if(temp=="0101") hStr+="5";
        else if(temp=="0110") hStr+="6";
        else if(temp=="0111") hStr+="7";
        else if(temp=="1000") hStr+="8";
        else if(temp=="1001") hStr+="9";
        else if(temp=="1010") hStr+="A";
        else if(temp=="1011") hStr+="B";
        else if(temp=="1100") hStr+="C";
        else if(temp=="1101") hStr+="D";
        else if(temp=="1110") hStr+="E";
        else if(temp=="1111") hStr+="F";
        str.erase(0,4);
    }
    return hStr;
}

string permu(string str,const int table[],int size)
{
    string result(size,'0');
    for(int i=0;i<size;i++)
        result[i]=str[table[i]-1];
    return result;
}

string doXOR(string str0,string str1)
{
    string result;
    for(int i=0;i<str0.length();i++)
        if(str0[i]==str1[i])
            result+='0';
        else
            result+='1';
    return result;
}

string rotateBit(string str, int movebit)
{
    string temp(str,0,movebit);
    str.erase(0,movebit);
    str+=temp;
    return str;
}

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
