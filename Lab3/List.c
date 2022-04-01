# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>
# include <assert.h>
# include "set.h"


typedef struct node
{
  int length;
  int count;
  int first;
  void** data;
  struct node* next;
  struct node* pre;

}NODE;

typedef struct list
{
  int Count;
  NODE* Head;
  NODE* Tail;
} LIST;
/*
  setting up the inital value of all the data structure in ADP SET,
  allocating memory for all the pointer values and checking if they are
  allocated correctly;
  Then return the SET pointer that the function just defined with max length of maxElts
  runtime:O(1)
*/
extern LIST *createList(void)
{
  NODE* n =malloc(sizeof(NODE));
  assert(n != NULL);
  LIST* pList = malloc(sizeof(LIST));
  assert(plist != NULL);
  pList->Count = 0;
  pList->Head = n;
  pList->Tail = n;
  pList->compare = compare;
  return pList;
}

extern void destroyList(LIST *lp)
{
  assert(lp != NULL);
  NODE* pDel = lp->Head;
  while(l=->Head != NULL)
  {
    pDel = lp->Head;
    lp->Head = pDel->Next;
    free(pDel);
    lp->Count--;
  }
  free(lp)
}

extern int numItems(LIST *lp)
{
  assert(lp != NULL);
  return lp->Count;
}

static int search(LIST* lp, NODE* pLoc, void* item)
{
   bool Found;
   pPre = NULL;
   pLoc = lp->Head;
   while(pLoc != NULL && )
   {

   }

}
extern void addFirst(LIST *lp, void *item)
{
  assert(lp != NULL);

  lp->Head = item;
  lp->Count++;
}

extern void addLast(LIST *lp, void *item);
{

  lp->Count++;
}

extern void *removeFirst(LIST *lp)
{
  assert(lp != null)

}

extern void *removeLast(LIST *lp)
{
  lp->Count--;
}

extern void *getFirst(LIST *lp);

extern void *getLast(LIST *lp);

extern void *getItem(LIST *lp, int index);

extern void setItem(LIST *lp, int index, void *item);
