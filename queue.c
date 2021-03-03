#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "harness.h"
#include "queue.h"

/*
 * Create empty queue.
 * Return NULL if could not allocate space.
 */
queue_t *q_new()
{
    queue_t *q = malloc(sizeof(queue_t));
    /* TODO: What if malloc returned NULL? */
    if (q == NULL)
        return q;
    q->head = NULL;
    q->tail = NULL;
    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    /* TODO: How about freeing the list elements and the strings? */
    /* Free queue structure */
    free(q);
}
/* * Attempt to insert element at head of queue.  * Return true if successful.
 * * Return false if q is NULL or could not allocate space.  * Argument s points
 * to the string to be stored.  * The function must explicitly allocate space
 * and copy the string into it.  */
bool q_insert_head(queue_t *q, char *s)
{
    /* TODO: What should you do if the q is NULL? */
    if (q == NULL)
        return false;
    lsit_ele_t *newh = malloc(sizeof(list_ele_t));
    if (newh == NULL) {
        free(newh);
        return false;
    }
    char *tmp = malloc(strlen(s) + 1);
    if (tmp == NULL) {
        free(tmp);
        free(newh);
        return false;
    }
    strncpy(tmp, s, strlen(s) + 1);
    newh->value = tmp;
    /* Don't forget to allocate space for the string and copy it */
    /* What if either call to malloc returns NULL? */
    newh->next = q->head;
    q->head = newh;
    if (q->tail == NULL)
        q->tail = newh->next;
    return true;
}

/*
 * Attempt to insert element at tail of queue.
 * Return true if successful.
 * Return false if q is NULL or could not allocate space.
 * Argument s points to the string to be stored.
 * The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_tail(queue_t *q, char *s)
{
    /* TODO: You need to write the complete code for this function */
    if (q == NULL)
        return false;
    lsit_ele_t *newt = malloc(sizeof(list_ele_t));
    if (newt == NULL) {
        free(newt);
        return false;
    }
    char *tmp = malloc(strlen(s) + 1);
    if (tmp == NULL) {
        free(tmp);
        free(newt);
        return false;
    }
    strncpy(tmp, s, strlen(s) + 1);
    newt->next = NULL;
    newt->value = tmp;
    q->tail->next = newt;
    q->tail = newt;
    /* Remember: It should operate in O(1) time */
    /* TODO: Remove the above comment when you are about to implement. */
    return true;
}

/*
 * Attempt to remove element from head of queue.
 * Return true if successful.
 * Return false if queue is NULL or empty.
 * If sp is non-NULL and an element is removed, copy the removed string to *sp
 * (up to a maximum of bufsize-1 characters, plus a null terminator.)
 * The space used by the list element and the string should be freed.
 */
bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{
    /* TODO: You need to fix up this code. */
    /* TODO: Remove the above comment when you are about to implement. */
    if (q == NULL || q->head == NULL)
        return false;
    sp = malloc(sizeof(char) * (bufsize + 1));
    for (int i = 0; i < bufsize; i++)
        sp[i] = q->head->value[i];
    sp[bufsize] = '\0';
    free(q->head->value);
    free(q->head->next);
    q->head = q->head->next;
    return true;
}

/*
 * Return number of elements in queue.
 * Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    /* TODO: You need to write the code for this function */
    /* Remember: It should operate in O(1) time */
    /* TODO: Remove the above comment when you are about implement. */
    return q->size;
}

/*
 * Reverse elements in queue
 * No effect if q is NULL or empty
 * This function should not allocate or free any list elements
 * (e.g., by calling q_insert_head, q_insert_tail, or q_remove_head).
 * It should rearrange the existing ones.
 */
void q_reverse(queue_t *q)
{
    /* TODO: You need to write the code for this function */
    if (q != NULL && q->head != NULL) {
        list_ele_t *tmp = q->head->next;
        lsit_ele_t *tmp2;
        q->head->next = NULL;
        while (tmp != NULL) {
            tmp2 = tmp->next;
            tmp->next = q->head;
            q->head = tmp;
            tmp = tmp2;
        }
        q->head = tmp;
    }
    /* TODO: Remove the above comment when you are about to implement. */
}

/*
 * sort elements of queue in ascending order
 * No effect if q is NULL or empty. In addition, if q has only one
 * element, do nothing.
 */
void q_sort(queue_t *q)
{
    /* TODO: You need to write the code for this function */

    /* TODO: Remove the above comment when you are about to implement. */
}
