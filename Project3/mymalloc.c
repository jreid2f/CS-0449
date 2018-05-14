/*
  Joseph Reidell
  My Custom Malloc
  Project 3
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// A structure that is a node for the linked list
struct node{
        int size_of_mem;
        int occ; // checks whether the node is free or not
        struct node *next;
        struct node *previous;
};

/*
  first is used as the current node in the list
  last is used as the tail of the list
  head is used as the beginning of the list
*/
struct node *first = 0;
struct node *last = 0;
struct node *head = 0;

// Function prototype used for the worst fit algorithm
void* largest_space(int);

void* my_worstfit_malloc(int size){
	
	// Checks the current address for the memory in sbrk
	void *address = sbrk(0);
	
	// Checks if we are at the beginning of the linked list
	if(head == 0){
	   
	   // This moves the pointer to the head of the list
	   sbrk(size + sizeof(struct node));
	   
	   /*
	      This sets the node to be the beginning of the linked list
	      Everything is mostly set to 0 or the beginning of the list
	   */
	   head = address;
	   head->size_of_mem = size;
	   head->occ = 0;
	   head->next = 0;
	   head->previous = 0;
	   last = head;
	   first = head;		   
	}

	/*
	   If it is not the beginning of the linked list
	   This will use the worst fit algorithm to check 
	   for the next chunk to place the data.
	*/
	else{
	   struct node* largest_chunk = largest_space(size);

	   if(largest_chunk == 0){
		sbrk(size + sizeof(struct node));
		last = (struct node*) address;
		last->occ = 0;
		last->size_of_mem = size;
		last->previous = first;
		last->next = 0;

		first->next = last;
		first = last;
	   }

	   else{
		largest_chunk->occ = 0;

		/*
		  If there is more space in the chunk of memory, 
		  then allocate that into a new node. It will then 
		  check if there is enough space to allocate the new node
		  along with the chunk of memory.
		*/
		int node_allocation = largest_chunk->size_of_mem;
		
		if(node_allocation > (size + sizeof(struct node))){
		   struct node* new_node = ((void*) largest_chunk) + sizeof(struct node) + size;

		   new_node->occ = 1;
		   new_node->size_of_mem = node_allocation - size;
		   new_node->previous = largest_chunk;
		   new_node->next = largest_chunk->next;
		   largest_chunk->next = new_node;
		   largest_chunk->size_of_mem = size;
		}
		
		// Return the chunk of memory that was determined to be large enough
		return ((void*) largest_chunk) + sizeof(struct node);
	   }
	}
	
	// Return the memory address that allocated the new memory from the heap
	return address + sizeof(struct node);

}

// My created free function
void my_free(void *ptr){
	int temp;
	struct node *point;
	struct node *prev, *nxt;

	if(ptr == NULL){
	   return;
	}

	point = (struct node *)((char *)ptr - sizeof(struct node));
	prev = point->previous;
	nxt = point->next;
	point->occ = 0;
	
	// if the node is null it will reduce the size of the heap
	if(nxt == NULL){
	   
	   if(prev == NULL)
	   {
		head = first = last = NULL;
		sbrk(0 - point->size_of_mem);
		return;
	   }
	   else
	   {
		if(prev->occ == 1 && prev != 0)
		{
		   prev = prev->previous;
	   	}
	    }
	}
	
	// This will coalese the adjacent free blocks
	else 
	{
		if(nxt != NULL && nxt->occ == 0) 
		{
			// combine the current node with the next node
			temp = nxt->size_of_mem;
			point->next = nxt->next;
			if(point->next!= NULL)point->next->previous = point;
			point->size_of_mem += temp;
		        nxt = point->next;
		}

		// Updates nxt node if neccassary 
		if(prev != NULL && prev->occ == 1) 
		{
			if(nxt != 0 && nxt->occ == 1){
			   prev->next = nxt->next;
			   prev->size_of_mem += point->size_of_mem + nxt->size_of_mem + 2 * sizeof(struct node);
			}

			else{
			   prev->next = nxt;
			   prev->size_of_mem += point->size_of_mem + sizeof(struct node);
			}
		}
	}
}


void* largest_space(int area){
	// Keeps track of the block that works with worst fit
	struct node* large_block = 0;

	/*
	   Uses the head of the linked list to traverse through
	   it to help find the largest block 
	*/
	struct node* curr = head;

	/*
	  This loop traverses through the linked list and looks 
	  for the largest block that works for worst fit
	*/
	while(curr != last && curr != 0){
		if(large_block == 0){
		   if(curr->size_of_mem >= area && curr->occ == 1){
			// Sets largest block if parameters are met
			large_block = curr;
		   }
		}
		
		else{
		  if(curr->size_of_mem > large_block->size_of_mem && curr->occ == 1){
			// Sets largest block if parameters are met
			large_block = curr;
		  }
		}
		
		/* 
		  If the block is not large enough, 
		  it will move to the next block
		*/
		curr = curr->next;
	}

	// This checks if the largest block for worst fit is the last node
	if(curr != 0 && curr->size_of_mem >= area && curr->occ == 1){
	   if(large_block == 0){
		large_block = curr;
	   }

	   else if(curr->size_of_mem > large_block->size_of_mem){
		large_block = curr;
	   }
	}

	// returns the largest block that is found
	return large_block;

}
