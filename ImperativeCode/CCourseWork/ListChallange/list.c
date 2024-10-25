// Implementation of the list module.
#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Each node in a doubly linked list is stored in this structure.
struct node { 
  struct node *back; 
  payload x; 
  struct node *next; 
};
typedef struct node node;

// A list is to be represented as a circular list. It has to contain a doubly linked list
// of nodes that hold an payload each and one special sentinel node that links to the two ends of the list.
// The none field holds this sentinel node. It has a default payload, must always be present for
// a list and always sits before the first payload node and after the last payload node. For a list
// that holds no nodes the back and next fields of the sentinel node point to the sentinel
// node itself. The current node refers to the currently selected payload node in the list. If
// the current node is the none node then no payload is selected.
struct list { 
  node *none, *current; //pointers to nodes
};
typedef struct list list;



// FUNCTION #1: Create a new empty list on the Heap and make payload e the default payload. This default payload
// can be returned by other functions in case no payload is selected. No payload is selected in an empty list.
list *newList(payload e){
  node *es = (node *) malloc(sizeof(node));
  es->back = es; //pointer *back of the node 'es' is pointing back to 'es'
  es->next = es; //pointer *next of the node 'es' is pointing back to 'es'
  es->x = e; // value of the node 'es' is e


  list *l = malloc(sizeof(list));
  
  // both nodes current and none point to the node es
  l->none = es; 
  l->current = es;
  return l;
}

// FUNCTION #2: Free up the list and all the data in it. Does not have to run in O(1).
void freeList(list *xs){
  node *curr;
  first(xs);

  
  while (xs->current != xs->none) {
    curr = xs->current;
    xs->current = xs->current->next;
    free(curr);

  }
  free(xs->none);
  
  free(xs);


}

// FUNCTIONS #3/#4: Set the current payload to the first payload or to the last
// payload of the list, respectively. If the list has no payloads the functions do nothing
// and no payload is selected.
void first(list *xs){
  if (xs->current->back != xs->current) {

    while (xs->current->back != xs->none) {
      xs->current = xs->current->back;
    }
    
  }

}

void last(list *xs){

  if (xs->current->next != xs->current) {
    while (xs->current->next != xs->none){
      xs->current = xs->current->next;
    }
  }
  
}

// FUNCTION #5: Returns true if no payload is selected.
// Otherwise it returns false.
bool none(list *xs){
  if (xs->current == xs->none) return true;
  else return false;
}

// FUNCTION #6: Make the payload in the node following the currently selected payload the current payload
// and return true. If after is called while the last payload is the current payload, then no payload is
// selected and true is returned. If the function is called while no payload
// is selected then the function does nothing and returns false.
bool after(list *xs){
  if (none(xs)) return false;
  else {
    xs->current = xs->current->next;
    return true;
  }
}

// FUNCTION #7: Make the payload in the node before the currently selected payload the current payload
// and return true. If before is called while the first payload is the current payload, then no payload
// is selected and true is returned. If the function is called while no payload
// is selected then the function does nothing and returns false.
bool before(list *xs){
  if (none(xs)) return false;
  else {
    xs->current = xs->current->back;
    return true;
  }
}

// FUNCTION #8: Return the current payload. If get is called and no payload is selected
// then the default payload is returned.
payload get(list *xs){
  return xs->current->x;
}

// FUNCTION #9: Set the current payload to be the value of argument x and return true. If set is called
// while no payload is selected then the function does nothing and returns false.
bool set(list *xs, payload x){
  if (none(xs)) return false;
  else {
    xs->current->x = x;
    return true;
  }
}

// FUNCTION #10: Insert a new node with payload x after the current payload and make it the current payload.
// If insertAfter is called while no payload is selected then the function inserts the payload into a new node 
// placed at the very beginning of the list.
void insertAfter(list *xs, payload x){

  // creates a new node that points back to the current node,
  // and points forward to the node after the current node,
  // with a payload value of x.
  node *new = (node *) malloc(sizeof(node));
  node *curr = xs->current;
  node *n = curr->next;

  new->back = curr; 
  new->next = n; 
  new->x = x;

  
  curr->next = new; // sets the node after the curr to be the new node
  n->back = new; // sets the node n to point back to the new node
  xs->current = new; // sets the new node to be the current node


}

// FUNCTION #11: Insert a new node with payload x before the current payload and make it the current payload.
// If insertAfter is called while no payload is selected then the function inserts the payload into a new node  
// placed at the very end of the list.
void insertBefore(list *xs, payload x){
  
  // creates a new node that points back to the current node,
  // and points forward to the node after the current node,
  // with a payload value of x.
  node *new = (node *) malloc(sizeof(node));
  node *curr = xs->current;
  node *b = curr->back;

  new->next = curr; 
  new->back = b; 
  new->x = x;

  
  curr->back = new; // sets the node after the curr to be the new node
  b->next = new; // sets the node n to point back to the new node
  xs->current = new; // sets the new node to be the current node

}

// FUNCTION #12: Delete the node with the current payload and make its successor the current payload,
// then return true. If deleteToAfter is called while the last payload is the current payload then
// the node with the last payload is deleted, no payload is selected, and true is returned. If 
// deleteToAfter is called while no payload is selected then the function does nothing and returns false.
bool deleteToAfter(list *xs){
  if (none(xs)) return false;
  else {
    node *curr = xs->current;
    node *b = xs->current->back;
    node *n = xs->current->next;

    n->back = b; // makes n point back to b instead of curr
    b->next = n; // makes b point forwards to n instead of curr
    xs->current = n; // makes n the current payload
    free(curr); // frees the previously current node

    return true;


  }
}

// FUNCTION #13: Delete the node with the current payload and make its predecessor the current payload,
// then return true. If deleteToBefore is called while the first payload is the current payload then
// the node with thw first payload is deleted, no payload is selected, and true is returned. If
// deleteToBefore is called while no payload is selected then the function does nothing and returns false.
bool deleteToBefore(list *xs){
  if (none(xs)) return false;
  else {
    node *curr = xs->current;
    node *b = xs->current->back;
    node *n = xs->current->next;

    n->back = b; // makes n point back to b instead of curr
    b->next = n; // makes b point forwards to n instead of curr
    xs->current = b; // makes b the current payload
    free(curr); // frees the previously current node

    return true;
  
  }

}

// FUNCTION #14: Invert the sequence of the list items, that is make the list start with the node and payload that originally had  
// the last position and ensure that payloads originally situated before a payload will now be situated after it, and vice versa.
// The selected payload is not changed by this function. Does not have to run in O(1).
void invert(list *xs){
  node *curr = xs->current;
  node *b = xs->current->back;
  node *n = xs->current->next;
  
  curr->back = n;
  curr->next = b;

  xs->current = curr->next;
  while (xs->current != curr){
    node *curr1 = xs->current;
    node *b1 = xs->current->back;
    node *n1 = xs->current->next;

    curr1->back = n1;
    curr1->next = b1;

    xs->current = curr1->next;
    

  }



}




// ---------- ADD YOUR 14 FUNCTIONS HERE TO SOLVE THE COURSEWORK ----------




// Test the list module, using int as the payload type. Strings are used as
// 'pictograms' to describe lists. Single digits represent payloads and the '|' symbol
// in front of a digit indicates that this is the current payload. If the '|' symbol
// is at the end of the string then 'none' of the payloads is selected. The strings
// "|37", "3|7", "37|" represent a list of two payloads, with the current position
// at the first payload, the last payload, and a situation where 'none' of the payloads
// is selected.
#ifdef test_list

// Build a list from a pictogram, with -1 as the default payload.
// Note: You do not need to understand this function to solve the coursework.
list *build(char *s) {
  list *xs = malloc(sizeof(list));
    int n = strlen(s);
    node *nodes[n];
    for (int i = 0; i < n; i++) nodes[i] = malloc(sizeof(node));
    for (int i = 0; i < n; i++) nodes[i]->next = nodes[(i + 1) % n];
    for (int i = 1; i < n + 1; i++) nodes[i % n]->back = nodes[i - 1];
    xs->none = nodes[0];
    xs->none->x = -1;
    node *p = xs->none->next;
    for (int i = 0; i < strlen(s); i++) {
      if (s[i] == '|') xs->current = p;
      else {
        p->x = s[i] - '0';
        p = p->next;
      }
    }
  return xs;
}

// Destroy a list which was created with the build function and which matches a pictogram.
// Note: You do not need to understand this function to solve the coursework.
void destroy(list *xs, char *s) {
  int n = strlen(s);
  node *nodes[n];
  nodes[0] = xs->none;
  for (int i = 1; i < n; i++) nodes[i] = nodes[i-1]->next;
  for (int i = 0; i < n; i++) free(nodes[i]);
  free(xs);
}

// Check that a list matches a pictogram.
// Note: You do not need to understand this function to solve the coursework.
bool match(list *xs, char *s) {
  int n = strlen(s);
  node *nodes[n];
  nodes[0] = xs->none;
  for (int i = 1; i < n; i++) nodes[i] = nodes[i - 1]->next;
  if (nodes[n - 1]->next != xs->none) return false;
    for (int i = 1; i < n; i++) {
      if (nodes[i]->back != nodes[i - 1]) return false;
    }
  node *p = xs->none->next;
  for (int i = 0; i < strlen(s); i++) {
    if (s[i] == '|') {
      if (p != xs->current) return false;
    }
    else {
      if (p->x != s[i] - '0') return false;
      p = p->next;
    }
  }
  return true;
}

// The tests use an enumeration to say which function to call.
enum { First, Last, None, After, Before, Get, Set, InsertAfter, InsertBefore, DeleteToAfter, DeleteToBefore, Invert};
typedef int function;

// A replacement for the library assert function.
void assert(int line, bool b) {
  if (b) return;
  printf("The test on line %d fails.\n", line);
  exit(1);
}

// Call a given function with a possible integer argument, returning a possible
// integer or boolean result (or -1).
// Note: You do not need to understand this function to solve the coursework.
int call(function f, list *xs, int arg) {
  int result = -1;
  switch (f) {
    case None: result = none(xs); break;
    case First: first(xs); break;
    case Last: last(xs); break;
    case After: result = after(xs); break;
    case Before: result = before(xs); break;
    case Get: result = get(xs); break;
    case Set: result = set(xs, arg); break;
    case InsertAfter: insertAfter(xs, arg); break;
    case InsertBefore: insertBefore(xs, arg); break;
    case DeleteToBefore: result = deleteToBefore(xs); break;
    case DeleteToAfter: result = deleteToAfter(xs); break;
    case Invert: invert(xs); break;
    default: assert(__LINE__, false);
  }
  return result;
}

// Check that a given function does the right thing. The 'in' value is passed to
// the function or is -1. The 'out' value is the expected result, or -1.
bool check(function f, int in, char *before, char *after, int out) {
  list *xs = build(before);
  int result = call(f, xs, in);
  //check your list has indeed a circular list structure
  assert(__LINE__, (xs->none == xs->none->next->back));
  assert(__LINE__, (xs->none == xs->none->back->next));
  //check that your function works correctly as the tests demand
  bool ok = (match(xs, after) && (result == out));
  destroy(xs, after);
  return ok;
}

// Test newList, and call freeList. The test for freeList is that the memory
// leak detector in the -fsanitize=address or -fsanitize=leak compiler option
// reports no problems.
void testNewList() {
    list *xs = newList(-1);
    //check circular list structure
    assert(__LINE__, (xs->none == xs->none->next));
    assert(__LINE__, (xs->none == xs->none->back));
    //check that an empty list is produced with a sentinel correctly
    assert(__LINE__, match(xs, "|"));
    freeList(xs);
}

// Test the various 14 functions.
void testFirst() {
    assert(__LINE__, check(First, -1, "|", "|", -1));
    assert(__LINE__, check(First, -1, "|37", "|37", -1));
    assert(__LINE__, check(First, -1, "3|7", "|37", -1));
    assert(__LINE__, check(First, -1, "37|", "|37", -1));
}

void testLast() {
    assert(__LINE__, check(Last, -1, "|", "|", -1));
    assert(__LINE__, check(Last, -1, "|37", "3|7", -1));
    assert(__LINE__, check(Last, -1, "3|7", "3|7", -1));
    assert(__LINE__, check(Last, -1, "37|", "3|7", -1));
}

void testNone() {
    assert(__LINE__, check(None, -1, "|", "|", true));
    assert(__LINE__, check(None, -1, "|37", "|37", false));
    assert(__LINE__, check(None, -1, "3|7", "3|7", false));
    assert(__LINE__, check(None, -1, "37|", "37|", true));
}

void testAfter() {
    assert(__LINE__, check(After, -1, "|", "|", false));
    assert(__LINE__, check(After, -1, "|37", "3|7", true));
    assert(__LINE__, check(After, -1, "3|7", "37|", true));
    assert(__LINE__, check(After, -1, "37|", "37|", false));
}

void testBefore() {
    assert(__LINE__, check(Before, -1, "|", "|", false));
    assert(__LINE__, check(Before, -1, "|37", "37|", true));
    assert(__LINE__, check(Before, -1, "3|7", "|37", true));
    assert(__LINE__, check(Before, -1, "37|", "37|", false));
}

void testGet() {
    assert(__LINE__, check(Get, -1, "|", "|", -1));
    assert(__LINE__, check(Get, -1, "|37", "|37", 3));
    assert(__LINE__, check(Get, -1, "3|7", "3|7", 7));
    assert(__LINE__, check(Get, -1, "37|", "37|", -1));
}

void testSet() {
    assert(__LINE__, check(Set, 5, "|", "|", false));
    assert(__LINE__, check(Set, 5, "|37", "|57", true));
    assert(__LINE__, check(Set, 5, "3|7", "3|5", true));
    assert(__LINE__, check(Set, 5, "37|", "37|", false));
}

void testInsertAfter() {
    assert(__LINE__, check(InsertAfter, 5, "|", "|5", -1));
    assert(__LINE__, check(InsertAfter, 5, "|37", "3|57", -1));
    assert(__LINE__, check(InsertAfter, 5, "3|7", "37|5", -1));
    assert(__LINE__, check(InsertAfter, 5, "37|", "|537", -1));
}

void testInsertBefore() {
    assert(__LINE__, check(InsertBefore, 5, "|", "|5", -1));
    assert(__LINE__, check(InsertBefore, 5, "|37", "|537", -1));
    assert(__LINE__, check(InsertBefore, 5, "3|7", "3|57", -1));
    assert(__LINE__, check(InsertBefore, 5, "37|", "37|5", -1));
}

void testDeleteToAfter() {
    assert(__LINE__, check(DeleteToAfter, -1, "|", "|", false));
    assert(__LINE__, check(DeleteToAfter, -1, "|37", "|7", true));
    assert(__LINE__, check(DeleteToAfter, -1, "3|7", "3|", true));
    assert(__LINE__, check(DeleteToAfter, -1, "37|", "37|", false));
    assert(__LINE__, check(DeleteToAfter, -1, "|5", "|", true));
}

void testDeleteToBefore() {
    assert(__LINE__, check(DeleteToBefore, -1, "|", "|", false));
    assert(__LINE__, check(DeleteToBefore, -1, "|37", "7|", true));
    assert(__LINE__, check(DeleteToBefore, -1, "3|7", "|3", true));
    assert(__LINE__, check(DeleteToBefore, -1, "37|", "37|", false));
    assert(__LINE__, check(DeleteToBefore, -1, "|5", "|", true));
}

void testInvert() {
    assert(__LINE__, check(Invert, -1, "|", "|", -1));
    assert(__LINE__, check(Invert, -1, "|37", "7|3", -1));
    assert(__LINE__, check(Invert, -1, "3|7", "|73", -1));
    assert(__LINE__, check(Invert, -1, "37|", "73|", -1));
}

int main() {
    testNewList();
    testFirst();
    testLast();
    testNone();
    testAfter();
    testBefore();
    testGet();
    testSet();
    testInsertAfter();
    testInsertBefore();
    testDeleteToAfter();
    testDeleteToBefore();
    testInvert();
    printf("List module tests run OK.\n");
    return 0;
}
#endif
