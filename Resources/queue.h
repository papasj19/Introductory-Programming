/*
  Spencer Johnson : May 9, 2021
  Project 2.3 Programming M and T 

  The file given to us from the estudy. 
  
you will see in this file that the element, although still reffered to as an element, and acting with the nature of an element, will call to the structure of the venue and place this as sthe element. 
*/

#ifndef _QUEUE_H_
#define _QUEUE_H_

// Libraries
#include <stdlib.h>

// Constants
#define QUEUE_SIZE 10

// Error codes
#define QUEUE_NO_ERROR 0
#define QUEUE_ERROR_EMPTY 1
#define QUEUE_ERROR_FULL 2
#define QUEUE_ERROR_MALLOC 3

// Data types
typedef struct{
  char name[50];
  int capacity;
} Venue; 

typedef Venue Element;


typedef struct _Node {
	Element element;
	struct _Node * next;
} Node;
	

typedef struct {
	int error;
	Node * first;
	Node * last;	
} Queue;

Queue   QUEUE_create ();
void    QUEUE_add (Queue * queue, Element element);
void    QUEUE_remove (Queue * queue);
Element QUEUE_getFirst (Queue * queue);
int     QUEUE_isEmpty (Queue queue);
int		QUEUE_isFull (Queue queue);
int 	QUEUE_getErrorCode (Queue queue);
void    QUEUE_destroy (Queue * queue);

#endif