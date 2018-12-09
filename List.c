#include "List.h"

static void* clist_pop      (CList *head,size_t index);
static int clist_push       (CList *head,void *elem,size_t index);
static void* clist_endpop   (CList *head);
static void* clist_begpop   (CList *head);
static void clist_erase     (CList *head);
static int clist_size       (CList *head);
static int clist_endpush    (CList *head,void *elem);
static int clist_begpush    (CList *head,void *elem);
static int clist_init       (CList **head,
                            int     (*begpush)  (CList *head,void *elem),
                            void*   (*begpop)   (CList *head),
                            int     (*endpush)  (CList *head,void *elem),
                            void*   (*endpop)   (CList *head),
                            int     (*push)     (CList *head,void *elem,size_t index),
                            void*   (*pop)      (CList *head,size_t index),
                            int     (*size)     (CList *head),
                            void    (*del)      (CList *head));


/* Function arguments:
 * - head  =>  input: Collection structure of methods and pointers to the first and last element.
 * - begpush  =>  input: Function, which insert the element at the beginning.
 * - begpop  =>  input: Function, which take the element from the beginning.
 * - endpush  =>  input: Function, which insert the element at the end.
 * - endpop  =>  input: Function, which take the element from the end.
 * - push  =>  input: Function, which insert the element at the index.
 * - pop  =>  input: Function, which take the element from the index.
 * - size  =>  input: Function, which return the size of the list.
 * - del  =>  input: Function, which delete the whole list.
 *
 * Function initializes the list.
 *
 * Return value:
 * - SUCCESS => 0
 * - ERROR => -1
 */

static int clist_init(CList **head,
                        int (*begpush) (CList *head,void *elem),
                        void* (*begpop) (CList *head),
                        int (*endpush) (CList *head,void *elem),
                        void* (*endpop) (CList *head),
                        int (*push) (CList *head,void *elem,size_t index),
                        void* (*pop) (CList *head,size_t index),
                        int (*size) (CList *head),
                        void (*erase) (CList *head)) {

        if( ((*head)=(CList*)malloc(sizeof(CList))) == NULL)
                return -1;
    else
    {
        (*head)->first=NULL;
        (*head)->last=NULL;
        (*head)->iSize=0;

        (*head)->begpop=begpop;
        (*head)->begpush=begpush;
        (*head)->erase=erase;
        (*head)->endpop=endpop;
        (*head)->endpush=endpush;
        (*head)->pop=pop;
        (*head)->push=push;
        (*head)->size=size;
    }

        return 0;

}

/* Function arguments:
 * -head => input: List structure.
 * -elem => input: Element to be inserted at the beginning.
 *
 * Function insert the element at the beginning.
 *
 * Return value:
 * - SUCCESS => 0
 * - ERROR => -1
 */

static int clist_begpush(CList *head, void *elem) {

        if(head->first==NULL)
        {
                if( (head->first=(LstElem*)malloc(sizeof(LstElem))) == NULL)
                        return -1;
        else
        {
            if( (head->first->value=(void*)malloc(sizeof(elem))) == NULL)
                return -1;
            else
            {
                head->first->value=elem;
                head->first->next=NULL;
                head->last=head->first;
                head->iSize++;
                return 0;
            }
        }
        }
    else
    {
        //Create new box for the next element
        LstElem *ptr;

        ptr=head->first;
        if( (head->first=(LstElem*)malloc(sizeof(LstElem))) == NULL)
            return -1;
        else
        {
            head->first->next=ptr;
            if( (head->first->value=(void*)malloc(sizeof(elem))) == NULL)
                return -1;
            else
            {
                head->first->value=elem;
                head->iSize=-1;
                return 0;
            }
        }
    }
}

/* Function arguments:
 * -head => input: List structure.
 * -elem => input: Element to be inserted at the end.
 *
 * Function insert the element at the end.
 *
 * Return value:
 * - SUCCESS => 0
 * - ERROR => -1
 */

static int clist_endpush(CList *head, void *elem) {

    if(head->first == NULL)
    {
                head->begpush(head,elem);
                return 0;
        }
    else
    {
        if( (head->last->next=(LstElem*)malloc(sizeof(LstElem))) == NULL)
            return -1;
        else
        {
            head->last=head->last->next;
            head->last->value=elem;
            head->last->next=NULL;
            head->iSize++;

            return 0;
        }
    }
}

/* Function arguments:
 * -head => input: List structure.
 *
 * Function return size of the list.
 *
 * Return value:
 * - SUCCESS => int <0,+inf)
 */

static int clist_size(CList *head) {

    return head->iSize;

}

/* Function arguments:
 * -head => input: List structure.
 *
 * Function delete the whole list.
 */

static void clist_erase(CList *head) {

        LstElem *ptr,*ptrnxt;
        ptr=head->first;

        while(ptr!=NULL)
        {
        ptrnxt=ptr->next;

                ptr->value=NULL;
                ptr->next=NULL;
                free(ptr);

        ptr=ptrnxt;
        }

        head->first=NULL;
        head->last=NULL;
        head->iSize=0;
}

/* Function arguments:
 * -head => input: List structure.
 *
 * Function remove the first element from the list and return it.
 *
 * Return value:
 * - SUCCESS => &void
 * - ERROR => NULL
 */

static void* clist_begpop(CList *head) {

        if(head->first==NULL)
                return NULL;
    else
    {
        void *ptr;
        ptr=head->first->value;

        if(head->first==head->last)
        {
            free(head->first);
            head->first=NULL;
            head->last=NULL;
        }
        else
        {
            LstElem *nextElem;
            nextElem=head->first->next;

            head->first->value=NULL;
            free(head->first);
            head->first=nextElem;
        }

        head->iSize--;
        return ptr;
    }

}

/* Function arguments:
 * -head => input: List structure.
 *
 * Function remove the last element from the list and return it.
 *
 * Return value:
 * - SUCCESS => &void
 * - ERROR => NULL
 */

static void* clist_endpop(CList *head) {

        if(head->last==NULL)
                return NULL;
    else
    {
        void *ptr;
        ptr=head->last->value;

        if(head->first==head->last)
        {
            free(head->last);
            head->first=NULL;
            head->last=NULL;
        }
        else
        {
            LstElem *iterator;
            iterator=head->first;

            while(iterator->next != head->last)
                iterator=iterator->next;

            head->last->value=NULL;
            free(head->last);

            head->last=iterator;
            head->last->next=NULL;
        }

        head->iSize--;
        return ptr;
    }
}

/* Function arguments:
 * -head => input: List structure.
 * -elem => input: Element to be inserted.
 * -index => input: Index of inserting element.
 *
 * Function insert the element at the index position.
 *
 * Return value:
 * - SUCCESS => 0
 * - ERROR => -1
 */

static int clist_push(CList *head, void *elem, size_t index) {

    LstElem *ptr, *prevPtr, *newPtr;

    ptr=head->first;
    prevPtr=NULL;

    for(size_t count=0; count<index; count++)
        {
                if(ptr==NULL)
                        return -1;
        else
        {
            prevPtr=ptr;
            ptr=ptr->next;
        }
        }

    newPtr=(LstElem*)malloc(sizeof(LstElem));

    newPtr->value=elem;
    newPtr->next=NULL;

    if(prevPtr==NULL) // Nothing has been changed with the previous pointer (ptr is at 0 index)
        {
        newPtr->next=head->first;
        head->first=newPtr;
        }
    else
    {
        newPtr->next=ptr;
        prevPtr->next=newPtr;
    }

    head->iSize++;
        return 0;

}

/* Function arguments:
 * -head => input: List structure.
 * -index => input: Index of searching element.
 *
 * Function return the element at the index position.
 *
 * Return value:
 * - SUCCESS => &void
 * - ERROR => NULL
 */

static void* clist_pop(CList *head, size_t index) {

    if(head->iSize==0)
        return NULL;
    else
    {
        LstElem *ptr, *prevPtr;
        void *value;

        ptr=head->first;
        prevPtr=NULL;

        for(size_t count=0; count<index; count++)
        {
            if(prevPtr==NULL)
                return NULL;
            else
            {
                prevPtr=ptr;
                ptr=ptr->next;
            }
        }

        value=ptr->value;

        if(head->first==ptr)
            head->first=head->first->next;
        else if(head->last==ptr)
            head->last=prevPtr;

        if(prevPtr!=NULL)
        prevPtr->next=ptr->next;

        ptr->value=NULL;
        ptr->next=NULL;
        free(ptr);

        head->iSize--;
        return value;
    }
}

/*
 * Function create the list.
 *
 * Return value:
 * - SUCCESS => &CList
 * - ERROR => NULL
 */

CList* clist_create(void) {

        CList *head;

    if(clist_init(&head,
                    clist_begpush,
                    clist_begpop,
                    clist_endpush,
                    clist_endpop,
                    clist_push,
                    clist_pop,
                    clist_size,
                    clist_erase)==0)
                return head;
        else
                return NULL;
}

/* Function arguments:
 * -head => input: List structure.
 *
 * Function delete the list.
 */

void clist_delete(CList *head)
{
    head->erase(head);
    free(head);
}
