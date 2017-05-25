#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(){
    printf("O hai! ");
    float f;
    do{   
    printf("How much change is owed?\n");
     f = get_float();
    }while(f<0);
    int i = (float) f;
    int d =0;
    int count =0;
    f=f*100;
    //printf("%0.55f ",f);
    i = round(f);
   // printf("%d ",i);
    if(i >= 100){
        d = i/100;
        count=d*4;
        i = i-d*100;
    }
    while(i >= 1){
       // printf("%d ",i);
        if(i>=25) {
             i = i-25;
             count++;
        }
        else if(i >=10){
            i= i-10;
            count++;
        }
        else if(i >= 5){
            i=i-5;
            count++;
        }
        else if (i >= 1){
            i=i-1;
            count++;
        }
    }
    printf("%d\n",count);
}