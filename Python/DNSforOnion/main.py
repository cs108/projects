# -*- coding: utf-8 -*-
"""
Created on Sat Jan 26 10:35:54 2019

@author: cs108

Python interpreter version: 32bit
"""

from Crypto.PublicKey import RSA
import hashlib
import time
import base64


'''
STEP 1
generate new rsa keys;
hash its public key;
mix hash value with timestamp after convert it from hexadecimal to decimal;
encode the mixed value with base32
'''
BITS=1024     #length of n in binary 
E=7           #specify e

rsaObj=RSA.generate(bits=BITS,e=E)

e=rsaObj.e    #of course it's equal to E
n=rsaObj.n
publicKey="(e=%d,n=%d)"%(e,n,)#'(e='+str(rsaObj.e)+',n='+str(rsaObj.n)+')'
print("public Key:",publicKey)
d=rsaObj.d
privateKey="(d=%d,n=%d)"%(d,n,)
print("private key:",privateKey)
hashValue=hashlib.sha1(publicKey.encode()).hexdigest()
print("raw hash value:",hashValue)
index=int(len(str(hashValue))/2)
hashValue=hashValue[:index]
print("first half of hash value:",hashValue)
hashValue=int(hashValue,16)
print("converted into decimal:",hashValue)
timeStamp=int(time.time())
print("time stamp:",timeStamp)
mixValue=hashValue+timeStamp
print("mix hash value with time stamp:",mixValue)
encodedObj=base64.b32encode(str(mixValue).encode('utf-8'))
encodedStr=str(encodedObj,'utf-8')
print("encoded with base32:",encodedStr)




'''
STEP 2
try to make encoded str looks more meaningful:
    change value of timestamp or change public key by generate rsa again.
obviously changing value of timestamp would save more time
'''

p=rsaObj.p
q=rsaObj.q
def collectMeaningfulDN():#collect meaningful domain name
    found=0
    dest="yzu"
    while not found:
        timeStamp=int(time.time())
        mixValue=hashValue+timeStamp
        encodedObj=base64.b32encode(str(mixValue).encode('utf-8'))
        encodedStr=str(encodedObj,'utf-8')
        a=encodedStr.find(dest)
        if(a!=-1):
            found=1
            print(encodedStr)
        
'''
    if(a!=-1):
        f=open("MeaningfulDN.txt",'a')
        f.writelines("DomainName:",encodedStr)
        f.writelines(publicKey,privateKey)
        f.writelines("p=",p,"\nq=",q)
        f.writelines("timeStamp:",timeStamp)
        f.close()
    
while 1==1:
    collectMeaningfulDN()
'''

collectMeaningfulDN()

#==============================================================================
# key = RSA.generate(bits=1024,e=6)
# print("d is",key.d)
# print("e is ",key.e)
# 
# print(key.exportKey("PEM"))
#  
#  
# pub_key=key.publickey()
# print(pub_key.exportKey("PEM"))
#==============================================================================



#==============================================================================
# f = open('mykey.pem','w')
# f.write(key.exportKey('PEM'))
# f.close()
# 
# f = open('mykey.pem','r')
# key = RSA.importKey(f.read())
#==============================================================================
