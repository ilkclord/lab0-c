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
    q->tail = q->head;
    q->size = 0;
    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    /* TODO: How about freeing the list elements and the strings? */
    if (q != NULL) {
        while (q->head != NULL) {
            list_ele_t *tmp = q->head->next;
            free(q->head->value);
            free(q->head);
            q->head = tmp;
        }
        /* Free queue structure */
        free(q);
    }
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
    list_ele_t *newh = malloc(sizeof(list_ele_t));
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
    strncpy(tmp, s, strlen(s));
    tmp[strlen(s)] = '\0';
    if (q->head == NULL)
        q->tail = newh;
    newh->value = tmp;
    /* Don't forget to allocate space for the string and copy it */
    /* What if either call to malloc returns NULL? */
    newh->next = q->head;
    q->head = newh;
    q->size = q->size + 1;
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
    list_ele_t *newt = malloc(sizeof(list_ele_t));
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
    strncpy(tmp, s, strlen(s));
    tmp[strlen(s)] = '\0';
    newt->next = NULL;
    newt->value = tmp;
    if (q->tail == NULL) {
        q->tail = newt;
        q->head = newt;
        return true;
    }
    q->tail->next = newt;
    q->tail = newt;
    q->size = q->size + 1;
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
    if (sp != NULL) {
        strncpy(sp, q->head->value, bufsize - 1);
        sp[bufsize - 1] = '\0';
    }
    list_ele_t *tmp = q->head->next;
    free(q->head->value);
    free(q->head);
    q->head = tmp;
    q->size = q->size - 1;
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
    if (q == NULL || q->head == NULL)
        return 0;
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
    if (q != NULL && q->head != NULL && q->head->next != NULL) {
        q->tail = q->head;
        list_ele_t *tmp = q->head->next;
        list_ele_t *tmp2 = NULL;
        q->head->next = NULL;
        while (tmp != NULL) {
            tmp2 = tmp->next;
            tmp->next = q->head;
            q->head = tmp;
            tmp = tmp2;
        }
    }
    /* TODO: Remove the above comment when you are about to implement. */
}

/*
 * sort elements of queue in ascending order
 * No effect if q is NULL or empty. In addition, if q has only one
 * element, do nothing.
 */
list_ele_t *merge(list_ele_t *q1, list_ele_t *q2)
{
    list_ele_t *leads = NULL, *root;
    if (strcmp(q1->value, q2->value) < 0) {
        leads = q1;
        q1 = q1->next;
    } else {
        leads = q2;
        q2 = q2->next;
    }
    root = leads;
    while (q1 != NULL && q2 != NULL) {
        if (strcmp(q1->value, q2->value) < 0) {
            leads->next = q1;
            q1 = q1->next;
        } else {
            leads->next = q2;
            q2 = q2->next;
        }
        leads = leads->next;
    }
    if (q1 == NULL)
        leads->next = q2;
    else
        leads->next = q1;
    return root;
}
list_ele_t *merge_find(int a, list_ele_t *root)
{
    while (a > 1) {
        root = root->next;
        a = a - 1;
    }
    return root;
}
list_ele_t *merge_split(list_ele_t *root, int size)
{
    if (size / 2 > 0) {
        list_ele_t *tmp = merge_find(size / 2, root);
        list_ele_t *q2 = tmp->next;
        tmp->next = NULL;
        root = merge_split(root, size / 2);
        q2 = merge_split(q2, size - size / 2);
        return merge(root, q2);
    } else {
        root->next = NULL;
        return root;
    }
}
void q_sort(queue_t *q)
{
    /* TODO: You need to write the code for this function */
    if (q == NULL || q->head == NULL || q->head->next == NULL)
        return;
    q->head = merge_split(q->head, q->size);
    q->tail = merge_find(q->size, q->head);
    /* TODO: Remove the above comment when you are about to implement. */
}
