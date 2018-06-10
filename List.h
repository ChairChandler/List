#ifndef LIST_H
#define LIST_H

/*
Operations:
1.Create								CList* clist_crt(void)
2.Add element in the beginning			int List_begpush(CList *head,void *elem)
3.Delete element from the beginning		void List_begpop(CList *head)
4.Add element at the end				int List_endpush(CList *head,void *elem)
5.Delete element from the end			void List_endpop(CList *head)
6.Add element in any position			int List_push(CList *head,void *elem,int index)
7.Delete element from any position		void List_pop(CList *head,int index)
8.Size of the list						int List_size(CList *head)
9.Delete the list						void List_del(CList *head)
10.Write integers elements				void List_print(CList *head)
*/

typedef struct LstElem_ {
	
	void *value;
	struct LstElem_ *next;
		
} LstElem;

typedef struct CList_ {
	
	struct LstElem_ *first;
	struct LstElem_ *last;
	int iSize;
	
	int 	(*begpush)	(struct CList_ *head,void *elem);
	void* 	(*begpop)	(struct CList_ *head);
	int 	(*endpush)	(struct CList_ *head,void *elem);
	void* 	(*endpop)	(struct CList_ *head);
	int 	(*push)		(struct CList_ *head,void *elem,int index);
	void* 	(*pop)		(struct CList_ *head,int index);
	int 	(*size)		(struct CList_ *head);
	void 	(*del)		(struct CList_ *head);
	void 	(*print)	(struct CList_ *head);
		
} CList;

CList* clist_crt(void);

void* clist_pop(CList *head,int index);

int clist_push(CList *head,void *elem,int index);

void* clist_endpop(CList *head);

void* clist_begpop(CList *head);

void clist_del(CList *head);

int clist_size(CList *head);

void clist_print(CList *head);

int clist_endpush(CList *head,void *elem);

int clist_begpush(CList *head,void *elem);

int clist_init(CList **head, int (*begpush) (CList *head,void *elem), void* (*begpop) (CList *head), int (*endpush) (CList *head,void *elem),
		void* (*endpop) (CList *head), int (*push) (CList *head,void *elem,int index), void* (*pop) (CList *head,int index),
		int (*size) (CList *head), void (*del) (CList *head), void (*print) (CList *head));

#endif
