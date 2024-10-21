/* This is a library module supporting lists. A list stores any number of payloads
and has a current payload, which can be any payload from the first payload to the
last payload or a unique 'none' position indicating
that no payload is selected. Every operation is constant time.
The lists provided by this module are not thread safe. */

#include <stdbool.h>

// The type of payloads stored in the list. Change this for different applications.
typedef int payload;

// The list type is opaque (declared here, and defined in lists.c).
struct list;
typedef struct list list;

// FUNCTION #1: Create a new empty list on the Heap and make payload e the default payload. This default payload
// can be returned by other functions in case no payload is selected. No payload is selected in an empty list.
list *newList(payload e);

// FUNCTION #2: Free up the list and all the data in it. Does not have to run in O(1).
void freeList(list *xs);

// FUNCTIONS #3/#4: Set the current payload to the first payload or to the last
// payload of the list, respectively. If the list has no payloads the functions do nothing
// and no payload is selected.
void first(list *xs);
void last(list *xs);

// FUNCTION #5: Returns true if no payload is selected.
// Otherwise it returns false.
bool none(list *xs);

// FUNCTION #6: Make the payload in the node following the currently selected payload the current payload
// and return true. If after is called while the last payload is the current payload, then no payload is
// selected and true is returned. If the function is called while no payload
// is selected then the function does nothing and returns false.
bool after(list *xs);

// FUNCTION #7: Make the payload in the node before the currently selected payload the current payload
// and return true. If before is called while the first payload is the current payload, then no payload
// is selected and true is returned. If the function is called while no payload
// is selected then the function does nothing and returns false.
bool before(list *xs);

// FUNCTION #8: Return the current payload. If get is called and no payload is selected
// then the default payload is returned.
payload get(list *xs);

// FUNCTION #9: Set the current payload to be the value of argument x and return true. If set is called
// while no payload is selected then the function does nothing and returns false.
bool set(list *xs, payload x);

// FUNCTION #10: Insert a new node with payload x after the current payload and make it the current payload.
// If insertAfter is called while no payload is selected then the function inserts the payload into a new node 
// placed at the very beginning of the list.
void insertAfter(list *xs, payload x);

// FUNCTION #11: Insert a new node with payload x before the current payload and make it the current payload.
// If insertAfter is called while no payload is selected then the function inserts the payload into a new node  
// placed at the very end of the list.
void insertBefore(list *xs, payload x);

// FUNCTION #12: Delete the node with the current payload and make its successor the current payload,
// then return true. If deleteToAfter is called while the last payload is the current payload then
// the node with the last payload is deleted, no payload is selected, and true is returned. If 
// deleteToAfter is called while no payload is selected then the function does nothing and returns false.
bool deleteToAfter(list *xs);

// FUNCTION #13: Delete the node with the current payload and make its predecessor the current payload,
// then return true. If deleteToBefore is called while the first payload is the current payload then
// the node with thw first payload is deleted, no payload is selected, and true is returned. If
// deleteToBefore is called while no payload is selected then the function does nothing and returns false.
bool deleteToBefore(list *xs);

// FUNCTION #14: Invert the sequence of the list items, that is make the list start with the node and payload that originally had  
// the last position and ensure that payloads originally situated before a payload will now be situated after it, and vice versa.
// The selected payload is not changed by this function. Does not have to run in O(1).
void invert(list *xs);