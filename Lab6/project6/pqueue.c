# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <assert.h>
# include "pqueue.h"

#define p(x) (((x)-1)/2)//functions for calculaing the parent node
#define l(x) ((x) * 2 + 1)//functions for calculaing the left child node
#define r(x) ((x) * 2 + 2)//functions for calculaing the right child node
#define INIT_LENGTH 10

//allocate memory and initialize a priority queue ADT pointer
//O(1)
PQ *createQueue(int (*compare)())
{
  PQ* pq;

  assert(compare != NULL);

  pq = malloc(sizeof(PQ));
  assert(pq != NULL);

  pq->compare = compare;
  pq->length = INIT_LENGTH;
  pq->count = 0;

  pq->data = malloc(sizeof(void*) * pq->length);
  assert(pq->data != NULL);

  return pq;
}

//deallocate all memmory associate with the PQ pointer pq
//O(1)
void destroyQueue(PQ *pq)
{
  assert(pq != NULL);

  free(pq->data);
  free(pq);
}

//return the number of entries in the priority pqueue
//O(1)
int numEntries(PQ *pq)
{
  assert(pq != NULL);
  return pq->count;
}

//add the entry to the last postion and undergoes reheap up process to place it in order
//O(nlog(n))
void addEntry(PQ *pq, void *entry)
{
  assert(pq != NULL);
  void* current;
  void* parent;
  int cur = 0;
  int pre = 0;

  if(pq->count == pq->length)
  {
    pq->length = pq->length * 2;
    pq->data = realloc(pq->data, sizeof(void*) * (pq->length));

  }
  pq->data[pq->count] = entry;
  cur = pq->count;
  pq->count++;


  while(p(cur) >= 0)
  {
    pre = p(cur);
    current = pq->data[cur];
    parent = pq->data[pre];
    if((pq->compare)(current, parent) < 0)
    {
      pq->data[pre] = current;
      pq->data[cur] = parent;
      cur = pre;
    }
    else
    {
      break;
    }

  }
}

//remove and return the smallest entry in the priority pqueue
//replace the root with the last element in the queue, and then do reheap down process
//O(nlog(n))
void *removeEntry(PQ *pq)
{
  assert(pq != NULL && pq->count > 0);
  void *current, * min, *smallest;
  int cur = 0;
  int next;

  smallest = pq->data[cur];
  pq->data[cur] = pq->data[pq->count - 1];
  pq->data[pq->count-1] = NULL;
  pq->count--;

  while(l(cur) < pq->count)
  {
    int left = l(cur);
    int right = r(cur);
    current = pq->data[cur];


    if(right < pq->count && (pq->compare)(pq->data[right],pq->data[left]) < 0)
    {
      min = pq->data[right];
      next = right;
    }
    else
    {
      min = pq->data[left];
      next = left;
    }

    if((pq->compare)(current,min) >= 0)
    {
      pq->data[cur] = min;
      pq->data[next] = current;
      cur = next;
    }
    else
    {
      break;
    }

  }
  return smallest;
}
