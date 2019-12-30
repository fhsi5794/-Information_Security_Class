from Crypto.Random import random
from Crypto.PublicKey import DSA
from Crypto.Hash import SHA

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