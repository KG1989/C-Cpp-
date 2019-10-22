#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "circularList.h"

// Double link
struct Link
{
	TYPE value;
	struct Link * next;
	struct Link * prev;
};

struct CircularList
{
	int size;
	struct Link* sentinel;
};

/**
 * Allocates the list's sentinel and sets the size to 0.
 * The sentinel's next and prev should point to the sentinel itself.
 */
static void init(struct CircularList* list)
{
	// FIXME: you must write this
    list->sentinel = (struct Link*) malloc(sizeof(struct Link));
    assert(list->sentinel != 0);

    list->sentinel->next = list->sentinel;
    list->sentinel->prev = list->sentinel;

    list->size = 0;
}

/**
 * Creates a link with the given value and NULL next and prev pointers.
 */
static struct Link* createLink(TYPE value)
{
	// FIXME: you must write this
    struct Link *newLink = (struct Link*) malloc(sizeof(struct Link));

    newLink->value = value;
    newLink->next = NULL;
    newLink->prev = NULL;
	return newLink;
}

/**
 * Adds a new link with the given value after the given link and
 * increments the list's size.
 */
static void addLinkAfter(struct CircularList* list, struct Link* link, TYPE value)
{
	// FIXME: you must write this
    struct Link *newLink = (struct Link *) malloc(sizeof(struct Link));
    newLink->value = value; //set value

    //update newLink's pointers
    newLink->next = link->next;
    newLink->prev = link;

    //update the old links pointers
    link->next->prev = newLink;
    link->next = newLink;

    //dont update link->prev
    list->size++;
}

/**
 * Removes the given link from the list and
 * decrements the list's size.
 */
static void removeLink(struct CircularList* list, struct Link* link)
{
	// FIXME: you must write this
    assert(list->size > 0);

    //re-order pointers so the previous and next links are pointing to each other now
    link->next->prev = link->prev;
    link->prev->next = link->next;

    free(link);

    list->size--;
}

/**
 * Allocates and initializes a list.
 */
struct CircularList* circularListCreate()
{
	struct CircularList* list = malloc(sizeof(struct CircularList));
	init(list);
	return list;
}

/**
 * Deallocates every link in the list and frees the list pointer.
 */
void circularListDestroy(struct CircularList* list)
{
	// FIXME: you must write this
    //similar to destroy list in the linked list deque application
    while (!circularListIsEmpty(list))
	{
		circularListRemoveFront(list);
	}

	free(list->sentinel);
	free(list);
}

/**
 * Adds a new link with the given value to the front of the deque.
 */
void circularListAddFront(struct CircularList* list, TYPE value)
{
	// FIXME: you must write this
    addLinkAfter(list, list->sentinel, value);
    //from addLinkAfter
    //newLink->next = link->next and in this case link is list->sentinel
    //now plugin and replace and we have:
    //newLink->next = list->sentinel->next  -- newLink->next now points to what the link before's next was pointing to.
}

/**
 * Adds a new link with the given value to the back of the deque.
 */
void circularListAddBack(struct CircularList* list, TYPE value)
{
	// FIXME: you must write this
    addLinkAfter(list, list->sentinel->prev, value);
}

/**
 * Returns the value of the link at the front of the deque.
 */
TYPE circularListFront(struct CircularList* list)
{
	// FIXME: you must write this
    assert(!circularListIsEmpty(list));
    //grabs the next value after the sentinel which is seen as our front
	return list->sentinel->next->value;
}

/**
 * Returns the value of the link at the back of the deque.
 */
TYPE circularListBack(struct CircularList* list)
{
	// FIXME: you must write this
    assert(!circularListIsEmpty(list));
    //grabs the previous value to the left, or prev, or the sentinel which is seen as our back
	return list->sentinel->prev->value;
}

/**
 * Removes the link at the front of the deque.
 */
void circularListRemoveFront(struct CircularList* list)
{
	// FIXME: you must write this
    assert(!circularListIsEmpty(list));
    //grabs the value right after the sentinel which is seen as our front, assigns it to the next value, then removes front
    removeLink(list, list->sentinel->next);
}

/**
 * Removes the link at the back of the deque.
 */
void circularListRemoveBack(struct CircularList* list)
{
	// FIXME: you must write this
    assert(!circularListIsEmpty(list)); //I think this is the same as assert(list->size > 0)
    removeLink(list, list->sentinel->prev); //same logic as remove front except point to the one before the sentinel
}

/**
 * Returns 1 if the deque is empty and 0 otherwise.
 */
int circularListIsEmpty(struct CircularList* list)
{
	// FIXME: you must write this
    //if sentinel->next points to itself then the list is empty
    if (list->sentinel->next == list->sentinel)
    {
        return 1;
    }
    else
    {
        return 0;
    }

}

/**
 * Prints the values of the links in the deque from front to back.
 */
void circularListPrint(struct CircularList* list)
{
	// FIXME: you must write this
    assert(!circularListIsEmpty(list));
    struct Link *temp;
    //assign a temp to the link after sentinel (first link)
    temp = list->sentinel->next;
    //while temp hasn't gone around in a full circle yet
    while(temp != list->sentinel)
    {
        printf("Value: %f\n", temp->value);
        //increment temp
        temp = temp->next;
    }
}

/**
 * Reverses the deque.
 */
void circularListReverse(struct CircularList* list)
{
    /*
        The idea for this was taken from
        https://www.geeksforgeeks.org/reverse-a-linked-list/
    */
	// FIXME: you must write this
    assert(!circularListIsEmpty(list));

    struct Link *current, *temp;
    current = list->sentinel; //current starts at beginning
    do
    {
        temp = current->next;
        current->next = current->prev;
        current->prev = temp;
        current = temp;
    } while (current != list->sentinel);
}
