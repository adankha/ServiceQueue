#include <stdio.h>
#include <stdlib.h>
#include "sq.h"



typedef struct node{
    int val;    
    struct node *next;
    struct node *previous;
}NODE;



typedef struct list_struct{	 // Pointers to point to front/back nodes.
    NODE *front;
    NODE *back;
    int length;
    int newNumber;
    int arraySize;
}LIST;



LIST *lst_create(){
    
    LIST *l = malloc(sizeof(LIST));
    
    l->front = NULL;		// Points to front of list.
    l->back = NULL;		// Points to back of list.
    l->length = 0;		// Length of queue list
    l->newNumber = -1;		// used to create a new number buzzer ID
    l->arraySize = 2;		// Used to realloc if more pointers are needed in the array.
    return l;
};  




struct service_queue{		// Struct that holds the linked lists and the array of pointers.
    LIST * the_queue;
    LIST * buzzer_bucket;
    NODE **arr;
};

// Returns pointer to newly created empty list for the que and buzzer bucket.
SQ *sq_create(){
    
    SQ *q = malloc(sizeof(SQ));
    
    // Create an array of pointers pointing to each node
    q->arr = malloc(sizeof(NODE*));
    
    // Create an empty list for the_queue
    q->the_queue = lst_create();
    
    // Create an empty list for buzzer_bucket
    q->buzzer_bucket = lst_create();
    
    return q;			 // Return the SQ pointer for the two lists.
}



void sq_display(SQ *q){
    
    printf("The current-queue contents:\n");
    NODE *p = q->the_queue->front;
    printf("[");
    while(p != NULL){
        printf("%d ", p->val);
        p = p->next;
    }
    printf("]\n");    
}



void sq_free(SQ* q){

    NODE* temp = q->the_queue->front;
    NODE *pnext;
    
    // Deletes the linked list: the_queue
    while ( temp != NULL ){
        pnext = temp->next;
        free(temp);
        temp = pnext;
    }
    free (q->the_queue);
    
    temp = q->buzzer_bucket->front;
    // Deletes the linked list: buzzer_bucket
    while(temp!= NULL){
        pnext = temp->next;
        free(temp);
        temp = pnext;
    }
    free(q->buzzer_bucket);   

    // Deletes the array of pointers
    free(q->arr);

    // Free the service queue
    free(q);    
}


// Returns the link of the queue.
int sq_length(SQ* q){
    return q->the_queue->length;
}



int push_front_que(SQ* q, int val){
    
    if (val  >= q->the_queue->newNumber){	// Reallocs memory for the array of pointers. Dependent on the # of nodes in the_queue.
        q->arr = realloc(q->arr, (q->the_queue->arraySize*2)*(sizeof(NODE*)));
        q->the_queue->arraySize *= 2;
    }
        
    NODE *p = malloc(sizeof(NODE));
    p->val = val;				// Store the value into the node.
    q->the_queue->length++;			// Since we are pushing, we increment our counter.   
    p->next = q->the_queue->front;		// Set the "future" head to point to current head to push front
    
    if( q->the_queue->front == NULL){
        q->the_queue->front = p;
        q->the_queue->back = p;
        q->the_queue->front->previous = NULL;
    }
    else{
        q->the_queue->front->previous = p;      // Set the previous of the head of list to point to new node
        q->the_queue->front = p;		// Set the new head of the list to the new node that's pushed
        p->previous = NULL;			// Set the previous of the head to be NULL
    }
}



int pop_front_que(SQ* q){
    
    int ret_val;    
    NODE *p;
    
    if(q->the_queue->front == NULL){		// Returns if list is empty.
        return;
    }
    
    q->the_queue->length--;			// Popping, so decrement length counter.
    ret_val = q->the_queue->front->val;		// Store the value that will be popped.
    
    if (q->the_queue->front == q->the_queue->back){
        free(q->the_queue->front);
        q->the_queue->front = NULL;
        q->the_queue->back = NULL;
    }
    else{
        p = q->the_queue->front;				// Hold the first node in list.
        q->the_queue->front = q->the_queue->front->next;        // Reassign the front to be the next node
        q->the_queue->front->previous = NULL;			// Reassign previous of the head of the list to be NULL.
        free(p);
    }
    return ret_val;
}



int push_back_que(SQ* q, int val){
    
    if(q->the_queue->back == NULL){				// If the list is empty, do a push front.
        push_front_que(q, val);
    }
    else{							
        
        if (val  >= q->the_queue->newNumber){			// Since we are pushing onto the queue, we want to make sure that we have enough pointers in our array that point to all the nodes in the list
            q->arr = realloc(q->arr, (q->the_queue->arraySize*2)*(sizeof(NODE*)));
            q->the_queue->arraySize *= 2;
        }
        
        NODE *p = malloc(sizeof(NODE));
        p->val = val;
        p->next = NULL;
        p->previous = q->the_queue->back;
        q->the_queue->back->next = p;
        q->the_queue->back = p;
        q->the_queue->length++;
    }     
}



int push_front_buzz(SQ* q, int val){
    
    NODE *p = malloc(sizeof(NODE));
    p->val = val;				// Store the value into the node.
    q->buzzer_bucket->length++;			// Since we are pushing, we increment our counter.   
    p->next = q->buzzer_bucket->front;		// Set the "future" head to point to current head to push front
    
    if( q->buzzer_bucket->front == NULL){
        q->buzzer_bucket->front = p;
        q->buzzer_bucket->back = p;
        q->buzzer_bucket->front->previous = NULL;
    }
    else{
        q->buzzer_bucket->front->previous = p;       // Set the previous of the head of list to point to new node
        q->buzzer_bucket->front = p;		     // Set the new head of the list to the new node that's pushed
        p->previous = NULL;			     // Set the previous of the head to be NULL
    }
}



int pop_front_buzz(SQ* q){
    
    int ret_val; 
    NODE *p;
    
    if(q->buzzer_bucket->front == NULL){
        return;
    }
    q->buzzer_bucket->length--;
    ret_val = q->buzzer_bucket->front->val;
    
    if (q->buzzer_bucket->front == q->buzzer_bucket->back){
        free(q->buzzer_bucket->front);
        q->buzzer_bucket->front = NULL;
        q->buzzer_bucket->back = NULL;
    }
    else{
        p = q->buzzer_bucket->front;				// Hold the first node in list.
        q->buzzer_bucket->front = q->buzzer_bucket->front->next;// Reassign the front to be the next node
        q->buzzer_bucket->front->previous = NULL;		// Reassign previous of the head of the list to be NULL.
        free(p);
    }
    return ret_val;
}



int sq_give_buzzer(SQ *q){
    
    int buzzer;
    if( q->buzzer_bucket->front != NULL){	// Checks to see if there is a buzzer in the bucket (bucket is a number that was already used in the queue)
        buzzer = pop_front_buzz(q);		// Assign buzzer to the most recent buzzer # pushed into the buzzer_bucket list
        push_back_que(q, buzzer);               // Push the number to the queue list
        q->arr[buzzer] = q->the_queue->back;    // Point to the buzzer #
        return buzzer;
    }
    else{
        q->the_queue->newNumber++;		// If no used number is found in the bucket list, create a new number ID for the buzzer
        buzzer = q->the_queue->newNumber;
        push_back_que(q, buzzer);		// Push into queue
        q->arr[buzzer] = q->the_queue->back;	// Assign the pointer in array to point to that node
        return buzzer;
    }
}



int sq_seat(SQ *q){
    
    int buzzer;
    
    if (q->the_queue->front == NULL)		// If there is nothing in the que, return -1 indicating that
        return -1; 
    else{
        buzzer = pop_front_que(q);		// Otherwise, seat the the buzzer that is in the front of the list.
        push_front_buzz(q, buzzer);
        q->arr[buzzer] = NULL;
        return buzzer;
    }
}



int sq_kick_out(SQ *q, int buzzer){
    
    if ( q->arr[buzzer] == NULL || buzzer > q->the_queue->newNumber || buzzer < 0){	// If the buzzer asked to kick out is not in the queue, prompt an error message.
        printf("Sorry #%d buzzer not found.\n", buzzer);
        return 0;
    }
    if(q->arr[buzzer] == q->the_queue->front && q->the_queue->front == q->the_queue->back){ 	// Condition that checks to see if the buzzer is the only buzzer in the list.
        q->the_queue->length--;		// Decrement the counter
        NODE *temp = q->arr[buzzer];	
        free(temp);			// Free the node
        q->the_queue->front = NULL;	// Reassign head and back and the array corresponding to that number to NULL.
        q->the_queue->back = NULL;
        q->arr[buzzer] = NULL;
        push_front_buzz(q, buzzer);	// Push it to the bucket list
        return 1;		
    }
    if(q->arr[buzzer] == q->the_queue->front){	// Same idea, but checks to see if it's in the front, but not in the back
        q->the_queue->length--;
        NODE *temp = q->arr[buzzer];
        temp->next->previous = temp->previous;
        q->the_queue->front = q->the_queue->front->next;
        free(temp);
        q->arr[buzzer] = NULL;
        push_front_buzz(q, buzzer);
        return 1;
    }
    else if(q->arr[buzzer] == q->the_queue->back){ 	// Checks to see if it's only in the back of the list
        q->the_queue->length--;				
        NODE *temp = q->arr[buzzer];			
        temp->previous->next = temp->next;		
        q->the_queue->back = q->the_queue->back->previous;
        free(temp);
        q->arr[buzzer] = NULL;
        push_front_buzz(q, buzzer);
        return 1;
    }    
    else{				// Checks the in-between condition of kicking out
        q->the_queue->length--;
        NODE *temp = q->arr[buzzer];
        temp->previous->next = temp->next;
        temp->next->previous = temp->previous;
        free(temp);
        q->arr[buzzer] = NULL;
        push_front_buzz(q, buzzer);
        return 1;
    }    
}



int sq_take_bribe(SQ *q, int buzzer){
    
    if ( q->arr[buzzer] == NULL || buzzer > q->the_queue->newNumber || buzzer < 0){	// Checks to see if buzzer exist
        printf("Sorry #%d buzzer not found.\n", buzzer);
        return 0;
    }
    
    if(q->arr[buzzer] == q->the_queue->front){						// Checks to see if it's already at the front of the list.
        printf("You are already at the front of the list, but I'll take your money!\n");
        return 1;
    }
    
    if (q->arr[buzzer] == q->the_queue->front && q->the_queue->front == q->the_queue->back && q->the_queue->length == 1){	// Checks to see if it's the only one in the list
        printf("You're the only one in the que, but I'll take your money.\n");
        return 1;
    }
    
    else if( q->arr[buzzer] == q->the_queue->back){	// Checks to see if it's in the back of the list
        NODE *temp = q->arr[buzzer];			
        temp->previous->next = temp->next;		// Reassign the prnode's next member to point to the next node.
        q->the_queue->back = temp->previous;		// Reassign the back pointer to point to the 2nd to last node
        temp->previous = NULL;				// Since we are pushing temp to the front, the previous will be NULL
        q->the_queue->front->previous = temp;		// The "old" front pointer previous member must point to temp
        temp->next = q->the_queue->front;		// The "new" node that is in the front of the list, it's next member must point to the "old" front node
        q->the_queue->front = temp;			// Reassign the pointer to point to the updated head of the list
        return 1;
    }
    else{        
        NODE *temp = q->arr[buzzer];			// Very similar to the above comments, only instead this satisfies the node(s) in the middle of the list. (So the back doesn't need to be updated).
        temp->previous->next = temp->next;
        temp->next->previous = temp->previous;
        temp->next = q->the_queue->front;
        q->the_queue->front->previous = temp;
        temp->previous = NULL;
        q->the_queue->front = temp;       
        return 1;
    }    
}

