#ifndef LIST_H
#define LIST_H
#include <stdlib.h>

/*
 * You need to first create list, then you can do the following operations:
 *
 * 1.Create
 * 2.Add element at the beginning
 * 3.Delete element from the beginning
 * 4.Add element at the end
 * 5.Delete element from the end
 * 6.Add element in any position
 * 7.Delete element from any position
 * 8.Size of the list
 * 9.Erase the list
 * 10.Delete the list
 */

typedef struct LstElem_ {
	
    void *value;
    struct LstElem_ *next;
		
} LstElem;

typedef struct CList_ {
	
    struct LstElem_ *first;
    struct LstElem_ *last;
    int iSize;
	
    int     (*begpush)	(struct CList_ *head, void *elem);
    void*   (*begpop)	(struct CList_ *head);
    int     (*endpush)	(struct CList_ *head, void *elem);
    void*   (*endpop)	(struct CList_ *head);
    int     (*push)     (struct CList_ *head, void *elem, size_t index);
    void*   (*pop)      (struct CList_ *head, size_t index);
    int     (*size)     (struct CList_ *head);
    void    (*erase)    (struct CList_ *head);
		
} CList;

CList* clist_create(void);
void clist_delete(CList*);

#endif
