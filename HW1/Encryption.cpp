// Encryption
#include <iostream>
#include <string>
using namespace std;
string caesar(string plaint, string key);
int main(int argc, char *argv[])
{
  string cipher, key, plaintext, encrypt;
  cipher=argv[1];
  key=argv[2];
  plaintext=argv[3];
  if(cipher=="caesar")
    encrypt=caesar(plaintext,key);
  cout<<"Output : "<<encrypt<<endl;
}

string caesar(string plaint, string key)
{
    string out=plaint;
    for(int i=0;i<plaint.length();i++)
    {
        out[i]=((plaint[i]-'a')+(key[0]-'0'))%26+'A';
    }
    return out;
}
