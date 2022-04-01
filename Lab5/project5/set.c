# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>
# include <assert.h>
# include "set.h"
# include "list.h"

#define FILLED 1
#define EMPTY 0
#define DELETED 2



typedef struct set
{
  int Count;
  int Length;
  LIST** lists;
  int (*compare)();
  unsigned (*hash)();
}SET;
/*
  setting up the initial value of all the data structure in ADP SET with a list ADT in each hash slot,
  allocating memory for all the pointer values and checking if they are
  allocated correctly;
  Then return the SET pointer that the function just defined with max length of maxElts with a list pointer to each index.
  runtime:O(1)+O(n) = O(n)
*/
SET *createSet(int maxElts, int(*compare)(), unsigned(*hash)())
{
  assert(compare != NULL && hash!= NULL);
  SET* sp = malloc(sizeof(SET));
  assert(sp != NULL);

  sp->Count = 0;
  sp->Length = maxElts;

  sp->lists = malloc(sizeof(LIST*) * maxElts);
  assert(sp->lists != NULL);

  sp->compare = compare;
  sp->hash = hash;

  for(int i = 0; i < maxElts; i++)
  {
    sp->lists[i] = createList(compare);
  }

  return sp;
}

/*
  takes in a SET pointer for generic lists pointer
  Free and deallocate all the memory associated with the SET pointer
  runtime: O(n)/O(n*n)
*/

void destroySet(SET *sp)
{
  assert(sp != NULL);
  for(int j = 0; j < sp->Length; j++)
  {
    destroyList(sp->lists[j]);
  }
    free(sp->lists);
    free(sp);
}

/*
  takes in a SET pointer
  return the number of elements in the arraylists pointed by sp
  runtime: O(1)
*/
int numElements(SET *sp)
{
  assert(sp != NULL);
  return sp->Count;
}


/*
  Takes in a SET pointer and a generic pointer
  go to the element's assigned hash list and check if it is in there
  if so, the function doesn't do anything
  if not, the function adds the character to the last available position of the array
  runtime: O(1)/O(n)
*/
void addElement(SET *sp, void *elt)
{
  assert(sp != NULL);
  int hashNum = ((sp->hash)(elt)) % (sp->Length);
  if(findItem(sp->lists[hashNum], elt) == NULL)
    {
      addFirst(sp->lists[hashNum], elt);
      sp->Count++;
    }
}

/*
  Takes in a SET pointer and a generic pointer
  go to the element's assigned hash value, and check if it is there
  if so, the funtion remove it from the list
  if not, the funtion doesn't do anything
  runtime:O(1)/O(n)
*/

void removeElement(SET *sp, void *elt)
{
  assert(sp != NULL);
  int hashNum = ((sp->hash)(elt)) % (sp->Length);
  if(findItem(sp->lists[hashNum], elt) != NULL)
  {
      removeItem(sp->lists[hashNum], elt);
      sp->Count--;
  }
}

/*
  takes in a SET pointer and a generic pointer
  go to the list with the element's hash value, check if it is there
  if so, return that equivalent element in the list
  if not, return NULL
  runtime: O(1)/O(n)
*/
void *findElement(SET *sp, void *elt)
{
   assert(sp != NULL);
   int hashNum = ((sp->hash)(elt)) % (sp->Length);

   return findItem(sp->lists[hashNum], elt);
}

/*
  takes in a SET pointer
  loop through the array of lists and get all the existing elements into another array and return the new array
  runtime: O(n)
*/
void *getElements(SET *sp)
{
  assert(sp != NULL);
  int i,j,k;
  k = 0;
  void** elts;
  elts = malloc(sizeof(void*) * sp->Count);
  assert(elts != NULL);

  for(i = 0; i < sp->Length; i++)
  {
    void **lists = getItems(sp->lists[i]);
    for(j = 0; j < numItems(sp->lists[i]); j++)
    {
      elts[k] = lists[j];
      k++;
    }
  }
  return elts;
}
