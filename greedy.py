import cs50


print("O hai! ",end = "")
    
while True:
    print("How much change is owed?")
    f = cs50.get_float()
    if not(f<0):
        break
    
i =  f
d =0
count =0
f=f*100
 
i = round(f);
#print(i)
if(i >= 100):
    d = i//100;
    
    count=d*4;
    i = i-d*100;
#print(i)
while(i >= 1):
    #print(i)
    if(i>=25) :
        i = i-25
        count=count+1

    elif(i >=10):
        i= i-10
        count=count+1
        
    elif(i >= 5):
        i=i-5
        count=count+1
    
    elif (i >= 1):
        i=i-1
        count=count+1
        
print(count)
