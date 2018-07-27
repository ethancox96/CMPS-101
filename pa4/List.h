//Ethan Cox
//etecox
//pa2
//List.h
//Header file for the ListADT used in this project

#ifndef LIST_H_INCLUDE
#define LIST_H_INCLUDE

//Exported types
typedef struct ListObj* List;

//Constructors-Destructors-------------------------------------------------

//newList()
//Returns reference to new empty List object
List newList(void);

//freeList()
//Frees all heap memory associated with List *pL, and sets *pL to NULL
void freeList(List *pL);

//Access function----------------------------------------------------------

//int length(List L)
//returns the length of the list
int length(List L);

//int index(List L)
//returns the value of the item at the cursor if it is not NULL
int index(List L);

//int front(List L)
//returns the item at the front of the list
int front(List L);

//int back(List L)
//returns back element
int back(List L);

//int get(List L)
//returns cursor element
int get(List L);

//int equals(List A, List B)
//Returs true if List A and List B are the same integer sequence
int equals(List A, List B);

//Manipulation procedures---------------------------------------------------

//void clear(List L)
//Resets this List to its original empty state
void clear(List L);

//void moveFront(List L)
//move cursor to the front
void moveFront(List L);

//void moveBack(List L)
//move cursor to the back
void moveBack(List L);

//void movePrev(List L)
//if cursor is not at front move it one spot back in the list
void movePrev(List L);

//void moveNext(List L)
//if cursor is not at tail move it one spot forward in the list
void moveNext(List L);

//void prepend(List L, int data)
//insert new element before front element
void prepend(List L, int data);

//void append(List L, int data)
//insert new element before back element
void append(List L, int data);

//void insertBefore(int data)
//insert new element before cursor
void insertBefore(List L, int data);

//void insertAfter(List, Lint data)
//insert new element after cursor
void insertAfter(List L, int data);

//void deleteFront(List L)
//deletes the first element in the list
void deleteFront(List L);

//void deleteBack(List L)
//deletes the last element in the list
void deleteBack(List L);

//void delete(List L)
//deletes the cursor element making the cursor undefined
void delete(List L);

//Other Operations----------------------------------------------------------

//void printList(FILE* out, List L)
//prints the List to out sperating each element with a space
void printList(FILE* out, List L);

//List copyList(List L)
//Returns a new List representing the same integer sequence as L, cursor NULL
List copyList(List L);

#endif





