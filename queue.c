/*
 * Code for basic C skills diagnostic.
 * Developed for courses 15-213/18-213/15-513 by R. E. Bryant, 2017
 * Modified to store strings, 2018
 */

/*
 * This program implements a queue supporting both FIFO and LIFO
 * operations.
 *
 * It uses a singly-linked list to represent the set of queue elements
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "harness.h"
#include "queue.h"

/*
  Create empty queue.
  Return NULL if could not allocate space.
*/
queue_t *q_new()
{
    queue_t *q = malloc(sizeof(queue_t));
    /* What if malloc returned NULL? */
    /* the following is going to solve the problem asked above */
    if (q == NULL)
        return NULL;
    /* note that we need to initialize more member if we add more member later
     */
    q->head = NULL;
    q->tail = NULL;
    q->eleCount = 0;
    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    /* How about freeing the list elements and the strings? */
    /* Free queue structure */
    if (q == NULL)
        return; /* nothing to free */
    list_ele_t *next = q->head, *tmp;

    while (next) {
        tmp = next->next;
        free(next->value);
        free(next);
        next = tmp;
    }
    free(q);
}

/*
  Attempt to insert element at head of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_head(queue_t *q, char *s)
{
    if (q == NULL)
        return false;
    list_ele_t *newh;
    /* What should you do if the q is NULL? */
    newh = malloc(sizeof(list_ele_t));
    if (newh == NULL)
        return false;
    /* Don't forget to allocate space for the string and copy it */
    /* What if either call to malloc returns NULL? */

    newh->value = malloc((strlen(s) + 1) * sizeof(char));
    if (newh->value == NULL) {
        free(newh);
        return false;
    }
    strcpy(newh->value, s);
    newh->value[strlen(s)] = '\0'; /* last element of the string */

    newh->next = q->head;
    q->head = newh;
    if (q->tail == NULL)
        q->tail = newh;

    q->eleCount++;
    return true;
}


/*
  Attempt to insert element at tail of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_tail(queue_t *q, char *s)
{
    /* You need to write the complete code for this function */
    /* Remember: It should operate in O(1) time */
    if (q == NULL)
        return false;
    list_ele_t *newt;
    newt = malloc(sizeof(list_ele_t));
    if (newt == NULL)
        return false;
    newt->next = NULL;
    newt->value = malloc((strlen(s) + 1) * sizeof(char));
    if (newt->value == NULL) {
        free(newt);
        return false;
    }
    strcpy(newt->value, s);
    newt->value[strlen(s)] = '\0';

    /* update the node */
    if (q->head == NULL)
        q->head = newt;
    else
        q->tail->next = newt;
    q->tail = newt;

    q->eleCount++;
    return true;
}

/*
  Attempt to remove element from head of queue.
  Return true if successful.
  Return false if queue is NULL or empty.
  If sp is non-NULL and an element is removed, copy the removed string to *sp
  (up to a maximum of bufsize-1 characters, plus a null terminator.)
  The space used by the list element and the string should be freed.
*/
bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{
    /* You need to fix up this code. */
    /* Q: difference beteween NULL and empty A: NULL indicate that q has no
       address no address stored, empty indicate that queue has no element
       stored */
    if (q == NULL)
        return false;
    if (q->head == NULL)
        return false;
    /* Q: why struct ELE has size 16 bytes, isn't it just a pointer same
       as list_ele_t? */
    /* ! not sure if bufsize - 1 included null terminator, here we counted */
    list_ele_t *tmp;
    if (sp != NULL) {
        if ((strlen(q->head->value) + 1) < bufsize) {
            strcpy(sp, q->head->value);
            sp[strlen(sp)] = '\0';
        }
    }

    tmp = q->head->next;
    free(q->head->value);
    free(q->head);
    q->head = tmp;

    q->eleCount--;
    return true;
}

/*
  Return number of elements in queue.
  Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    /* You need to write the code for this function */
    /* Remember: It should operate in O(1) time */
    if (q)
        return q->eleCount;
    return 0;
}

/*
  Reverse elements in queue
  No effect if q is NULL or empty
  This function should not allocate or free any list elements
  (e.g., by calling q_insert_head, q_insert_tail, or q_remove_head).
  It should rearrange the existing ones.
 */
void q_reverse(queue_t *q)
{
    /* You need to write the code for this function */
    if (q == NULL)
        return;
    if (q->head == NULL)
        return;
    list_ele_t *previous, *preceding, *tmp;

    if (q->head->next) { /* positive reverse */
        preceding = q->head->next;
        previous = q->head;

        while (preceding) {
            tmp = preceding->next;
            preceding->next = previous;
            previous = preceding;
            preceding = tmp;
        }
        q->head->next = NULL;
    } else if (q->tail->next) { /* negative reverse */
        preceding = q->tail->next;
        previous = q->tail;

        while (preceding) {
            tmp = preceding->next;
            preceding->next = previous;
            previous = preceding;
            preceding = tmp;
        }
        q->tail->next = NULL;
    }
}
