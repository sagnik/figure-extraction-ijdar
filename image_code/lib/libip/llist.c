/* 
 * llist.c
 * 
 * Practical Algorithms for Image Analysis
 * 
 * Copyright (c) 1997, 1998, 1999 MLMSoftwareGroup, LLC
 */

/*
 * LLIST
 *
 * manipulations of doubly linked lists:
 *   several lists may be active 
 *
 * ref: 
 *   R. Sessions
 *   "Reusable Data Structures For C", sects. 3.4, 5.6, 7.1;
 *   Prentice Hall, Englewood Cliffs, NJ, 1989;
 *
 * note:
 *   pointers to struct itemtype, passed in the argument list to
 *   several list manipulation functions in this module (see e.g. 
 *   lladd()), are mapped onto pointers to char!! (see Sessions, p.38); 
 *   this procedure was found to be robust when compiling with the small 
 *   model of MSC-5.1 which employs near (or 2byte) pointers, but found 
 *   to lead to ill-defined conditions when compiling with the large 
 *   model which employs far (or (2+2)byte) pointers; in the latter case, 
 *   a pertinent compiler warning message is given concerning the 
 *   malloc() calls in llcrlink():
 *   ->C4017: cast of int expression to far pointer!! 
 *   for the small memory model, malloc() maps to _fmalloc(), 
 *   in the small model to _nmalloc();
 *   -->a magic quickfix was found:
 *      when gmod() is employed, this problem is not observed!!
 *
 *   to specify the currently active list, the calling routine may
 *   employ a special function llsetlist() in which case a static
 *   variable static struct linklist *list is required; to activate
 *   this option, set SETLIST;
 *   alternatively, the active list may be explicitly specified
 *   in the argument list to the list manipulation functions 
 *   (see Sessions, pp.47 - 49); this option is used here and
 *   requires that SETLIST be undefined
 *
 *   a similar choice of procedure applies to the specification
 *   of the appropriate matching function (see Sessions, sect 5.4);
 *   here, it is specified via the function llsetmatch(); if this
 *   method is to be used, struct linklist (in lldef.h) must contain 
 *   a field specifying this function: int (*match) (); this method 
 *   is recommended when it may be assumed that at any given time a 
 *   linked list only has one associated matching function;
 *   alternatively, the pertinent matching function may be designated
 *   in the argument list to the function llsearch()
 *
 */
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include "lldef.h"


#undef	SETLIST                  /* set this switch to activate llsetlist() */
#undef	LLDEBUG


/*
 * specify active list
 */
#ifdef SETLIST
void
llsetlist (newlist)
     struct linklist *newlist;
{

  list = newlist;
}

#endif

/*
 * specify matching function pertinent to current application
 */
void
llsetmatch (numatch, list)
     int (*numatch) ();
     struct linklist *list;
{
  list->match = numatch;
}


/*
 * determine size of data item to manipulated
 */
void
llsetsize (size, list)
     int size;
     struct linklist *list;
{
  list->itemlength = size;
}


/*
 * memory to memory transfer (MSC 5.1)
 */
void
moveitem (src_addr, dest_addr, length)
     char *src_addr, *dest_addr;
     int length;
{
  char *retval;

  retval = memmove (dest_addr, src_addr, length);

}



/*
 * memory allocation for a new link (see Sessions, pp.39-41, p.49)
 */
struct linktype *
llcrlink (list)
     struct linklist *list;
{
  struct linktype *link;

  link = (struct linktype *) malloc (sizeof (struct linktype));
/*      link->item = (char near *)_nmalloc(list->itemlength); */
  link->item = (char *) malloc (list->itemlength);

#ifdef LLDEBUG
  printf ("...LLCRLINK:(char *)link->item = %p\n", link->item);
#endif

  return (link);
}


/*
 * initialize empty list
 */
void
llzero (list)
     struct linklist *list;
{
  list->head = list->tail = list->clp = NULL;
  list->listlength = 0;
}


/*
 * initialize linked list with an item
 */
void
llinit (newitem, list)
     char *newitem;
     struct linklist *list;
{

  /* there is only one link (node) in list */
  list->head = list->tail = list->clp = llcrlink (list);
  if (list->clp == NULL) {
    printf ("\n...LLINIT: memory allocation failed\n");
    return;
  }
#ifdef LLDEBUG
  printf ("...LLINIT:  (char *)newitem = %p\n", newitem);
  printf ("	(linktype *)newlink = %p\n", list->clp);
#endif


  list->clp->next = list->clp->previous = NULL;  /* no other links */

  moveitem (newitem, list->clp->item, list->itemlength);  /* mv item */
/*      memmove(list->clp->item, newitem, list->itemlength); */

  list->listlength = 1;         /* init. listlength */
}


/*
 * set the current link ptr (clp) to point to the top (head) of the list
 */
void
llhead (list)
     struct linklist *list;
{

  list->clp = list->head;
}


/*
 * set the current link ptr (clp) to point to the end (tail) of the list
 */
void
lltail (list)
     struct linklist *list;
{

  list->clp = list->tail;
}


/*
 * set the current link ptr to the next link, returning False if 
 * clp is pointing to the tail (end of list), True otherwise
 */
Boolean
llnext (list)
     struct linklist *list;
{

  if (list->clp->next == NULL)
    return (False);
  else {
    list->clp = list->clp->next;
    return (True);
  }
}


/*
 * set the current link ptr to the previous link, returning False if 
 * clp is pointing to the tail
 */
Boolean
llprevious (list)
     struct linklist *list;
{

  if (list->clp->previous == NULL)
    return (False);
  else {
    list->clp = list->clp->previous;
    return (True);
  }
}



/*
 * retrieve the item pointed to by the current link ptr and place it 
 * into a memory location specified as an argument
 */
void
llretrieve (newitem, list)
     char *newitem;
     struct linklist *list;
{

  moveitem (list->clp->item, newitem, list->itemlength);
}


/*
 * search list for a given item, returning True if found, False otherwise
 * (see Sessions, sect. 3.5, p.30  ca_check(), 
 *             sect. 5.4, pp.53/54  llcheck() )
 */
Boolean
llsearch (desired_item, list)
     char *desired_item;
     struct linklist *list;
{
  Boolean retval = False;
  Boolean MatchStatus = False;


  llhead (list);
  do {
    if ((*list->match) (list->clp->item, desired_item)) {
      printf ("\n...found item in llist\n");
      MatchStatus = True;
    }
  } while ((MatchStatus != True) && ((retval = llnext (list)) == True));


  return (MatchStatus);
}




/*
 * add (insert) a new link containing a newitem immediately
 * following the link pointed to by the current link ptr
 */
void
lladd (newitem, list)
     char *newitem;
     struct linklist *list;
{
  struct linktype *newlink;
  int retval;


/* if empty, initialize list */
  if ((retval = ll_length (list)) == 0) {
    llinit (newitem, list);
    return;
  }

/* create new link */
  if ((newlink = llcrlink (list)) == NULL) {
    printf ("\n...LLADD: memory allocation failed\n");
    return;
  }
#ifdef LLDEBUG
  printf ("...LLADD:   (char *)newitem = %p\n", newitem);
  printf ("	size of ptr to char = %d\n", sizeof (char *));
  printf ("	(linktype *)newlink = %p\n", newlink);
#endif


  moveitem (newitem, newlink->item, list->itemlength);
  list->listlength++;


/* reset list pointers */
  newlink->next = list->clp->next;
  newlink->previous = list->clp;

  if (list->tail == list->clp)  /* handle appending new tail */
    list->tail = newlink;
  else
    list->clp->next->previous = newlink;

  list->clp->next = newlink;
  list->clp = newlink;
}


/*
 * add (insert) a new link containing a newitem immediately
 * preceding (!) the head of the list
 */
void
lladdhead (newitem, list)
     char *newitem;
     struct linklist *list;
{
  struct linktype *newlink;
  int retval;

/* if empty, initialize list */
  if ((retval = ll_length (list)) == 0) {
    llinit (newitem, list);
    return;
  }

/* create new link */
  if ((newlink = llcrlink (list)) == NULL) {
    printf ("\n...LLADDHEAD: memory allocation failed\n");
    return;
  }

  moveitem (newitem, newlink->item, list->itemlength);
  list->listlength++;

/* reset list pointers */
  newlink->next = list->head;
  newlink->previous = NULL;
  list->head->previous = newlink;
  list->clp = list->head = newlink;
}


/*
 * add (insert) a new link containing a newitem immediately
 * preceding(!) the link pointed to by the current link ptr
 * (this is generalization of routine lladdhead() represents
 * the analog of routine lladd() )
 */
void
lladdprev (newitem, list)
     char *newitem;
     struct linklist *list;
{
  struct linktype *newlink;
  int retval;

/* if empty, initialize list */
  if ((retval = ll_length (list)) == 0) {
    llinit (newitem, list);
    return;
  }

/* create new link */
  if ((newlink = llcrlink (list)) == NULL) {
    printf ("\n...LLADDPREV: memory allocation failed\n");
    return;
  }

  moveitem (newitem, newlink->item, list->itemlength);
  list->listlength++;

/* reset list pointers */
  newlink->previous = list->clp->previous;
  newlink->next = list->clp;

  if (list->head == list->clp)  /* handle insertion of new head */
    list->head = newlink;
  else
    list->clp->previous->next = newlink;

  list->clp->previous = newlink;
  list->clp = newlink;
}


/* 
 * delete the link pointed to by the current link ptr (clp)
 */
void
lldelete (list)
     struct linklist *list;
{
  struct linktype *before, *after;

  /* only one link in list */
  if ((list->head == list->clp) && (list->tail == list->clp))
    list->head = list->tail = NULL;

  else if (list->head == list->clp) {  /* del head of list */
    list->head = list->head->next;
    list->head->previous = NULL;
  }
  else if (list->tail == list->clp) {  /* del tail of list */
    list->tail = list->tail->previous;
    list->tail->next = NULL;
  }
  else {                        /* del interior link */
    before = list->clp->previous;
    after = list->clp->next;
    before->next = after;
    after->previous = before;
  }

  free (list->clp->item);       /* free mem */
  free (list->clp);

  list->clp = list->head;       /* del current link */
  list->listlength--;

}


/*
 * return listlength
 */
int
ll_length (list)
     struct linklist *list;
{
  return (list->listlength);
}
