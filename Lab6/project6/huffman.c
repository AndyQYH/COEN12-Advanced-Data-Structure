# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <ctype.h>
# include <assert.h>
# include "pqueue.h"
# include "pack.h"
#define NODE struct node
#define MAX_ARRAY_LENGTH 257// total number of ASCII values(256) plus 1 for EOF


//O(1)
//allocate memory and initiate a NODE pointer with two other pointer as its left and right children.
static NODE* mknode(int data, NODE* left, NODE *right)
{
  NODE* np = malloc(sizeof(NODE));
  assert(np != NULL);

  np->parent = NULL;
  np->count = data;

  if(left != NULL)
  {
    left->parent = np;
  }
  if(right != NULL)
  {
    right->parent = np;
  }
  return np;
}

//O(1)
//function that compare the count value stored in two NODE pointers
static int nodecmp(NODE* t1, NODE* t2)
{
  assert(t1 != NULL && t2 != NULL);
  if (t1->count < t2->count)
	{
		return -1;
	}
	else if (t1->count > t2->count)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

//O(log(n))
//a recursive function that determine the depth of a node to the root
static int depth(NODE*np)
{
  assert(np != NULL);
  if(np->parent == NULL)
  {
    return 0;
  }
  return 1 + depth(np->parent);
}

//Huffman coding project with main
int main(int argc, char* argv[])
{
  assert(argc > 2);

  FILE* fp;//declare a file pointer object
  PQ* pq;// priority queue pointer
  NODE *min1, *min2, *combine;// NODE pointers used to store minmium tree values
  int c; int bits = 0;// used to store ASCII value of a character
  int counts[MAX_ARRAY_LENGTH] = {0};//change to malloc if this does not work;
  NODE* nodes[MAX_ARRAY_LENGTH]= {NULL};//change to malloc if this does not work;


 //check if the program can open the file

  fp = fopen(argv[1],"r"); //set the pointer to the start of the file, in reading mode

  if (fp == NULL)
  {
   	 fprintf(stderr, "cannot open file\n");
     exit(EXIT_FAILURE);
  }

  //use scanner to scan all the characters in the file
  //O(n)
  while((c = fgetc(fp)) != EOF)
  {
    counts[c]++;
  }
  fclose(fp);

 //create a priority queue ADT with nodecmp as its compare function
 pq = createQueue(nodecmp);

 //add leaf nodes with characters of non zero count into the priority queue
 //O(n)
 for(int m = 0; m < MAX_ARRAY_LENGTH; m++)
  {
    if(counts[m] != 0 || m == MAX_ARRAY_LENGTH - 1)
    {
       nodes[m] = mknode(counts[m], NULL, NULL);
       addEntry(pq, nodes[m]);
    }
  }
  //we take the smallest two nodes, remove them from the priority queue,
  //combine them together into onw tree
  //and reinsert it into the priority queue
  //O(n)
  while(numEntries(pq) > 1)
  {
    min1 = removeEntry(pq);
    min2 = removeEntry(pq);
    combine = mknode(min1->count + min2->count, min1, min2);
    addEntry(pq, combine);
  }

 //print out the assigned bit value for each character in the priority pqueue
 //O(n)
  for(int j = 0; j < MAX_ARRAY_LENGTH; j++)
  {
    if(nodes[j] != NULL)
    {
      printf(isprint(j) ? "'%c':" : "%03o:", j);
      printf("%d x %d bits = %d bits", nodes[j]->count, depth(nodes[j]), nodes[j]->count * depth(nodes[j]));
      printf("\n");
      bits += (nodes[j]->count * depth(nodes[j]));
    }
  }

  printf("Total number of bits:%d bits\n", bits);

  //last, pack the file
  pack(argv[1], argv[2], nodes);

  //deallocate memory associate with priority queue
  destroyQueue(pq);
  exit(EXIT_SUCCESS);
}
