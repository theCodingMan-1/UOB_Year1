// for efficiency it is worth grouping data values into new 'meaningful' structures.
// A character in a game may have variables for its position, velocity and size for example, that are treated as one object
// This is the start of object oriented programming. 





// struct item {
//     int x, y;
// };


// struct item move (struct item i, int dx, int dy) {
//     i.x = i.x + dx;
//     i.y = i.y + dy;
//     return i;
// }


// int main() {
//     struct item i = {137, 91}; // creates an object i with values i.x = 137 and i.y = 91
//     i.x++; // i.x = 138
//     i.y = i.y + 15; // i.y = 106
//     printf("%d %d\n", i.x, i.y); // ouputs -> 138 106
// }


// struct item {
//     int x, y;
// };


// typedef struct item Item; // saves ourselfves from writing 'struct item' all the time


// Item move (struct item i, int dx, int dy) {
//     i.x = i.x + dx;
//     i.y = i.y + dy;
//     return i;
// }


// int main() {
//     Item i = {137, 91}; // creates an object i with values i.x = 137 and i.y = 91
//     i.x++; // i.x = 138
//     i.y = i.y + 15; // i.y = 106
//     printf("%d %d\n", i.x, i.y); // ouputs -> 138 106
// }





struct word {
    char s[30];
    int count;
};

typedef struct word Word;




struct item {
    int x, y;
};

typedef struct item Item;

void move(Item *i, int dx, int dy) {
    i -> x = i -> x + dx;
    i -> y = i -> y + dy;
}



int main() {
    Item itemData = {137, 91};
    Item *i = &itemData;
    move(i, 1, 15); // pass-by-reference since the pointer to the address has been passed
    

}