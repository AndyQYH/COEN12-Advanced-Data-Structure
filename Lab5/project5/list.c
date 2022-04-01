# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>
# include <assert.h>
# include "list.h"

//define the structure of a list head
typedef struct node
{
  void* data;
  struct node* next;
  struct node* pre;

}NODE;

//define the structure of a node in the list
typedef struct list
{
  int count;
  NODE* head;
  int (*compare)();
}LIST;

//initialize a LIST pointer by allocating memory for the data structure inside the lists with a dummy node
//takes in the generic compare function
//return a list pointer.
LIST *createList(int (*compare)())
{
  LIST* pList = malloc(sizeof(LIST));
  assert(pList != NULL);
  pList->count = 0;
  pList->head = malloc(sizeof(NODE));
  assert(pList->head != NULL);
  pList->head->next = pList->head;
  pList->head->pre = pList->head;
  pList->compare = compare;
  return pList;
}

//initialize a NODE pointer by allocating memory for the data structure inside the Node
//takes in a generic data type for the node's value
//return a list pointer.
NODE* createNode(void* item)
{
  NODE* pNew = malloc(sizeof(NODE));
  assert(pNew!= NULL);
  pNew->data = item;
  pNew->next= NULL;
  pNew->pre = NULL;
  return pNew;

}

//free and deallocate all the memories associated with a list
void destroyList(LIST *lp)
{
  assert(lp != NULL);
  NODE* pDel = lp->head->next;
  NODE* pLoc;
  while(pDel != lp->head)
  {
    pLoc = pDel->next;
    free(pDel);
    pDel = pLoc;
  }
  free(lp);

}
//return the number of elements in the lists
//runtime: O(1)
int numItems(LIST *lp)
{
  assert(lp != NULL);
  return lp->count;
}

/*add a generic data to the front of the list by creating a new node
  and add to the location after list head.
  runtime:O(1)
*/
void addFirst(LIST *lp, void *item)
{
  assert(lp != NULL);
  NODE* new = createNode(item);
  new->next = lp->head->next;
  lp->head->next = new;
  new->next->pre = new;
  new->pre = lp->head;

  lp->count++;

}

/*add a generic data to the end of the list by creating a new node
  and add to the location before list head.
  runtime:O(1)
*/
void addLast(LIST *lp, void *item)
{
  assert(lp != NULL);
  NODE* new = createNode(item);
  new->pre = lp->head->pre;
  lp->head->pre = new;
  new->pre->next = new;
  new->next = lp->head;

  lp->count++;
}

/*remove the first element after list head and free the node's memory
  runtime: O(1)
*/
void *removeFirst(LIST *lp)
{
  assert(lp != NULL);
  NODE* np;
  np = lp->head->next;
  void* item = np->data;
  lp->head->next = np->next;
  lp->head->next->pre = lp->head;
  lp->count --;

  free(np);
  return item;
}

/*remove the last element before list head and free the node's memory
  runtime: O(1)
*/
void *removeLast(LIST *lp)
{
  assert(lp != NULL);
  NODE* np = lp->head->pre;
  void* item = np->data;
  lp->head->pre = np->pre;
  lp->head->pre->next = lp->head;
  lp->count --;

  free(np);
  return item;
}

// return the first element of the list
//runtime: O(1)
void *getFirst(LIST *lp)
{
  assert(lp != NULL);
  return lp->head->next->data;
}

//return the last element of the lists
//runtime: O(1)
void *getLast(LIST *lp)
{
  assert(lp != NULL);
  return lp->head->pre->data;
}

/*
  Takes in a LIST pointer and a generic pointer
  traverse through the list using a pointer,
  and compare each item in the list with the generic data
  if found, the funtion remove it from the list
  if not, the funtion doesn't do anything
  runtime:O(1)/O(n)
*/
void removeItem(LIST *lp, void *item)
{
  assert(lp != NULL && lp->compare != NULL);
  NODE* pcur = lp->head->next;

  while(pcur != lp->head)
  {
    if((*lp->compare)(pcur->data, item) == 0)
    {
        pcur->next->pre = pcur->pre;
        pcur->pre->next = pcur->next;
        free(pcur);
        lp->count--;
        break;
    }
    pcur = pcur->next;
  }
}

/*
  Takes in a LIST pointer and a generic pointer
  traverse through the list using a pointer,
  and compare each item in the list with the generic data
  if found, the funtion return the matching element from the list
  if not, the funtion returns null
  runtime:O(1)/O(n)
*/
void *findItem(LIST *lp, void *item)
{
  assert(lp != NULL && lp->compare != NULL);
  NODE* pcur = lp->head->next;
  while(pcur != lp->head)
  {
    assert(pcur->data != NULL);
    if((*lp->compare)(pcur->data, item) == 0)
    {
        return pcur->data;
    }
    pcur = pcur->next;
  }
  return NULL;
}

/*
  takes in a SET pointer
  loop through the list and get all the existing elements into another array and return the new array
  runtime: O(n)
*/
void *getItems(LIST *lp)
{
  assert(lp != NULL);
  void** items = malloc(sizeof(void*) * lp->count);
  assert(items != NULL);
  NODE* pcur = lp->head->next;
  int index = 0;
  while(pcur != lp->head)
  {
    items[index] = pcur->data;
    pcur = pcur->next;
    index++;
  }
  return items;
}
