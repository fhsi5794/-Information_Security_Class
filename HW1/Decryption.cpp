// Decryption
#include <iostream>
#include <string>
using namespace std;
string caesar(string cipher, string key);
int main(int argc, char *argv[])
{
  string cipher, key, plaintext, encrypt;
  cipher=argv[1];
  key=argv[2];
  encrypt=argv[3];
  if(cipher=="caesar")
    plaintext=caesar(encrypt,key);
  cout<<"Output : "<<plaintext<<endl;
}

string caesar(string cipher, string key)
{
    string out=cipher;
    for(int i=0;i<cipher.length();i++)
    {
        out[i]=((26+cipher[i]-'A')-(key[0]-'0'))%26+'a';
    }
    return out;
}
