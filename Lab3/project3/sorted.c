# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>
# include <assert.h>
# include "set.h"

bool Found = false;//declare a boolean value to store the existence of certain word in an array

/*
  takes in an int as max length
  setting up the inital value of all the data structure in ADP SET,
  allocating memory for all the pointer values and checking if they are
  allocated correctly;
  Then return the SET pointer that the function just defined with max length of maxElts
  runtime: O(1)
*/
SET *createSet(int maxElts)
{
  SET* sp = malloc(sizeof(SET));
  assert(sp != NULL);

  sp->Count = 0;
  sp->Length = maxElts;
  sp->Data = malloc(sizeof(char*) * maxElts);
  assert(sp->Data != NULL);

  return sp;
}

/*
  takes in a SET pointer
  Free and deallocate all the memory associated with the SET pointer
  runtime: O(n)
*/
void destroySet(SET *sp)
{
  assert(sp != NULL);
  for(int j = 0; j < sp->Count; j++)
  {
    free(sp->Data[j]);
  }
    free(sp->Data);
    free(sp);
}

/*
  takes in a SET pointer
  return the number of elements in the array pointed by sp
  runtime: O(1)
*/
int numElements(SET *sp)
{
  return sp->Count;
}

/*
  A Binary search function that takes in a character array pointer, an int max length, a character pointer, and a bollean pointer
  return the middle index if found the character in the chracter array
  return the lower index if did not find(the number then indicatew where the charcter should go in the sorted array)
  runtime: O(log(n))
*/
static int bSearch(char* a[], int n, char* x, bool *found)
{
  int low,high,mid; low = 0, high = n - 1;

  while(low <= high)
  {
    mid = (low + high)/2;
    if (strcmp(x, a[mid]) < 0)
    {
      high = mid - 1;
    }
    else if (strcmp(x, a[mid]) > 0)
    {
      low = mid + 1;
    }
    else
    {
      *found = true;
      return mid;
    }
  }
  *found = false;
  return low;
}

/*
  Takes in a SET pointer and a character pointer
  Check if the character already exists in the array
  if so, the funtion doesn't do anything
  if not, the function adds the chracter to the array in sorted order
  runtime: O(log(n))
*/
void addElement(SET *sp, char *elt)
{
  int index = bSearch(sp->Data, sp->Count, elt, &Found);
  if(sp->Count == sp->Length)
  {
    printf("The set is full, can not add any more element to the set.\n");
  }
  else if(Found == true)
  {
    printf("Element %s already exists in the set.\n", elt);
  }
  else
  {
    for(int i = sp->Count - 1; i >= index; i--)
    {
      sp->Data[i + 1] = sp->Data[i];
    }
    sp->Data[index] = strdup(elt);
    sp->Count ++;

    printf("Element %s Successfully added to the set in index %d.\n", elt, index);
  }
}

/*
  Takes in a SET pointer and a character pointer
  check if the character exists in the array
  if so, the funtion removes it from the array, and sort other elements in unorder
  if not, the funtion doesn't do anything
  runtime: O(log(n))
*/
void removeElement(SET *sp, char *elt)
{
  int index = bSearch(sp->Data, sp->Count, elt, &Found);
  if(sp->Count == 0)
  {
    printf("There is no element to remove.\n");
  }
  else if(Found == false)
  {
    printf("The element %s is not in the set\n", elt);
  }
  else
  {
    for(int k = index; k < sp->Count - 1; k++)
    {
      sp->Data[k] = sp->Data[k+1];
    }
      sp->Count--;
  }
}

/*
  takes in a SET pointer and a character
  check if the character is in the array
  if so, return that euivalent element in the array
  if not, return NULL
  runtime: O(log(n))
*/
char *findElement(SET *sp, char *elt)
{
  int index = bSearch(sp->Data, sp->Count, elt, &Found);
	if(Found == true)
	{
		return sp->Data[index];
	}
    	return NULL;
}

/*
  takes in a SET pointer
  return the value of the pointer the character array pointer
  runtime: O(1)
*/
char **getElements(SET *sp)
{
  assert(sp != NULL);
  return sp->Data;
}
