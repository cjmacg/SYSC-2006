/* SYSC 2006 Lab 10
   A module that implements a singly-linked list of integers. 
 */

#include <assert.h>  // assert
#include <stdlib.h>  // malloc, free
#include <stdbool.h>
#include <stdio.h>   // printf

#include "singly_linked_list.h"

/*************************************************************
 * Functions presented in lectures.
 *************************************************************/

/* Parameter head points to the first node in a linked list, or is NULL
   if the linked list is empty. Insert a node containing the specified 
   integer value at the front of the linked list, and return a pointer to 
   the first node in the modified list.

   Terminate (via assert) if memory for the node cannot be allocated.
 */
intnode_t *push(intnode_t *head, int value)
{
    intnode_t *p = malloc(sizeof(intnode_t));
    assert (p != NULL);
    p->value = value;
    p->next = head;
    return p;
}

/* Parameter head points to the first node in the list.
   Return the length of a linked list (0 if the linked list is empty). 
 */
int length(intnode_t *head)
{
    int count = 0;
    for (intnode_t *curr = head; curr != NULL; curr = curr->next) {
        count += 1;
    }
    return count;
}

/* Parameter head points to the first node in a linked list.
   Print the linked list, using the format:
       value1 -> value2 -> value3 -> ... -> last_value
 */
void print_list(intnode_t *head)
{
    if (head == NULL) {
        printf("empty list");
        return; 
    }

    intnode_t *curr;

    /* The loop prints a every node in the linked list except the last one,
       using the format "value -> ", where "->" represents the link from each node
       to the following node.

       Notice that the loop condition is:
           curr->next != NULL
       and not:
           curr != NULL

       During the last iteration, the value in the second-last node is
       printed, then curr is updated to point to the last node. The
       condition curr->next != NULL now evaluates to false, so the 
       loop exits, with curr pointing to the last node (which has  
       not yet been printed.) 
     */

    for (curr = head; curr->next != NULL; curr = curr->next) {
        printf("%d -> ", curr->value);
    }

    /* Print the last node. */
    printf("%d", curr->value);
}



/*****************************************************************
 * Solutions to New Exercises
 *****************************************************************/

// Exercise 1

/* Parameter head points to the first node in a linked list, or is
 * NULL if the list is empty.
 *
 * Count the number of nodes in the linked list that contain an integer
 * equal to target, and return that count.
 * 
 * Return 0 if the linked list is empty.
 */ 
int count(intnode_t *head, int target)
{
    //ran an assert here but not supposed to, rather return 0 like this
    // if (head == NULL) return 0;
    //arguably this wasn't necessary either cuz for loop just returns count being 0 lol

    int count = 0;
    intnode_t *curr;
    for (curr = head; curr != NULL; curr = curr->next) {
        if (curr->value == target) {
            count += 1;
        }
    }

    return count;
} 

// Exercise 2

/* Parameter head points to the first node in a linked list, or is
 * NULL if the list is empty.
 *
 * Return the largest integer in the linked list.
 *
 * The function terminates (via assert) if the linked list is empty.
 */
int max_value(intnode_t *head)
{
    //this one does use assert, see definition above
    assert(head != NULL);


    // considered this, but if largest value is negative, this may falsely return 0
    //honestly test cases are a little lacking on this, but wtv!
    // int max = 0;
    int max = head -> value; //hardset head value to the max, NOT zero.
    intnode_t *curr = head -> next; //initialize current node pointer, which is the second
    //we have to start on second node and hardset the first value as max
    for (curr; curr != NULL; curr = curr->next) {
        if (curr->value > max) {
            max = curr->value;
        }
    }


    return max;
}

/*
 *
*  // OK this does not work, as max has to be initalized to something
    //to compare it, which its not here. But, we can't set to zero without
    //the functino failing for any sequences only containing negative numbers
    int max;

    // for (initial condition, end condition, step instruction
    for (intnode_t* curr = head; curr != NULL; curr = curr->next) {
        if (curr->value > max) {
            max = curr->value;
        }
    }

    return max;

 */






// Exercise 3

/* Parameter head points to the first node in a linked list, or is
 * NULL if the list is empty.
 *
 * Return the index (position) of the first node that contains an 
 * integer equal to target. The first node is at index 0, the second node
 * is at index 1, etc.
 *
 * Return -1 if target is not in the linked list, or if the linked list
 * is empty.
 */
int value_index(intnode_t *head, int target)
{
    intnode_t *curr = head;


    //screw it, while loop would look clean here instead of for loop
    int index = 0;
    bool hit = false;
    while (curr != NULL) {
        if (curr -> value == target) {
            return index;
        }
        else {
            index ++;
            curr = curr -> next;
        }
    }

    return -1; //if we get to the end of list without a hit, we return -1
    //also handles empty list immediately, skipping while loop
}


// Exercise 4

/* Parameter head points to the first node in a linked list, or is
 * NULL if the list is empty.
 *
 * Parameter other points to the first node in a linked list, or is
 * NULL if the list is empty.
 *
 * Extend the linked list pointed to by head so that it contains
 * copies of the values stored in the linked list pointed to by other.
 *
 * The function terminates (via assert) if the the linked list 
 * pointed to by head is empty.
 */
void extend(intnode_t *head, intnode_t *other)
{



    assert(head != NULL);

    intnode_t *currO = other;
    intnode_t *currH = head;

    //I think it would be more efficient to use the tailpointer finding
    //while loop outside the for loop, not to do it every iteration
    //rather hard set the tail pointers address every time

    for (currO; currO != NULL; currO = currO->next) {
        while (currH -> next != NULL) {
            currH = currH -> next;
        }

        intnode_t *p = malloc(sizeof(intnode_t));
        assert (p != NULL);
        p->value = currO -> value;
        p->next = NULL;
        currH -> next = p;
    }
}


/*
Had the thought of just tacking on the pointer to the front of the other list
to the tail's next one, but couldn't get it to work.
assert(head != NULL);


    intnode_t *curr = head;
    while (curr -> next != NULL) {
        curr = curr -> next;
    }
    curr -> next = other;
 */




// Exercise 5

/* Parameter head points to the first node in a linked list, or is
 * NULL if the list is empty.
 *
 * The function terminates (via assert) if the linked list is empty.
 *
 * Copy the value in the head node to the location pointed to by
 * parameter popped_value, delete the head node, and return a pointer
 * to the first node in the modified list.
 */
intnode_t *pop(intnode_t *head, int *popped_value)
{

    assert(head != NULL);
    *popped_value = head -> value;

    intnode_t *newHead = head -> next;

    free(head);

    return newHead;
}

