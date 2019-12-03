from math import gcd
import sys

mode=sys.argv[1]
plain=sys.argv[2]
p=int(sys.argv[3])
q=int(sys.argv[4])
n=p*q
# φ(n) = (p-1)(q-1)
phi=(p-1)*(q-1)
# 0<e<φ(n) and gcd(e,φ(n))=1
e=0
for i in range(2,phi):
    if gcd(i,phi)==1 :
        e=i
        break
# d*e≡1 (mod φ(N))
d = 0
for i in range(2,phi):
    if (e*i%phi)==1 :
        d=i
        break
# different mode's cipher and decrypt
if mode=="num" :
    plain=int(plain)
    cipher=pow(plain, e, n )
    decrypted=pow(cipher, d, n)
elif mode=="text" :
    cipher=""
    decrypted=""
    cipherList=[]
    for i in range(len(plain)):
        cipherList.append(pow(ord(plain[i]),e,n))
        cipher+=str(cipherList[i])

    for i in range(len(plain)):
        decrypted+=chr(pow(cipherList[i],d,n))


print("--------- Variables ---------")
print("* p = " + str(p))
print("* q = " + str(q))
print("* n = " + str(n))
print("* phi = " + str(phi))
print("* e = " + str(e))
print("* d = " + str(d))
print("----------- Keys ------------")
print("* Public (n,e) = (" + str(n) + "," + str(e) + ")")
print("* Private (n,d) = (" + str(n) + "," + str(d) + ")")
print("---------- Messages ---------")
print("* Plain: " + str(plain))
print("* Encrypted: " + str(cipher))
if plain == decrypted:
    print("* Decrypted: " + str(decrypted) + " (Correct)")
else:
    print("* Decrypted: " + str(decrypted) + " (Failed)")
print()
