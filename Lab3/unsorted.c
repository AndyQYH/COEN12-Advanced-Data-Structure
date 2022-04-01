# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>
# include <assert.h>
# include "set.h"

/*
  setting up the inital value of all the data structure in ADP SET,
  allocating memory for all the pointer values and checking if they are
  allocated correctly;
  Then return the SET pointer that the function just defined with max length of maxElts
  runtime:O(1)
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
  A Sequential search function that takes in a SET pointer and a character array pointer,
  if the character is in the array pointed by sp, return the index where the chracter is in
  if not, return -1 (which is equivalent to nothing is found)
  runtime: O(n)
*/
static int search(SET *sp, char *elt)
{
  assert(sp != NULL);
  for(int l = 0; l < sp->Count; l++)
  {
    if(strcmp(sp->Data[l],elt) == 0)
    {
      return l;
    }
  }
  return -1;
}

/*
  Takes in a SET pointer and a character pointer
  Check if the character already exists in the array
  if so, the funtion doesn't do anything
  if not, the function adds the chracter to the last available postion of the array
  runtime: O(n)/O(1)
*/
void addElement(SET *sp, char *elt)
{
  if(sp->Count == sp->Length)
  {
    printf("The set is full, can not add any more element to the set.\n");
  }
  else if(search(sp,elt) != -1)
  {
    printf("Element already exists in the set.\n");

  }
  else
  {
    sp->Data[sp->Count] = strdup(elt);
    printf("Element %s Successfully added to the set in index %d.\n", elt, sp->Count);
    sp->Count ++;
  }
}

/*
  Takes in a SET pointer and a character pointer
  check if the character exists in the array
  if so, the funtion replace it with the element in the last postion, since order doesn't matter
  if not, the funtion doesn't do anything
  runtime:O(n)
*/

void removeElement(SET *sp, char *elt)
{
  int index = search(sp,elt);
  if(sp->Count == 0)
  {
    printf("There is no element to remove.\n");
  }
  else if(index == -1)
  {
    printf("The element %s is not in the set\n", elt);
  }
  else
  {
    sp->Data[index] = sp->Data[sp->Count - 1];
    sp->Count --;
  }
}

/*
  takes in a SET pointer and a character
  check if the character is in the array
  if so, return that euivalent element in the array
  if not, return NULL
  runtime: O(n)
*/
char *findElement(SET *sp, char *elt)
{
   int index2 = search(sp,elt);
    if(index2 != -1)
    {
      return sp->Data[index2];
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
