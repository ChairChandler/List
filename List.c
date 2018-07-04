#include <stdio.h>
#include <stdlib.h>
#include "List.h"

static void* clist_pop(CList *head,int index);
static int clist_push(CList *head,void *elem,int index);
static void* clist_endpop(CList *head);
static void* clist_begpop(CList *head);
static void clist_del(CList *head);
static int clist_size(CList *head);
static void clist_print(CList *head);
static int clist_endpush(CList *head,void *elem);
static int clist_begpush(CList *head,void *elem);
static int clist_init(CList **head, int (*begpush) (CList *head,void *elem), void* (*begpop) (CList *head), int (*endpush) (CList *head,void *elem),
		void* (*endpop) (CList *head), int (*push) (CList *head,void *elem,int index), void* (*pop) (CList *head,int index),
		int (*size) (CList *head), void (*del) (CList *head), void (*print) (CList *head));



static int clist_init(CList **head, int (*begpush) (CList *head,void *elem), void* (*begpop) (CList *head), int (*endpush) (CList *head,void *elem),
		void* (*endpop) (CList *head), int (*push) (CList *head,void *elem,int index), void* (*pop) (CList *head,int index),
		int (*size) (CList *head), void (*del) (CList *head), void (*print) (CList *head)) {
			
	if( ((*head)=(CList*)malloc(sizeof(CList))) == NULL)
		return -1;			

	(*head)->first=NULL;
	(*head)->last=NULL;
	(*head)->iSize=0;

	(*head)->begpop=begpop;
	(*head)->begpush=begpush;
	(*head)->del=del;
	(*head)->endpop=endpop;
	(*head)->endpush=endpush;
	(*head)->pop=pop;
	(*head)->print=print;
	(*head)->push=push;
	(*head)->size=size;
	
	return 0;	

}

static int clist_begpush(CList *head,void *elem) {
	
	if(head->first==NULL)
	{
		if( (head->first=(LstElem*)malloc(sizeof(LstElem))) == NULL)
			return -1;
			
		if( (head->first->value=(void*)malloc(sizeof(elem))) == NULL)
			return -1;
		
		head->first->value=elem;
		head->first->next=NULL;
		head->last=head->first;
		head->iSize=-1;
		return 0;
	}
	
	LstElem *ptr;
	
	ptr=head->first;
	if( (head->first=(LstElem*)malloc(sizeof(LstElem))) == NULL)
		return -1;
		
	head->first->next=ptr;
	if( (head->first->value=(void*)malloc(sizeof(elem))) == NULL)
		return -1;
		
	head->first->value=elem;
	head->iSize=-1;
	
	return 0;

}

static int clist_endpush(CList *head,void *elem) {
	
	if( head->first == NULL) {
		
		head->begpush(head,elem);
		return 0;
		
	}
	
	if( (head->last->next=(LstElem*)malloc(sizeof(LstElem))) == NULL)
		return -1;
	
	head->last=head->last->next;
	head->last->value=elem;
	head->last->next=NULL;
	
	return 0;
	
}

static void clist_print(CList *head) {
	
	LstElem *ptr;
	ptr=head->first;
	while(ptr!=NULL)
	{
	printf("%d ",ptr->value);
	ptr=ptr->next;
	}

	return;
}

static int clist_size(CList *head) {
	
	if(head->iSize!=(-1))
		return head->iSize;
	
	int count;
	LstElem *ptr;
	
	count=0;
	ptr=head->first;
	while(ptr!=NULL)
	{
		count++;
		ptr=ptr->next;
	}
	
	head->iSize=count;
	return count;
}

static void clist_del(CList *head) {
	
	LstElem *ptr,*ptrnxt;
	ptr=head->first;
	
	while(ptr!=NULL)
	{
		ptr->value=NULL;
		ptrnxt=ptr->next;
		ptr->next=NULL;
		free(ptr);
		ptr=ptrnxt;
	}
	
	head->first=NULL;
	head->last=NULL;
	head->iSize=0;
	return;
}

static void* clist_begpop(CList *head) {
	
	if(head->first==NULL)
		return NULL;
	
	if(head->first==head->last)
	head->last=NULL;
	
	void *ptr=head->first->value;
	head->first->value=NULL;
	void *nxt=head->first->next;
	free(head->first);
	head->first=nxt;
	
	head->iSize=-1;
	return ptr;
	
}

static void* clist_endpop(CList *head) {
	
	if(head->last==NULL)
		return NULL;
		
	void *ptr=head->last->value;
	
	if(head->first==head->last)
	{
		head->first=NULL;
		head->last=NULL;
		return ptr;
	}
	
	LstElem *mv;
	mv=head->first;
	while(mv->next!=NULL&&mv->next->next!=NULL)
	mv=mv->next;
	
	head->last->value=NULL;
	free(head->last);
	
	if(mv!=NULL&&mv!=head->last)
	{
	head->last=mv;
	head->last->next=NULL;
	}
	
	
	head->iSize=-1;
	return ptr;
	
}

static int clist_push(CList *head,void *elem,int index) {
	
	int count;
	LstElem *ptr,*hlptr,*nptr;
	ptr=head->first;
	hlptr=NULL;
	
	for(count=1;count<=index;count++)
	{
		if(ptr==NULL)
			return -1;
		
		hlptr=ptr;
		ptr=ptr->next;
	}
	
	nptr=(LstElem*)malloc(sizeof(LstElem));
	nptr->value=elem;
	
	if(hlptr!=NULL)
	{
	nptr->next=hlptr->next;
	hlptr->next=nptr;
	}
	else
	{
		nptr->next=head->first;
		head->first=nptr;
	}
	
	if(nptr->next==NULL)
	head->last=nptr;
	
	return 0;
	
}

static void* clist_pop(CList *head,int index) {
	
	int count;
	LstElem *ptr,*hlptr;
	ptr=head->first;
	hlptr=NULL;
	
	for(count=1;count<=index;count++)
	{
		if(ptr==NULL)
			return -1;
			
		hlptr=ptr;
		ptr=ptr->next;
	}
	
	if(head->first==ptr)
	head->first=head->first->next;
	
	if(head->last==ptr)
	head->last=hlptr;
	
	void *rval=ptr->value;
	if(hlptr!=NULL)
	hlptr->next=ptr->next;
	ptr->value=NULL;
	ptr->next=NULL;
	free(ptr);
	
	return rval;
	
}

CList* clist_crt(void) {
	
	CList *head;
	if(clist_init(&head,clist_begpush,clist_begpop,clist_endpush,clist_endpop,clist_push,clist_pop,clist_size,clist_del,clist_print)==0)
		return head;
	else
		return NULL;
	
}
