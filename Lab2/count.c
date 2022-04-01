#include <stdio.h>
#define MAX_WORD_LENGTH 30

int main(int argc, char* argv[])
{
  FILE* fP;//declare a pointer object
  int wordCount = 0;// declare a int value to store wordcount
  char word[MAX_WORD_LENGTH];//declare a chracter array(string) to store scanned value
  fP = fopen(argv[1],"r"); //set the pointer to the start of the file, in reading mode

  /*
    The while loop is a checking condition for if the scanner scans the entire file.
    In other words, does the scanner reaches the end of file.
    We ser the scanner to read one word at a time(by using the buffer), so as long as there's another word after, the while loop will run
    And each time, the number of word read is increased by 1 so we have to implement that value by 1 everytime.
  */
  while(fscanf(fP,"%s", word) != EOF)
  {
     wordCount++;
  }
  fclose(fP);

  /* print out the number of word in a text to check for errors*/
  printf("The total number of words in %s is %d \n", argv[1], wordCount);
}
