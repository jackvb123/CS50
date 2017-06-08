import cs50

while True:
    print("Height:",end='')
    h  = cs50.get_int()
    if not (h<0 or h>23):
        break
n=h+1

for i in range(0,h):
    for j in range(0,n-(i+2)):
        print(" ",end = "")
    for j in range(0,i+2):
        print("#",end="")
    print ("")

