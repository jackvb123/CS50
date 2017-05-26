/**
 * helpers.c
 *
 * Helper functions for Problem Set 3.
 */
 
#include <cs50.h>

#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
	int l = 0;
	int r = n-1;
	while(l<=r){
		int m = l+(r-l)/2;
		
		if(values[m] == value)
		return true;
		if(values[m] < value)
			l=m+1;
		else
		   	r=m-1;
	}
    return false;
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    int min ;
    int ind = 0;
    int k;
    for( k=0;k< n; k++){
        min = INT_MAX;
        int j ;
        for(j=k;j<n;j++){
            if(values[j] < min )
                {
                    min = values[j];
                    ind = j;
                }
        }
        int temp = values [ind];
        values[ind] = values [k];
        values[k] = temp;
    }
    return;
}
