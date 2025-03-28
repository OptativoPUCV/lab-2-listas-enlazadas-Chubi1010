#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct Node Node;

struct Node {
    void * data;
    Node * next;
    Node * prev;
};

struct List {
    Node * head;
    Node * tail;
    Node * current;
};

typedef List List;

Node * createNode(void * data) {
    Node * new = (Node *)malloc(sizeof(Node));
    assert(new != NULL);
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

List * createList() {
    List* list =(List*) malloc (sizeof(List));
    if(list == NULL) {
        return NULL;
    }
    list->head=NULL;
    list->tail=NULL;
    list->current=NULL;
    return list;
}

void * firstList(List * list) 
{
    if (list == NULL || list->head == NULL) return NULL;
    list->current = list->head;
    return list->current->data;
}

void * nextList(List * list) {
    if (list == NULL || list->current == NULL) return NULL;
    list->current = list->current->next;
    if (list->current == NULL) return NULL;
    return list->current->data;
}

void * lastList(List * list) {
    if (list == NULL || list->tail == NULL) return NULL;
    list->current = list->tail;
    return list->current->data;
}

void * prevList(List * list) {
    if (list == NULL || list->current == NULL) return NULL;
    list->current = list->current->prev;
    if (list->current == NULL) return NULL;
    return list->current->data;
}

void pushFront(List * list, void * data) 
{
    Node* nuevo = createNode(data);
    nuevo->data = data;
    nuevo->next = list->head;
    nuevo->prev = NULL;
    if (list-> head != NULL)
    {
        list->head->prev = nuevo;
        list->head = nuevo;
    }
    else
    {
        list->head = nuevo;
        list->tail = nuevo;
    }
}
    

void pushBack(List * list, void * data) {
    list->current = list->tail;
    pushCurrent(list,data);
}

void pushCurrent(List * list, void * data) {
    Node* nuevo = createNode(data);
    nuevo->prev = list->current;
    nuevo->next = list->current->next;
    if (list->current->next != NULL)
    {
        list->current->next->prev = nuevo;
    } 
    else 
    {
        list->tail = nuevo;
    }
    list->current->next = nuevo;
}

void * popFront(List * list) {
    list->current = list->head;
    return popCurrent(list);
}

void * popBack(List * list) {
    list->current = list->tail;
    return popCurrent(list);
}

void * popCurrent(List * list) {
    if (list->current == NULL) return NULL;
    void * data = list->current->data;
    if (list->current == list->head)
    {
        if (list->current->next != NULL)
        {
            list->current->next->prev = NULL;
            list->head = list->current->next;
        }
        
    }
    else if(list->current == list->tail)
    {
        if (list->current->prev != NULL)
        {
            list->current->prev->next = NULL;
            list->tail = list->current->prev;
        }
    }
    else
    {
        
        if (list->current->prev != NULL)list->current->prev->next = list->current->next;
        if (list->current->next != NULL)list->current->next->prev = list->current->prev;
    }
    free(list->current);
    list->current = list->current->next;
    return data;
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}