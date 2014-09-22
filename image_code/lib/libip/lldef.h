/* 
 * lldef.h
 * 
 * Practical Algorithms for Image Analysis
 * 
 * Copyright (c) 1997, 1998, 1999 MLMSoftwareGroup, LLC
 */

/*
 * LLDEF.H
 *
 * header file for doubly linked list manipulation functions in llist.c
 *
 * ref: 
 *   R. Sessions
 *   "Reusable Data Structures For C"
 *   Prentice Hall, Englewood Cliffs, NJ, 1989;
 */

#ifndef _LLDEF_H_
#define	_LLDEF_H_


typedef enum {
  False = 0, True = 1,
  InActive = 0, Active = 1,
  UnSet = 0, Set = 1,
  Fail = 0, Pass = 1,
  UnMatched = 0, Matched = 1,
  Accept = 0, Reject = 1,
  Forward = 0, Reverse = 1, UnKnown = -1
} Boolean;

/*
 * structure of each link (node) in a given list
 */
struct linktype {
  struct linktype *next;
  struct linktype *previous;
  char *item;                   /* ptr to struct itemtype will be */
  /* mapped onto this ptr to char!! */
};


/*
 * parameters characterizing active list
 * (several lists may be handled; see Sessions, sect 5.3)
 */
struct linklist {
  struct linktype *head;        /* pointers for active list */
  struct linktype *tail;
  struct linktype *clp;

  int listlength;
  int itemlength;

  int (*match) ();              /* func ptr to matching function */
};



/* function prototypes (in llist.c) */
static struct linktype *llcrlink (struct linklist *list);
extern void llsetmatch (int (*numatch) (), struct linklist *list);
extern void llsetsize (int size, struct linklist *list);
extern void moveitem (char *src_addr, char *dest_addr, int length);
extern void llzero (struct linklist *list);
extern void llinit (char *newitem, struct linklist *list);
extern void llhead (struct linklist *list);
extern void lltail (struct linklist *list);
extern Boolean llnext (struct linklist *list);
extern Boolean llprevious (struct linklist *list);
extern Boolean llsearch (char *desired_item, struct linklist *list);
extern void llretrieve (char *newitem, struct linklist *list);
extern void lladd (char *newitem, struct linklist *list);
extern void lladdhead (char *newitem, struct linklist *list);
extern void lladdprev (char *newitem, struct linklist *list);
extern void lldelete (struct linklist *list);
extern int ll_length (struct linklist *list);

#endif /* _LLDEF_H_ */
