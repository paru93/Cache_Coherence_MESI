from random import randint
import os

def generator(n):
    for i in range(0,n):
        if(i==n-1):
            a=''
        else:
            a='\n'
        fp.write(str((randint(1,15)%2 + 1))+" "+hex(randint(1,99999999))+" "+str((randint(1,15)%2))+" "+hex(randint(1,99999999))+a)
    fp.close()

os.chdir(os.getcwd())
fp=open("in.txt","w")
x=[]
generator(10)
