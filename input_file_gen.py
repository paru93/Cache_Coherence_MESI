from random import randint
import os
address=0
proc_id=0
rw=0
data=0
def generator(no_memory_lines,no_processors,no_transactions):
    for i in range(0,no_transactions):
        if(i==no_transactions-1):
            a=''
        else:
            a='\n'
            proc_id=str(randint(1,15)%no_processors + 1)
            address=randint(1,no_memory_lines)
            rw=(randint(1,15)%2)
            data=randint(1,256)                        
            if(rw==1):            
                fp.write(proc_id+" "+hex(address)+" "+str(rw)+" "+a)
            else:
                fp.write(proc_id+" "+hex(address)+" "+str(rw)+" "+hex(data)+a)
    fp.close()

os.chdir(os.getcwd())
fp=open("in.txt","w")
x=[]
no_memory_lines=int(input(' No. of memory lines:'))
no_processors=int(input('No. of processors:'))
no_transactions=int(input('No. of read write transactions:'))

generator(no_memory_lines,no_processors,no_transactions)
