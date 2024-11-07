#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>


// Lists are a sequence of data items except that the number of items can change dramatically



typedef int item;



typedef struct list {
    int length; // current number of items in the list
    int capacity; // max of items storable with current allocation
    item *items; // pointer to the item array
} list;


void test() {
    list *l = newList();
    assert(check (l, 0, NULL));
    insert(1, 0, 37);
    freeList(l);
}

