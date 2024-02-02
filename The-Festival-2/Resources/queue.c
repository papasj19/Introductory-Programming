/*
  Spencer Johnson : May 9, 2021
  Project 2.3 Programming M and T 

  The file given to us from the estudy. 
  This proved to be the most crucial piece of the puzzle when completing this project. It was very nice having this as an assist. 

  This file contains all the possible actions i can do with my dynamic queue 
    Utilizing a queue was FIFO situation 
*/
#include "queue.h"

Queue   QUEUE_create () {
	Queue queue;
	Node * phantomNode = NULL;

	phantomNode = (Node*) malloc(sizeof(Node));
	if (NULL == phantomNode) {
		queue.error = QUEUE_ERROR_MALLOC;
	}
	else {
		queue.error = QUEUE_NO_ERROR;

		queue.first = phantomNode;
		queue.last = phantomNode;

		phantomNode->next = NULL;
	}

	return queue;
}


void    QUEUE_add (Queue * queue, Element element) {
	Node * node = NULL;

	// Petition memory for a new node.
	node = (Node*) malloc (sizeof(Node));
	// Check if we got the new node.
	if (NULL == node) {
		queue->error = QUEUE_ERROR_MALLOC;
	}
	else {
		queue->error = QUEUE_NO_ERROR;

		// Set the information to the node.
		node->element = element;
		node->next = NULL;
		
		// Bind the new node after the last current node.
		queue->last->next = node;
		// And set the new node as the last node.
		queue->last = node;

	}
}


void    QUEUE_remove (Queue * queue) {
	Node * aux = NULL;

	if (QUEUE_isEmpty(*queue)) {
		queue->error = QUEUE_ERROR_EMPTY;
	}
	else {
		queue->error = QUEUE_NO_ERROR;

		// Reference the auxiliary pointer to the first valid node (the one after the phantom).
		aux = queue->first->next;
		// Change who the first node is. Now the first node is the node after the first one.
		queue->first->next = queue->first->next->next;
		// Free the first node. The one referenced by aux.
		free(aux);
	
		// Exception: When we remove the last node in a queue, we need to reset who the last node is.
		if (QUEUE_isEmpty(*queue)) {
			queue->last = queue->first;
		}
	}
}


Element QUEUE_getFirst (Queue * queue) {
	Element element;
	
	if (QUEUE_isEmpty(*queue)) {
		queue->error = QUEUE_ERROR_EMPTY;
	}
	else {
		queue->error = QUEUE_NO_ERROR;
		// We get the element contained inside the node after the phantom node.
		element = queue->first->next->element;
	}

	return element;

}


int     QUEUE_isEmpty (Queue queue) {
	// Is there any node after the phantom node?
	return NULL == queue.first->next;
}


int		QUEUE_isFull (Queue queue) {
	// A dynamic queue will never be full (theoretically speaking).
	return 0;
}


int 	QUEUE_getErrorCode (Queue queue) {
	return queue.error;
}
void    QUEUE_destroy (Queue * queue) {
	while (!QUEUE_isEmpty(*queue)) {
		QUEUE_remove(queue);
	}
	// Free the phantom node.
	free(queue->first);
	queue->first = NULL;
	queue->last = NULL;
}
