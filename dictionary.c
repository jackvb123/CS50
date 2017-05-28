/**
 * Implements a dictionary's functionality.
 */

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "dictionary.h"
#include <ctype.h>

int count=0;
struct Node{
    struct Node * child[27];
    bool isEnd;
    
};

struct Node *newNode(void){
    struct Node *pNode = NULL;
    pNode = (struct Node *)malloc(sizeof(struct Node));
    
    if(pNode){
        pNode->isEnd = false;
        for(int i =0;i<27;i++)
            pNode->child[i] = NULL;
    }
    return pNode;
}

void insertWord(struct Node *root, const char *word){
    int l = strlen(word);
    int i;
    struct Node *pTemp = root;
    for(int j=0;j<l;j++){
        i = (word[j])-'a';
        if(word[j]=='\'') i = 26;
        if(!pTemp->child[i]) 
            pTemp->child[i] = newNode();
        pTemp = pTemp->child[i];
    }
    if(pTemp->isEnd != true) count++;
    pTemp->isEnd = true;   
}

bool checkWord(struct Node*root, const char *w){
    
    int l = strlen(w);
    
    char word[l];
    for(int j=0;j<l;j++) 
        {
            if(isupper(w[j])){
                word[j]=w[j]+32;
            }else
            word[j] = w[j];
        }
   // printf("%d--%s ",l,word);
    int i;
    struct Node *pTemp =root;
    for(int j = 0 ; j < l ;j++){
        i=(word[j]) - 'a';
        if(word[j]=='\'') i = 26;
        if(!pTemp->child[i])
            return false;
        pTemp = pTemp->child[i];
    }
    //if((pTemp!=NULL && pTemp->isEnd)) 
      //  printf(" found");
   // printf("\n");
    
    return (pTemp!=NULL && pTemp->isEnd);
}
bool deleteAll(struct Node *root){
    struct Node *pTemp =root;
    int j=0;
    for(int i=0;i<27;i++){
        if(!pTemp->child[i])
            j++;
    }
    //printf("%d\n",j);
    if(j==27) {
        free(pTemp);
        return true;
        
    }
    else{
    for(int i=0;i<27;i++){
        if(pTemp->child[i])
            deleteAll(pTemp->child[i]);
    }
    free(pTemp);
    return true;
    }
    return false;
}

struct Node * root ;

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char *word)
{
   // printf("Checking %s\n",word);
    return checkWord(root, word);
}

/**
 * Loads dictionary into memory. Returns true if successful else false.
 */
bool load(const char *dictionary)
{
    FILE *inptr = fopen(dictionary, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", dictionary);

        return false;
    }
    char word[LENGTH+1];
    root = newNode();
    int index =0;
     for (int c = fgetc(inptr); c != EOF; c = fgetc(inptr))
    {
        if (isalpha(c) || (c == '\'' && index > 0))
        {
            word[index] = c;
            index++;
            if (index > LENGTH)
            {
                while ((c = fgetc(inptr)) != EOF && isalpha(c));
                index = 0;
            }
        }
        else if (isdigit(c))
        {
            while ((c = fgetc(inptr)) != EOF && isalnum(c));
            index = 0;
        }
        else if (index > 0)
        {
            word[index] = '\0';
            
            //printf("%s\n",word);
            insertWord(root,word);
            
            index = 0;
        }
    }
   
    return true;    
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    // TODO
    return count;
}

/**
 * Unloads dictionary from memory. Returns true if successful else false.
 */
bool unload(void)
{
    return deleteAll(root);
    
}
