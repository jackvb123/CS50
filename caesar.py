import sys
import cs50

argc  = len(sys.argv)
argl  = list(sys.argv)
if(argc !=2):
    print("Usage: ./caesar k")
    exit(1)

k= int(argl[1])
#print(k)
print("plaintext: ",end ='')
p = cs50.get_string()
q=str()
for i in range(0,len(p)):
 #   print(type(p[i])," ",end='')
    if(p[i].islower()):
        d = ord(p[i]) - ord('a')
        d = (d+k)%26
        q =q+ chr(ord('a') + d)
        
    elif (p[i].isupper()):
        d = ord(p[i])-ord('A')
        d = (d+k)%26
        q =q+ (chr(ord('A') + d))
    else:
        q = q+p[i]
  #  print(q[i]," ",end='')    
    
print("ciphertext: ", q)


    