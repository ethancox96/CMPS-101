//Ethan Cox
//etecox
//pa2
//List.c
//Implements the ListADT

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
#include"List.h"

//Constructors-Destructors

//NodeObj
typedef struct NodeObj{
   int item;
   struct NodeObj* next;
   struct NodeObj* prev;
} NodeObj;

//Node
typedef NodeObj* Node;

//newNode()
//constructor for the Node type
Node newNode(int data){
   Node N = malloc(sizeof(NodeObj));
   assert(N!=NULL);
   N->item = data;
   N->next = NULL;
   N->prev = NULL;
   return(N);
}

//freeNode()
//destructor for the Node type
void freeNode(Node* pN){
   if (pN != NULL && *pN != NULL){
      free(*pN);
      *pN = NULL;
   }
}

//ListObj
typedef struct ListObj{
   Node head;
   Node tail;
   Node cursor;
   int index;
   int numItems;
} ListObj;

//newList()
//constructor for the List type
List newList(void){
   List L = malloc(sizeof(ListObj));
   assert(L!=NULL);
   L->head = NULL;
   L->tail = NULL;
   L->cursor = NULL;
   L->index = -1;
   L->numItems = 0;
   return(L);
}

//freeList()
//destructor for the List type
void freeList(List *pL){
   if (pL != NULL && *pL != NULL){
      free(*pL);
      *pL = NULL;
   }
}

//Access functions

//int length(List L)
//returns the length of the list
int length(List L){
   return L->numItems;
}

//int index(List L)
//returns the value of the item at the cursor if it is not NULL
int index(List L){
   return L->index;
}

//int front(List L)
//returns the item at the front of the list
int front(List L){
   if (length(L) > 0)
      return L->head->item;
   else
      return -1;
}

//int back(List L)
//returns back element
int back(List L){
   if (length(L) > 0)
      return L->tail->item;
   else
      return -1;
}

//int get(List L)
//returns cursor element
int get(List L){
   if (L->cursor == NULL){
      printf("\nNull Pointer\n");
   }
   if (length(L) > 0 && index(L) >= 0)
      return L->cursor->item;
   else
      return -1;
}

//int equals(List A, List B)
//Returs true if List A and List B are the same integer sequence
int equals(List A, List B){
   if (A->numItems != B->numItems)
      return 0;
   else{
      moveFront(A);
      moveFront(B);
      while(index(A) >= 0){
         int x = get(A);
	 int y = get(B);
	 if (x != y)
	    return 0;   
	 moveNext(A);
	 moveNext(B);      
      }
   }
   return 1;
}

//Manipulation procedures

//void clear()
//resets the List to its original state
void clear(List L){
   L->head = NULL;
   L->tail = NULL;
   L->cursor = NULL;
   L->index = -1;
   L->numItems = 0;
}

//void moveFront(List L)
//move cursor to the front
void moveFront(List L){
   if (length(L) > 0){
      L->cursor = L->head;
      L->index = 0;
   }
}

//void moveBack(List L)
//move cursor to the back
void moveBack(List L){
   if (length(L) > 0){
      L->cursor = L->tail;
      L->index = L->numItems;
   }
}

//void movePrev(List L)
//if cursor is not at front move it one spot back in the list
void movePrev(List L){
   if(L->cursor != NULL && L->cursor != L->head){
      L->cursor = L->cursor->prev;
      L->index--;
   }
   else if(L->cursor == L->head){
      L->index = -1;
      L->cursor = NULL;
   }
}

//void moveNext(List L)
//if cursor is not at tail move it one spot forward in the list
void moveNext(List L){
   if (L->cursor != NULL && L->cursor != L->tail){
      L->cursor = L->cursor->next;
      L->index++;
   }
   else if(L->cursor == L->tail){
      L->index = -1;
      L->cursor = NULL;
   }
}

//void prepend(List L, int data)
//insert new element before front element
void prepend(List L, int data){
   Node oldHead = L->head;
   L->head = newNode(data);

   if (oldHead != NULL){
      oldHead->prev = L->head;
      L->head->next = oldHead;
   }

   if (L->numItems == 0){
      L->tail = L->head;
      L->index++;
   }
   L->numItems++;
}

//void append(List L, int data)
//insert new element before back element
void append(List L, int data){
   Node oldTail = L->tail;
   L->tail = newNode(data);

   if (oldTail != NULL){
      oldTail->next = L->tail;
      L->tail->prev = oldTail;
   }

   if (L->numItems == 0){
      L->head = L->tail;
      L->index++;
   }
   L->numItems++;
}

//void insertBefore(int data)
//insert new element before cursor
void insertBefore(List L, int data){
   if (length(L) > 0 && L->index >= 0){
      Node N = L->cursor;
      if (N == L->head)
	 prepend(L, data);
      else{
	 Node P = newNode(data);
	 P->next = N;
	 P->prev = N->prev;
	 N->prev->next = P;
	 N->prev = P;
      }
   }
   L->numItems++;
}

//void insertAfter(List, Lint data)
//insert new element after cursor
void insertAfter(List L, int data){
   if (length(L) > 0 && L->index >= 0){
      Node N = L->cursor;
      if (N == L->tail)
	 append(L, data);
      else{
	 Node P = newNode(data);
	 P->prev = N;
	 P->next = N->next;
	 N->next->prev = P;
	 N->next = P;
      }
   }
   L->numItems++;
}

//void deleteFront(List L)
//deletes the first element in the list
void deleteFront(List L){
   if (length(L) > 0){
      L->head = L->head->next;
      L->head->prev = NULL;
   }
   L->numItems--;
}

//void deleteBack(List L)
//deletes the last element in the list
void deleteBack(List L){
   if (length(L) > 0){
      L->tail = L->tail->prev;
      L->tail->next = NULL;
   }
   L->numItems--;
}

//void delete(List L)
//deletes the cursor element making the cursor undefined
void delete(List L){
   Node N = L->cursor;
   N->next->prev = N->prev;
   N->prev->next = N->next;
   N = NULL;
   L->cursor = NULL;
   L->numItems--;
}

//Other methods

void printList(FILE* out, List L){
   if (L == NULL){
      fprintf(stderr, "List Error: calling printList() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   moveFront(L);
   while(index(L) >= 0){
      int i = L->cursor->item;
      char str[30];
      sprintf(str, "%d", i);
      fprintf(out, "%s ", str);
      moveNext(L);
   }
}

List copyList(List L){
   List R = newList();
   moveFront(L);
   while(index(L)>=0){
      append(R, L->cursor->item);
      moveNext(L);
   }
   return R;
}








