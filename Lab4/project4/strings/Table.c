# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>
# include <assert.h>
# include "set.h"

#define FILLED 1
#define EMPTY 0
#define DELETED 2
/*
  setting up the inital value of all the data structure in ADP SET,
  allocating memory for all the pointer values and checking if they are
  allocated correctly;
  Then return the SET pointer that the function just defined with max length of maxElts
  runtime:O(1)+O(n) = O(n)
*/
SET *createSet(int maxElts)
{
  SET* sp = malloc(sizeof(SET));
  assert(sp != NULL);

  sp->Count = 0;
  sp->Length = maxElts;

  sp->Data = malloc(sizeof(char*) * maxElts);
  assert(sp->Data != NULL);

  sp->Flag = malloc(sizeof(char) * maxElts);
  assert(sp->Flag != NULL);

  for(int i = 0; i < maxElts; i++)
  {
    sp->Flag[i] = EMPTY;
  }

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
  for(int j = 0; j < sp->Length; j++)
  {
    if(sp->Flag[j] == FILLED)
    {
      free(sp->Data[j]);
    }
  }
    free(sp->Data);
    free(sp->Flag);
    free(sp);
}

/*
  takes in a SET pointer
  return the number of elements in the array pointed by sp
  runtime: O(1)
*/
int numElements(SET *sp)
{
  assert(sp != NULL);
  return sp->Count;
}

static unsigned strhash(char *s)
{
  unsigned hash = 0;
  while (*s != '\0')
  {
    hash = 31 * hash + *s ++;
  }
  return hash;
}

/*
  A search function that uses linear probing and hashing techniques; takes in a SET pointer, a char pointer,
  if the character is in the array pointed by sp, return the index where the chracter is in
  else return the first available position for the word
  runtime: O(n)
*/
static int search(SET *sp, char *elt, bool* found)
{
  int hashNum = strhash(elt) % sp->Length;
  int index = -1;
  int firstSlotDeleted = -1;


  for(int i = 0; i < sp->Length; i++)
  {
    index = (hashNum + i) % sp->Length;

    if(sp->Flag[index] == EMPTY)
    {
      *found = false;
      if(firstSlotDeleted == -1)
      {
        return index;
      }
      return firstSlotDeleted;
    }
    else if(sp->Flag[index] == FILLED)
    {
      if(strcmp(sp->Data[index], elt) == 0)
      {
        *found = true;
         return index;
      }
    }
    else if(sp->Flag[index] == DELETED)
    {
      if(firstSlotDeleted == -1)
      {
        firstSlotDeleted = index;
      }
    }
 }

  *found = false;
   return index;
}

/*
  Takes in a SET pointer and a character pointer
  Check if the character already exists in the array
  if so, the funtion doesn't do anything
  if not, the function adds the chracter to the last available postion of the array
  runtime: O(n)
*/
void addElement(SET *sp, char *elt)
{
  assert(sp != NULL && elt != NULL);
  bool Found;
  int index = search(sp, elt, &Found);
  if(Found == false)
  {
    assert(sp->Count < sp->Length);
    sp->Data[index] = strdup(elt);
    sp->Flag[index] = FILLED;
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
  assert(sp != NULL && elt != NULL);
  bool Found;
  int index = search(sp,elt, &Found);
  if(sp->Count != 0 && Found == true)
  {
    free(sp->Data[index]);
    sp->Flag[index] = DELETED;
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
   assert(sp != NULL && elt != NULL);
   bool Found;
   int index2 = search(sp,elt, &Found);
    if(Found == true)
    {
      return sp->Data[index2];
    }
    return NULL;
}

/*
  takes in a SET pointer
  loop through sp->data and get all the existing elements into another array and return the new array
  runtime: O(n)
*/
char **getElements(SET *sp)
{
  assert(sp != NULL);
  int i,j;
  j =0;
  char** elts;
  elts = malloc(sizeof(char*) * sp->Count);
  assert(elts != NULL);

  for(i = 0; i < sp->Length && j < sp->Count; i++)
  {
    if(sp->Flag[i] == FILLED)
    {
      elts[j] = sp->Data[i];
      j++;
    }
  }
  return elts;
}
