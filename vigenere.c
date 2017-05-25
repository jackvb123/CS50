#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, string argv[]){
    int f =0;
    if(argv[1]==NULL ) {
    printf("Usage: ./caesar k\n");
    return 1;
        
    }
    for(int i =0;i < strlen(argv[1]);i++){
        if(!isalpha(argv[1][i])) f=1;
    }
    if(argc !=2 | f ==1 ) {
    printf("Usage: ./caesar k\n");
    return 1;
        
    }
   
    string k = (argv[1]);
    int l = strlen(argv[1]);
    int c = 0;
    printf("plaintext: ");
    string p = get_string();
    for(int i =0;i< strlen(p);i++){
        if(!isalpha(p[i])){
            continue;
        }
        if(islower(p[i])){
            int d = p[i]-'a';
            if(islower(k[c]))
            d = (d+(k[c]-'a'))%26;
            else if(isupper(k[c]))
             d = (d+(k[c]-'A'))%26;
            c=(c+1)%l;
            p[i] = 'a' + d;
        }
        else if (isupper(p[i])){
            int d = p[i]-'A';
            if(islower(k[c]))
            d = (d+(k[c]-'a'))%26;
            else if(isupper(k[c]))
             d = (d+(k[c]-'A'))%26;
            c=(c+1)%l;
            p[i] = 'A' + d;
        }
        
    }
    printf("ciphertext: %s\n", p);
  
}