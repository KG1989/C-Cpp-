/*	stack.c: Stack application. */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "dynArray.h"


/* ***************************************************************
Using stack to check for unbalanced parentheses.
***************************************************************** */

/* Returns the next character of the string, once reaches end return '0' (zero)
	param: 	s pointer to a string 	
	pre: s is not null		
*/
char nextChar(char* s)
{
	static int i = -1;	
	char c;
	++i;	
	c = *(s+i);			
	if ( c == '\0' )
		return '\0';	
	else 
		return c;
}

/* Checks whether the (), {}, and [] are balanced or not
	param: 	s pointer to a string 	
	pre: s is not null	
	post:	
*/
int isBalanced(char* s)
{
	/* FIXME: You will write this function */		
	char c;
	DynArr *arr; //need this for push and pop functions
	arr = newDynArr(100);

	    while ((c = nextChar(s)) != '0') {
        if ((c == '(') || (c == '{' ) || (c == '[')) {
            pushDynArr(arr,c);
        }

        else if (c == ')') {
            if (topDynArr(arr) == '(') {
                popDynArr(arr);
            }
            else {
                return 0;
            }
        }

        else if (c == '}') {
            if (topDynArr(arr) == '{') {
                popDynArr(arr);
            }
            else {
                return 0;
            }
        }

        else if (c == ']') {
            if (topDynArr(arr) == '[') {
                popDynArr(arr);
            }
            else {
                return 0;
            }
        }
    }

    if(!isEmptyDynArr(arr)){
        return 0;
    }
    deleteDynArr(arr);
    return 1;

}
/*
	while (ch = nextChar(s) != '\0')
	{
		if (ch == '(')
		{
			pushDynArr(arr, ')');
		}
		else if (ch == '{' )
		{
			pushDynArr(arr, '}');	
		}
		else if (ch == '[' )
		{
			pushDynArr(arr, ']');
		}
		else if (ch == ')' || ch == '}' || ch == ']')
		{
            if(isEmptyDynArr(arr))
			{
				return 0;
			}
            else if (ch == topDynArr(arr)) 
			{
                popDynArr(arr);
            } 
			else if (ch != topDynArr(arr)) 
			{
                return 0;
            }
		}

		ch = nextChar(s);
	}

	if (isEmptyDynArr(arr))
	{
		deleteDynArr(arr);
		return 1;
	}
	else
	{
		return 0;
	}


	*/


int main(int argc, char* argv[]){
	
	char* s=argv[1];	
	int res;
	
	printf("Assignment 2\n");

	res = isBalanced(s);

	if (res)
		printf("The string %s is balanced\n",s);
	else 
		printf("The string %s is not balanced\n",s);
	
	return 0;	
}

