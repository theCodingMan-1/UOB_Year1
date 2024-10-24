// Lists are a sequence of data items except that the number of items can change dramatically



typedef int item;



typedef struct list {
    int length; // current number of items in the list
    int capacity; // max of items storable with current allocation
    item *items; // pointer to the item array
} list;