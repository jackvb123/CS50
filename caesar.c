#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, string argv[]){
    if(argc !=2) {
    printf("Usage: ./caesar k\n");
    return 1;
        
    }
   
    int k = atoi(argv[1]);
    printf("plaintext: ");
    string p = get_string();
    for(int i =0;i< strlen(p);i++){
        if(islower(p[i])){
           int d = p[i]-'a';
            d = (d+k)%26;
            p[i] = 'a' + d;
        }
        else if (isupper(p[i])){
            int d = p[i]-'A';
            d = (d+k)%26;
            p[i] = 'A' + d;
        }
        
    }
    printf("ciphertext: %s\n", p);
  
}