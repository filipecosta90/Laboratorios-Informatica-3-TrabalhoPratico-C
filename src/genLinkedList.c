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
  node->data = element;
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
  node->next = NULL;
  node->data = element;
  if( list->logicalLength == 0 ) {
    list->head = list->tail = node;
  } else {
    list->tail->next = node;
    list->tail = node;
  }
  list->logicalLength++;
}

void orderedInsertLL ( struct list *list , void * element , int ( *comparatorFunc ) ( void* , void* ) ) {
  struct listNode *node;
  struct listNode *temp; 
  struct listNode *previous;

  node = malloc ( sizeof ( struct listNode ) );
  node->next = NULL;
  node->data = element;
  if( list->logicalLength == 0 ) {
    list->head = list->tail = node;
  } else {
    previous = list->head;
    temp = list->head;

    while ( temp->next != NULL && comparatorFunc ( node->data , temp->data ) < 0 ){
      previous = temp;
      temp = temp->next;
    }
    node->next = temp;
    previous->next = node;
  }
}

void*  headLL ( struct list *list ){
  struct listNode *node; 
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

struct list* limitLL ( struct list* list , int number ){
  struct listNode *current, *previous;
  int i = 0;
  current = list->head;
  while( current != NULL && i < number  ) {
    previous = current;
    current = current->next; 
    i++;
    list->logicalLength--;
  }
  if ( i == number ){
    list->logicalLength = number;
    previous->next = NULL;
  }
  return list;
}

void myFreeChar1 ( void* myfree ){
  char* stringF;
  stringF = NULL;
  assert ( myfree != NULL );
  stringF = ( char* ) myfree;
  free ( stringF );
}

struct list* convertLLtoStringer ( struct list* list  , char* ( toStringer ) ( void* ) ){
  struct list* returningList;
  struct listNode *current;
  returningList = initLL ( ) ;
  newLL ( returningList , sizeof ( char* ) , &myFreeChar1 );
  current = list->head;
  while( current != NULL  ) {
    appendLL( returningList , toStringer ( current->data) );
  }
  return returningList;
}
