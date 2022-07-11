#include

#include

#include

#include "PrintError.h"

class CLMutex;

CLMutex* g_pMutex;

#define CAS(ptr, oldvalue, newvalue) \
    __sync_bool_compare_and_swap(ptr, oldvalue, newvalue)

template

    struct Node

{
    undefined

        T* data;

    Node* next;
};

template

    struct Queue

{
    undefined

        Node* head;

    Node* tail;
};

template

    Queue*

    queueNew(void)

{
    undefined

        Node* tmp = new Node;

    Queue* queue = new Queue;

    queue->head = queue->tail = tmp;

    return queue;
}

Queue* myqueue;

template

    void

    queuePush(Queue* queue, T* data)

{
    undefined

        Node* onenode = new Node;

    onenode->data = data;

    onenode->next = NULL;

    Node* tail;

    Node* next;

    while (true)

    {
        undefined

            tail = queue->tail;

        next = tail->next;

        if (tail != queue->tail) continue;

        if (next != NULL)

        {
            undefined

                CAS(&queue->tail, tail, next);

            continue;
        }

        if (CAS(&tail->next, next, onenode)) break;
    }

    CAS(&queue->tail, tail, onenode);
}

template

    T*

    queuePop(Queue* queue)

{
    undefined

        Node* head;

    Node* tail;

    Node* next;

    T* data = NULL;

    while (true)

    {
        undefined

            head = queue->head;

        tail = queue->tail;

        next = head->next;

        if (head != queue->head) continue;

        if (next == NULL) return NULL;

        if (head == tail)  // prevent head exceed tail

        {
            undefined

                CAS(&queue->tail, tail, next);

            continue;
        }

        data = next->data;

        if (CAS(&queue->head, head, next)) break;
    }

    delete head;

    return data;
}
