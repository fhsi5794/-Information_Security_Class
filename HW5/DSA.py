from Crypto.Random import random
from Crypto.PublicKey import DSA
from Crypto.Hash import SHA
"""
def gcd(a,b):
    while b!=0:
            a,b=b,a%b
    return a

def findModReverse(a,m): # use Extended Euclidean algorithm
    if gcd(a,m)!=1:
        return None
    u1,u2,u3 = 1,0,a
    v1,v2,v3 = 0,1,m
    while v3!=0:
        q = u3//v3
        v1,v2,v3,u1,u2,u3 = (u1-q*v1),(u2-q*v2),(u3-q*v3),v1,v2,v3
    return u1%m
"""
message = "Hello"
key = DSA.generate(1024)
h = SHA.new(message.encode('utf8')).digest()
k = random.StrongRandom().randint(1,key.q-1)
sig = key.sign(h,k)
v = key.verify(h,sig)

print("----------Generate Key----------")
print("p = ",key.p,"\nq = ",key.q,"\ngenerator = ",key.g,"\nPublic key = ",key.y)
print("----------Sign----------")
print("message = ",message)
print("r = ",sig[0],"\ns = ",sig[1])
print("----------Verification----------")
print("verify = ",v)