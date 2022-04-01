# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>
# include <assert.h>
# include "list.h"

//define a LIST structure
typedef struct node
{
  int length;
  int count;
  int first;
  void** data;
  struct node* next;
  struct node* pre;

}NODE;

//define a NODE structure
typedef struct list
{
  int Count;
  NODE* Head;
  NODE* Tail;
} LIST;

//initialize a LIST pointer by allocating memory for the data structure inside the lists with a dummy node
//takes in the generic compare function
//return a list pointer.
LIST *createList(void)
{
  LIST* pList = malloc(sizeof(LIST));
  assert(pList != NULL);

  pList->Count = 0;
  pList->Head = NULL;
  pList->Tail = NULL;

  return pList;
}

//initialize a NODE pointer by allocating memory for the data structure inside the Node
//takes in a generic data type for the node's value
//return a list pointer.
//runtime: O(1)
NODE* createNode(int first, int length)
{
  assert(first < length);
  NODE* pNew = malloc(sizeof(NODE));
  assert(pNew!= NULL);
  pNew->length = length;
  pNew->count = 0;
  pNew->first = first;
  pNew->data = malloc(sizeof(void*) * pNew->length);
  assert(pNew->data != NULL);
  pNew->next= NULL;
  pNew->pre = NULL;

  return pNew;
}

//free and deallocate all the memories associated with a list
//runtime: O(n)
void destroyList(LIST *lp)
{
  assert(lp != NULL);
  NODE* pDel;
  while(lp->Head != NULL)
  {
    pDel = lp->Head;
    free(pDel);
    lp->Head = pDel->next;
  }
  free(lp);

}
//return the number of elements in the lists
//runtime: O(1)
int numItems(LIST *lp)
{
  assert(lp != NULL);
  return lp->Count;
}

/*add a generic data to the front of the list by adding either the item to the front
 of the current array or a new last array if the current one is full.
  runtime:O(1)
*/
void addFirst(LIST *lp, void *item)
{
  assert(lp != NULL);
  
  if(lp->Head == NULL)
  {
    NODE* new = createNode(2,6);
    lp->Head = new;
    lp->Tail = lp->Head;
    new->data[new->first] = item;
    lp->Count++;
    new->count++;
  }
  else if (lp->Head->count == lp->Head->length)
  {
    NODE* first = createNode(0,lp->Head->length * 2);
    first->next = lp->Head;
    first->pre = NULL;
    first->next->pre = first;
    lp->Head = first;

    first->data[first->first] = item;
    first->count++;
    lp->Count++;
  }
  else
  {
    lp->Head->first = lp->Head->first-1;
		if(lp->Head->first < 0)
    {
			lp->Head->first = lp->Head->length-1;
		}
		lp->Head->data[lp->Head->first] = item;

		lp-head->count++;
		lp->Count++;
  }


}

/*add a generic data to the end of the list by adding either the item to the last
  slot of the last array or a new last array if the current one is full.
  runtime:O(1)
*/
void addLast(LIST *lp, void *item)
{
  assert(lp != NULL);

  if(lp->Tail == NULL)
  {
    NODE* pNew  = createNode(2,6);
    lp->Tail = pNew;
    lp->Head = pNew;
    pNew->data[pNew->first] = item;

    pNew->count++;
    lp->Count++;

  }
  else if (lp->Tail->count == lp->Tail->length)
  {
    NODE* last  = createNode(0,2 * lp->Tail->length);
    last->pre = lp->Tail;
    lp->Tail = last;
    last->next = NULL;
    last->pre->next = last;
    last->data[last->first] = item;

    last->count++;
    lp->Count++;
  }
  else
  {
    lp->Tail->data[(lp->Tail->first + lp->Tail->count) % lp->Tail->length] = item;

    lp->Tail->count++;
    lp->Count++;

  }
}

/*remove the first element in the list
  free the node's memory if the first node is empty
  otherwise, set the data slot to NULL
  runtime: O(1)
*/
void *removeFirst(LIST *lp)
{
  assert(lp != NULL && lp->Head != NULL);
  NODE* np = lp->Head;
  if(np->count == 0)
  {
    lp->Head = lp->Head->next;
    lp->Head->pre = NULL;
    free(np->data);
    free(np);

  }
  void* item = lp->Head->data[lp->Head->first];
  lp->Head->data[lp->Head->first] = NULL;
  lp->Head->first = (lp->Head->first+1)%lp->Head->length;

  lp->Head->count--;
  lp->Count --;

  return item;
}

/*remove the last element in the list
  free the node's memory if the last node is empty
  otherwise, set the data slot to NULL
  runtime: O(1)
*/
void *removeLast(LIST *lp)
{
  assert(lp != NULL && lp->Tail != NULL);
  NODE* np = lp->Tail;
  int last;
  if(np->count == 0)
  {
    lp->Tail = lp->Tail->pre;
    lp->Tail->next = NULL;
    free(np->data);
    free(np);
  }

  last = (lp->Tail->first + lp->Tail->count - 1) % lp->Tail->length;
  void* item = lp->Tail->data[last];
  lp->Tail->data[last] = NULL;

  lp->Tail->count--;
  lp->Count --;

  return item;
}


/*
  takes in a SET pointer and an index
  traverse the list and get the element on the index
  runtime: O(log(n))
*/
void *getItem(LIST *lp, int index)
{
  assert(lp != NULL && index < lp->Count);
  NODE* pCur = lp->Head;
  int i = index;
  while(i >= pCur->count)
  {
    i = i - pCur->count;
    pCur = pCur->next;
  }

  assert(i <= pCur->count);
  return pCur->data[(i + pCur->first) % pCur->length];

}
/*
  Takes in a LIST pointer and an index
  traverse through the list and change the value of the data on the index
  runtime:O(log(n))
*/
void setItem(LIST *lp, int index, void *item)
{
  assert(lp != NULL && index < lp->Count);
  NODE* pCur = lp->Head;
  int i = index;
  while(i >= pCur->count)
  {
    i = i - pCur->count;
    pCur = pCur->next;
  }
    assert(i <= pCur->count);
    pCur->data[(i + pCur->first) % pCur->length] = item;
}
