/*
 *  * Copyright (C) Carlos Sá, Filipe Oliveira, Sérgio Caldas
 *  * Copyright (C) Laboratórios Informática III, Universidade do Minho, 2015
 *  */

#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "genLinkedList.h"

struct listNode {
  void* data;
  struct listNode* next;
};

struct list {
  int logicalLength;
  int elementSize;
  struct listNode* head;
  struct listNode* tail;
  freeFunction freeFn;
};

struct list* initLL (){
  struct list* newLL;
  newLL = ( struct list* ) malloc ( sizeof ( struct list ) );
  return newLL;
}

void newLL ( struct list* list , int elementSize , void ( *freeFunc ) ( void* ) ){
  assert(list != NULL);
  assert( elementSize > 0 );
  list->logicalLength = 0;
  list->elementSize = elementSize;
  list->head = NULL;
  list->tail = NULL;
  list->freeFn = freeFunc;
}

void destroyLL ( struct list* list ){
  struct listNode *current;
  while( list->head != NULL ) {
    current = list->head;
    list->head = current->next;
    if( list->freeFn ) {
      list->freeFn( current->data );
    }
    free( current->data );
    free( current );
  }
}

void prependLL ( struct list *list , void *element ){
  struct listNode* node = malloc( sizeof ( struct listNode ) );
  node->data = malloc ( list->elementSize );
  memcpy( node->data , element , list->elementSize );
  node->next = list->head;
  list->head = node;
  /* First Node */
  if( !list->tail ) {
    list->tail = list->head;
  }
  list->logicalLength++;
}

void appendLL ( struct list *list , void *element ){
  struct listNode *node = malloc ( sizeof ( struct listNode ) );
  node->data = malloc( list->elementSize );
  node->next = NULL;
  memcpy( node->data , element , list->elementSize );
  if( list->logicalLength == 0 ) {
    list->head = list->tail = node;
  } else {
    list->tail->next = node;
    list->tail = node;
  }
  list->logicalLength++;
}

void*  headLL ( struct list *list ){
  struct listNode *node = malloc ( sizeof ( struct listNode ) );
  node->data = malloc( list->elementSize );
  node->next = NULL;
  node = list->head;
  assert( list->head != NULL );
  list->head = node->next;
  list->logicalLength--;
  return node->data;
}

void tailLL ( struct list *list, void *element ){
  struct listNode *node;
  node = list->tail;
  assert( list->tail != NULL );
  memcpy( element , node->data , list->elementSize );
}

int sizeLL ( struct list *list ){
  return list->logicalLength;
}

