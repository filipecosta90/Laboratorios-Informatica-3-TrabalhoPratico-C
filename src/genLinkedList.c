/*
 *  * Copyright (C) Carlos Sá, Filipe Oliveira, Sérgio Caldas
 *  * Copyright (C) Laboratórios Informática III, Universidade do Minho, 2015
 *  */

#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>

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

struct list* orderedInsertLLWithLimit ( struct list *list , void * element , int ( *comparatorFunc ) ( void* , void* ) , int limit) {
  struct listNode *current, *previous;
  int bigger = 0;
  struct listNode *node = malloc ( sizeof ( struct listNode ) );
  node->next = NULL;
  node->data = element;
  if( list->logicalLength == 0 ) {
    list->head = list->tail = node;
  } else {
    current = list->head;
    previous = NULL;
    while( current->next != NULL && bigger == 0 ) {
      if ( comparatorFunc ( element , current->data ) > 0 ){
        bigger = 1;
      }
      else {
        previous = current;
        current = current->next;
      }
    }
    if (previous == NULL) {
      node->next = list->head;
      list->head = node;
    }
    else if ( current->next == NULL ){
      current->next = node;
    }
    else if ( bigger == 1 ){
      previous->next = node;
      node->next=current;
    }
  }
  list->logicalLength++;
  list = limitLL ( list , limit );
  return list;
}

struct list* orderedInsertLL ( struct list *list , void * element , int ( *comparatorFunc ) ( void* , void* ) ) {
  struct listNode *current, *previous;
  int bigger = 0;
  struct listNode *node = malloc ( sizeof ( struct listNode ) );
  node->next = NULL;
  node->data = element;
  if( list->logicalLength == 0 ) {
    list->head = list->tail = node;
  } else {
    current = list->head;
    previous = NULL;
    while( current->next != NULL && bigger == 0 ) {
      if ( comparatorFunc ( element , current->data ) > 0 ){
        bigger = 1;
      }
      else {
        previous = current;
        current = current->next;
      }
    }
    if (previous == NULL) {
      node->next = list->head;
      list->head = node;
    }
    else if ( current->next == NULL ){
      current->next = node;
    }
    else if ( bigger == 1 ){
      previous->next = node;
      node->next=current;
    }
  }
  list->logicalLength++;
  return list;
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
  if ( list->logicalLength <= number ) {
    return list;
  }
  while( current != NULL && i < number  ) {
    previous = current;
    current = current->next; 
    i++;
  }
  previous->next = NULL;
  list->logicalLength = i;
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
    current = current->next;
  }
  return returningList;
}

