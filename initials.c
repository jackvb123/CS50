#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int main(){
    string name = get_string();
    int l = strlen(name);
    char c;
    for(int i =0;i<l;i++){
        if(i==0 || c==' ')
            printf("%c",toupper(name[i]));
        c= name[i];
    }
    printf("\n");
}