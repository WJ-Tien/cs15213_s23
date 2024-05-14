/**

* @file queue.c

* @brief Implementation of a queue that supports FIFO and LIFO operations.

*

* This queue implementation uses a singly-linked list to represent the

* queue elements. Each queue element stores a string value.

*

* Assignment for basic C skills diagnostic.

* Developed for courses 15-213/18-213/15-513 by R. E. Bryant, 2017

* Extended to store strings, 2018

*

* TODO: fill in your name and Andrew ID

* @author XXX XXX@andrew.cmu.edu

*/

 
#include "queue.h"
#include "harness.h"
#include <stdlib.h>
#include <string.h>
 

/**

* @brief Allocates a new queue

* @return The new queue, or NULL if memory allocation failed

*/

queue_t *queue_new(void) {
    queue_t *q = malloc(sizeof(queue_t));
    /* What if malloc returned NULL? */
    if (q == NULL) {
        return NULL;
    }

    q->head = NULL;
    q->tail = NULL;
    q->que_size = 0;

    return q;
}

 

/**

* @brief Frees all memory used by a queue

* @param[in] q The queue to free

*/

void queue_free(queue_t *q) {

    /* How about freeing the list elements and the strings? */

    /* Free queue structure */

    if (q == NULL){
        return;

    }

    list_ele_t *cur_head = q->head;
    while (cur_head) {
        // free both cur_head (malloced) and string (malloced)
        list_ele_t *tmp_head = cur_head;
        char *tmp_str = cur_head->value;
        cur_head = cur_head->next;
        free(tmp_str);
        free(tmp_head);
    }
    //q -> l1 (head) -> l2 -> NULL
    free(q);

}


/**

* @brief Attempts to insert an element at head of a queue

*

* This function explicitly allocates space to create a copy of `s`.

* The inserted element points to a copy of `s`, instead of `s` itself.

*

* @param[in] q The queue to insert into

* @param[in] s String to be copied and inserted into the queue

*

* @return true if insertion was successful

* @return false if q is NULL, or memory allocation failed

*/

bool queue_insert_head(queue_t *q, const char *s) {

    /* What should you do if the q is NULL? */

    /* Don't forget to allocate space for the string and copy it */

    /* What if either call to malloc returns NULL? */

 

    list_ele_t *newh;
    char *copys;
    newh = malloc(sizeof(list_ele_t));
    copys = (char *)malloc(strlen(s) + 1); //null terminator
 
    if (q == NULL || newh == NULL || copys == NULL){
        free(newh);
        free(copys);
        return false;
    }

    strcpy(copys, s);
    // if q->head is NULL
    if (q->head == NULL){
        q->head = newh;
        q->head->next = NULL; // critical!
        q->head->value = copys;
		q->tail = q->head;
    }

    else {
        list_ele_t *cur_head = q->head;
		q->head = newh;
        q->head->value = copys;
		q->head->next = cur_head;
    }

    q->que_size++;

    return true;
}


/**

* @brief Attempts to insert an element at tail of a queue

*

* This function explicitly allocates space to create a copy of `s`.

* The inserted element points to a copy of `s`, instead of `s` itself.

*

* @param[in] q The queue to insert into

* @param[in] s String to be copied and inserted into the queue

*

* @return true if insertion was successful

* @return false if q is NULL, or memory allocation failed

*/

bool queue_insert_tail(queue_t *q, const char *s) {

	/* You need to write the complete code for this function */

    /* Remember: It should operate in O(1) time */

    list_ele_t *newh;
    char *copys;
    newh = malloc(sizeof(list_ele_t));
    copys = (char *)malloc(strlen(s) + 1); //null terminator

    if (q == NULL || newh == NULL || copys == NULL){
        free(newh);
        free(copys);
        return false;
    }

 

 

    else if (q->head == NULL) {
		strcpy(copys, s);
        q->head = newh;
        q->head->next = NULL;
        q->head->value = copys;
        q->tail = q->head;
    }


    // key of O(1)

    else {
		strcpy(copys, s);
        q->tail->next = newh;
        q->tail->next->value = copys;
        q->tail = q->tail->next;
        q->tail->next = NULL;
    }

	q->que_size++;

    return true;
}

 

/**

* @brief Attempts to remove an element from head of a queue

*

* If removal succeeds, this function frees all memory used by the

* removed list element and its string value before returning.

*

* If removal succeeds and `buf` is non-NULL, this function copies up to

* `bufsize - 1` characters from the removed string into `buf`, and writes

* a null terminator '\0' after the copied string.

*

* @param[in]  q       The queue to remove from

* @param[out] buf     Output buffer to write a string value into

* @param[in]  bufsize Size of the buffer `buf` points to

*

* @return true if removal succeeded

* @return false if q is NULL or empty

*/

bool queue_remove_head(queue_t *q, char *buf, size_t bufsize) {

    /* You need to fix up this code. */

    if (q == NULL || q-> head == NULL) {
        return false;
    }
 
    list_ele_t *tmp = q->head;
    if (q->que_size > 1) {
        q->head = q->head->next;
    }

    else if (q->que_size == 1) {
        q->head = NULL;
    }


    //copy string

    if (buf != NULL && tmp->value != NULL) {
        unsigned long last_loc = 0;
        if (strlen(tmp->value) <= bufsize-1) {
            strncpy(buf, tmp->value, strlen(tmp->value));
            last_loc = strlen(tmp->value);
        }

        else {
            strncpy(buf, tmp->value, bufsize-1);
            last_loc = bufsize - 1;
        }
        buf[last_loc] = '\0';

    }

    free(tmp->value);
    free(tmp);
    q->que_size--;

    return true;
}

 

/**

* @brief Returns the number of elements in a queue

*

* This function runs in O(1) time.

*

* @param[in] q The queue to examine

*

* @return the number of elements in the queue, or

*         0 if q is NULL or empty

*/

size_t queue_size(queue_t *q) {

    /* You need to write the code for this function */

    /* Remember: It should operate in O(1) time */

    if (q == NULL) {
        return 0;
    }

    return q->que_size;
}

 

/**

* @brief Reverse the elements in a queue

*

* This function does not allocate or free any list elements, i.e. it does

* not call malloc or free, including inside helper functions. Instead, it

* rearranges the existing elements of the queue.

*

* @param[in] q The queue to reverse

*/

void queue_reverse(queue_t *q) {

    /* You need to write the code for this function */

    if (q == NULL || q->head == NULL || q->que_size == 1) {
        return;
    }


    list_ele_t *prev = NULL;
    list_ele_t *cur_head = q->head;
    list_ele_t *tmp_head = q->head;
    while (cur_head) {
        list_ele_t *next_ele = cur_head->next;
        cur_head->next = prev;
        prev = cur_head;
        cur_head = next_ele;
    }

    q->head = prev;
    q->tail = tmp_head;
}
