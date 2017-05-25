#include <stdio.h>
#include <cs50.h>

int main(void){
    int h;
    do{
    printf("Height: ");
     h=get_int();
    }while(h<0 | h > 23);
    int n=h+1;
    for(int i=0; i < h;i++){
        for(int j=0;j<n-(i+2);j++)
            printf(" ");
        for(int j=0;j<i+2;j++)
            printf("#");
        printf("\n");
    }
}